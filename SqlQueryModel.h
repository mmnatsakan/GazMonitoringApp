#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

class QTimer;

class SqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    SqlQueryModel(QSqlQueryModel* parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    //void setFilter(const QString &filterText = QString());
    //void setSort(const QString &sortText = QString());
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void setBaseQuery(const QString& query, const QString& mkod);
    void refresh();


private:
    bool updateDatabaseTable(const QModelIndex &index, const QVariant &value);
    QString calculateHashxm(const QModelIndex &index, const QVariant &value);
    QString m_baseQuery;
    QString m_mkod;
    //QString m_filterText;
    //QString m_sortText;
    //QTimer* m_filterTimer;
};

#endif // SQLQUERYMODEL_H
