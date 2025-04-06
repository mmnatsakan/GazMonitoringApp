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
    void updateData(const MainData &mainData);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void updateUI();

    QWidget* m_mainWidget;
    QLabel* m_customerLabel;
    QTableWidget* m_tableWidget;

};

#endif // DETAILSWIDGET_H
