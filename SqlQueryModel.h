#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

#include "Utils.h"

class QTimer;

class SqlQueryModel : public QSqlQueryModel {
    Q_OBJECT
public:
    SqlQueryModel(QObject *parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void setMkodHskichkod(const QString& mkod, const QString& hskichkod);
    void setBaseQuery(const QString& query);
    void refresh();
    QMap<QString, QString> getCountsInfo() const;
    Utils::MainData getDetails(const QString& value, bool searchByAbonhamar) const;

private:
    bool updateMainTable(const QModelIndex &index, const QVariant &value);
    QString m_baseQuery;
    QString m_filterString;
    QString m_mkod;
    QString m_hskichkod;
    QString m_mainTable;

};

#endif // SQLQUERYMODEL_H
