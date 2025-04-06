#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

class QTimer;

class SqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    SqlQueryModel(QObject *parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void setBaseQuery(const QString& query, const QString& mkod);
    void refresh();

private:
    bool updateMonitoringTable(const QModelIndex &index, const QVariant &value);
    QString m_baseQuery;
    QString m_mkod;

};

#endif // SQLQUERYMODEL_H
