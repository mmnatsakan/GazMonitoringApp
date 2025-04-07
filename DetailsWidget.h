#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H

#include <QDialog>

struct AmisData{
    AmisData() {}
    QString taram;
    QString hashxm;
    QString xaxthash;
    QString hashvichn;
    QString kniqner;
};

struct MainData
{
    MainData() {}
    QString abonhamar;
    QString aah;
    QString hasce;
    QString sot_hamar;
    QString hashvich;
    QString hashvichn;
    QString hashnaxc;
    QString kniq;
    QList<AmisData> tableDataList;
};

class QLabel;
class QTableWidget;

class DetailsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DetailsWidget(const MainData &mainData, QWidget *parent = nullptr);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void updateData(const MainData &mainData);

    QWidget* m_mainWidget;
    QLabel* m_customerLabel;
    QTableWidget* m_tableWidget;

};

#endif // DETAILSWIDGET_H
