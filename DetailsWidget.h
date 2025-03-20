#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H

#include <QWidget>
#include "JsonParser.h"

class QLabel;
class QTableWidget;
class QPushButton;

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
    void setupTable(const QList<AmisData>& gazQanakList);
    void setWidgetsHidden(bool isHidden);
    void updateUI();
    void updateArrows();

    QLabel* m_noDataLabel;

    QWidget* m_mainWidget;

    QLabel* m_customerLabel;

    QTableWidget* m_tableWidget;

    // QPushButton* m_goUp;
    // QPushButton* m_goDown;


};

#endif // DETAILSWIDGET_H
