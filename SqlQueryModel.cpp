#include "SqlQueryModel.h"
#include "Constants.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTimer>

#define FILTER_DELAY_TIME 300

SqlQueryModel::SqlQueryModel(QObject* parent)
    : QSqlQueryModel(parent)
    , m_mainTable("cucak")
{

}

void SqlQueryModel::refresh() {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare(m_baseQuery.arg(m_mainTable) + m_filterString);
    query.bindValue(":mkod", m_mkod);
    query.bindValue(":hskichkod", m_hskichkod);
    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError();
        return;
    }

    if (m_baseQuery.trimmed().toUpper().startsWith("SELECT")) {
        setQuery(query);
    }
}

Qt::ItemFlags SqlQueryModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);
    if (index.column() == HASHVERC_COLUMN_INDEX)
        return defaultFlags | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    return defaultFlags & ~(Qt::ItemIsEditable | Qt::ItemIsSelectable);
}

bool SqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole || !updateMainTable(index, value))
        return false;

    this->setQuery(this->query().lastQuery());
    emit dataChanged(index, index);
    return true;
}

void SqlQueryModel::setMkodHskichkod(const QString &mkod, const QString &hskichkod)
{
    m_mkod = mkod;
    m_hskichkod = hskichkod;
    m_baseQuery = MONITORING_MODEL_BASE_QUERY;
    refresh();
}

bool SqlQueryModel::updateMainTable(const QModelIndex &index, const QVariant &value)
{
    QString columnName;
    switch (index.column()) {
    case HASHVERC_COLUMN_INDEX:
        columnName = "hashverc";
        break;
    case MEKNAB_COLUMN_INDEX:
        columnName = "meknab";
        break;
    default:
        return false;
    }
    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET %2 = :value WHERE mkod = :mkod and abonhamar = :abonhamar ").arg(m_mainTable).arg(columnName));

    query.bindValue(":value", value);
    query.bindValue(":mkod", m_mkod);
    query.bindValue(":abonhamar", record(index.row()).value("abonhamar").toString());

    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qWarning() << "Update failed:" << query.lastError().text();
        return false;
    }
    return true;
}

void SqlQueryModel::setBaseQuery(const QString &query)
{
    if(m_baseQuery == query)
        return;
    m_baseQuery = query;
    refresh();
}

QMap<QString, QString> SqlQueryModel::getCountsInfo() const
{
    QSqlQuery query;
    query.prepare(QString("SELECT sum(iif(hashverc is not null, 1, 0)) as filledCount, COUNT(*) as totalCount FROM %1 "
                          "WHERE mkod = :mkod AND hskichkod = :hskichkod ").arg(m_mainTable)); //and filtr <> ''
    query.bindValue(":mkod", m_mkod);
    query.bindValue(":hskichkod", m_hskichkod);

    qDebug() << query.lastQuery();
    qDebug() << query.boundValueNames() << " *** " << query.boundValues();
    query.exec();
    qDebug() << query.executedQuery();

    QMap<QString, QString> infoMap;
    if (query.next()) {
        infoMap["filledCount"] = QString::number(query.value(0).toInt());
        infoMap["totalCount"] =  QString::number(query.value(1).toInt());
    }
    return infoMap;
}

Utils::MainData SqlQueryModel::getDetails(const QString &value, bool searchByAbonhamar) const
{
    QSqlQuery query;
    query.prepare(  QString("SELECT abonhamar, TRIM(aah) AS aah, TRIM(hasce) AS hasce, TRIM(hashvichn) AS hashvichn, "
                    "hashnaxc, hashxmner, kniqner "
                          "FROM :tableName WHERE mkod = :mkod AND :searchColumn = :value ").arg(m_mainTable).arg(searchByAbonhamar ? "abonhamar" : "hashvichn"));
    query.bindValue(":mkod", m_mkod);
    query.bindValue(":value", value);
    qDebug() << query.lastQuery();
    query.exec();

    Utils::MainData mainData;
    if (query.next()) {
        mainData.abonhamar = query.value("abonhamar").toString();
        mainData.aah = query.value("aah").toString();
        mainData.hasce = query.value("hasce").toString();
        mainData.hashvichn = query.value("hashvichn").toString();
        mainData.hashnaxc = query.value("hashnaxc").toString();
        Utils::AmisData amisData;
        QStringList gazList = query.value("hashxmner").toString().split(";");
        QStringList kniqList = query.value("kniqner").toString().split(";");
        for(int i = 0; i < gazList.count() - 1; ++i){
            if(!gazList.at(i).isEmpty()){
                QStringList gazQanakData = gazList.at(i).split("_");
                amisData.taram = gazQanakData.at(0);
                amisData.hashxm = gazQanakData.at(1);
                amisData.xaxthash = gazQanakData.at(2);
            }
            if(i < kniqList.count() && !kniqList.at(i).isEmpty()){
                QStringList kniqData = kniqList.at(i).split("_");
                amisData.hashvichn = kniqData.at(1);
                amisData.kniqner = kniqData.at(2);
            }
            mainData.tableDataList << amisData;
        }
    }
    return mainData;
}

