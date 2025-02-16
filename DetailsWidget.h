#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H

#include <QWidget>
#include "JsonParser.h"

class QLabel;
class QTableWidget;

class DetailsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailsWidget(QWidget *parent = nullptr);
    void updateData(const QString& searchText, bool searchAbonhamar);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();
    void setupTable(const QList<GazQanak>& gazQanakList);
    void setWidgetsHidden(bool isHidden);

    QLabel* m_noDataLabel;

    QWidget* m_mainWidget;
    QWidget* m_dataWidget;

    QLabel* m_customerIdLabel;
    QLabel* m_nameLabel;
    QLabel* m_addressLabel;
    QLabel* m_phoneLabel;
    QLabel* m_hashvichLabel;

    QTableWidget* m_tableWidget;

};

#endif // DETAILSWIDGET_H
