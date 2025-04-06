#include "SqlQueryModel.h"
#include "Constants.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTimer>

#define FILTER_DELAY_TIME 300

SqlQueryModel::SqlQueryModel(QObject* parent)
    :QSqlQueryModel(parent)
{

}

void SqlQueryModel::refresh() {

    QSqlQuery query(QSqlDatabase::database());

    QString finalQueryString = m_baseQuery;
    qDebug() << finalQueryString;
    if (!query.exec(finalQueryString)) {
        qWarning() << "Query execution failed:" << query.lastError();
        return;
    }

    if (finalQueryString.trimmed().toUpper().startsWith("SELECT")) {
        setQuery(finalQueryString, QSqlDatabase::database());
    }
}

Qt::ItemFlags SqlQueryModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);
    if (index.column() == HASHVERC_COLUMN_INDEX)
        return defaultFlags | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    return defaultFlags & ~(Qt::ItemIsEditable | Qt::ItemIsSelectable);
}

bool SqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole || !updateMonitoringTable(index, value))
        return false;

    this->setQuery(this->query().lastQuery());
    emit dataChanged(index, index);
    return true;
}

bool SqlQueryModel::updateMonitoringTable(const QModelIndex &index, const QVariant &value)
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
    query.prepare(QString("UPDATE cucak SET " + columnName + " = :value WHERE mkod = :mkod and abonhamar = :abonhamar "));

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

void SqlQueryModel::setBaseQuery(const QString &query, const QString &mkod)
{
    m_mkod = mkod;
    if(m_baseQuery == query)
        return;
    m_baseQuery = query;
    refresh();
}



