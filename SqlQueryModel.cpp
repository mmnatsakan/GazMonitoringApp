#include "SqlQueryModel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTimer>

#define FILTER_DELAY_TIME 300

SqlQueryModel::SqlQueryModel(QSqlQueryModel* parent)
{
    // m_filterTimer = new QTimer(this);
    // m_filterTimer->setSingleShot(true);
    // connect(m_filterTimer, &QTimer::timeout, this, &SqlQueryModel::refresh);
}

void SqlQueryModel::refresh() {
    // if(m_filterTimer->isActive())
    //     m_filterTimer->stop();

    QSqlQuery query(QSqlDatabase::database());

    QString finalQueryString = m_baseQuery; //+ m_filterText + m_sortText;

    if (!query.exec(finalQueryString)) {
        qWarning() << "Query execution failed:" << query.lastError();
        return;
    }

    if (finalQueryString.trimmed().toUpper().startsWith("SELECT")) {
        setQuery(finalQueryString, QSqlDatabase::database());
    }
}

Qt::ItemFlags SqlQueryModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 6 || index.column() == 9)
        flags |= Qt::ItemIsEditable;
    return flags;
}
/*
void SqlQueryModel::setFilter(const QString &filterText)
{
    if (m_filterText == filterText)
        return;

    m_filterText = filterText.isEmpty() ? "" : " WHERE (:filterText) ";
    m_filterTimer->start(FILTER_DELAY_TIME);
}

void SqlQueryModel::setSort(const QString &sortText)
{
    if (m_sortText == sortText)
        return;

    m_sortText = sortText.isEmpty() ? "" : " ORDER BY (:sortText) ";
}
*/
QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    // if (role == Qt::DisplayRole) {
    //     QVariant value = QSqlQueryModel::data(index, role);

    //     if (value.userType() == QMetaType::Int || value.userType() == QMetaType::Double) {
    //         if (value.toDouble() == 0) {
    //             return QVariant();
    //         }
    //     }
    //     else if (value.userType() == QMetaType::QString && value.toString() == "0") {
    //         return QVariant();
    //     }
    // }
    return QSqlQueryModel::data(index, role);
}

bool SqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole || !updateDatabaseTable(index, value))
        return false;

    this->setQuery(this->query().lastQuery());
    emit dataChanged(index, index);
    return true;
}

bool SqlQueryModel::updateDatabaseTable(const QModelIndex &index, const QVariant &value)
{
    QString abonhamar = record(index.row()).value("abonhamar").toString();
    QSqlQuery query;
    if(index.column() == 6){
        query.prepare(QString("UPDATE cucBlank SET hashverc = %1, hashxm = %2 WHERE mkod = %3 and abonhamar = %4 ").arg(value.toString(), calculateHashxm(index, value), m_mkod, abonhamar));
    }
    else if(index.column() == 9)
        query.prepare(QString("UPDATE cucBlank SET meknab = %1, WHERE mkod = %2 and abonhamar = %3 ").arg(value.toString(), m_mkod, abonhamar));
    else
        return false;
    qDebug() << query.lastQuery();
    if (!query.exec()) {
        qWarning() << "Update failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QString SqlQueryModel::calculateHashxm(const QModelIndex &index, const QVariant &value)
{
    if(value.toString().isEmpty())
        return "NULL";
    double hashnaxc = record(index.row()).value("hashnaxc").toDouble();
    double hashxm = value.toDouble() - hashnaxc;
    if(hashxm >= 0)
        return QString::number(hashxm);

    int astichan1 = 0;

    QSqlQuery query;
    query.prepare(QString("SELECT b.dovlenie FROM cucBlank a"
                          " LEFT JOIN hashvich b ON a.mkod = b.mkod and a.hashtipkod = b.kod"
                          " WHERE a.mkod = '%1' and a.abonhamar = '%2'").arg(m_mkod, record(index.row()).value("abonhamar").toString()));
    qDebug() << query.lastQuery();
    query.exec();
    if (query.next())
        astichan1 = query.value(0).toInt();
    if(astichan1 == 0)
        astichan1 = (int)std::log10(hashnaxc) + 1;
    hashxm += pow(10, astichan1);
    return QString::number(hashxm);
}

void SqlQueryModel::setBaseQuery(const QString &query, const QString &mkod)
{
    m_mkod = mkod;
    if(m_baseQuery == query)
        return;
    // m_filterText = "";
    // m_sortText = "";
    m_baseQuery = query;
    refresh();
}



