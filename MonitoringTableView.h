#ifndef MONITORINGTABLEVIEW_H
#define MONITORINGTABLEVIEW_H

#include <QTableView>

class SqlQueryModel;


class MonitoringTableView : public QTableView
{
    Q_OBJECT
public:
    explicit MonitoringTableView(QWidget *parent = nullptr);
    void updateUiData(const QString& mkod, const QString& hskichkod);
    QMap<QString, QString> getCountsInfo() const;


private:
    void installStyleSheets();
    void makeConnections();

    void clearCell(const QModelIndex &index);
    void showDetailsWidget(int row);
    SqlQueryModel* m_model;

signals:
    void dataUpdated(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QList<int> &roles = QList<int>());

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MONITORINGTABLEVIEW_H
