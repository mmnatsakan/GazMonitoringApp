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
    QMap<QString, QString> getInfo() const;


private:
    SqlQueryModel* m_model;

    QString m_mkod;
    QString m_hskichkod;

signals:
    void dataUpdated(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QList<int> &roles = QList<int>());
};

inline const QStringList MONITORING_HEADERS_LIST = {
    "Բաժ.\nհամարը", "Ազգանուն Անունը", "Հասցեն", "Հաշվիչի\nհամարը", "Նախկին\nցուցմունքը", "Առկա\nցուցմունքը", "Մեկնաբա-\nնություն"
};

inline const QString MONITORING_MODEL_BASE_QUERY = "SELECT abonhamar, TRIM(aah) AS aah, TRIM(hasce) AS hasce, TRIM(hashvichn) AS hashvichn, "
                                        "hashnaxc, hashverc, meknab "
                                        "FROM cucak ";

#endif // MONITORINGTABLEVIEW_H
