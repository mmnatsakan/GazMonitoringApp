#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H

#include <QDialog>

#include "Utils.h"

class QLabel;
class QTableWidget;

class DetailsWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DetailsWidget(const Utils::MainData &mainData, QWidget *parent = nullptr);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void updateData(const Utils::MainData &mainData);

    QWidget* m_mainWidget;
    QLabel* m_customerLabel;
    QTableWidget* m_tableWidget;

};

#endif // DETAILSWIDGET_H
