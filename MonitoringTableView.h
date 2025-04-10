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

private:
    void installStyleSheets();
    void makeConnections();
    void showDetails(const QString &value, bool searchByAbonhamar);

    void clearCell(const QModelIndex &index);
    SqlQueryModel* m_model;

protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void filledRowsCountsChanged(const QString& filledCount, const QString& totalCount);

private slots:
    void onHorizontalHeaderSectionClickedSlot(int section);

};

#endif // MONITORINGTABLEVIEW_H
