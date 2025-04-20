#ifndef MONITORINGPAGE_H
#define MONITORINGPAGE_H

#include <QWidget>

class QLabel;
class QPushButton;
class MonitoringTableView;
class QCheckBox;

class MonitoringPage : public QWidget
{
    Q_OBJECT
public:
    explicit MonitoringPage(QWidget *parent = nullptr);
    void updateData(QMap<QString, QString> topWidgetDataMap);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();

    QWidget* m_mainWidget;

    QPushButton* m_goToStartPageButton;
    QCheckBox* m_showFilteredCheckBox;

    QLabel* m_abonentCountLabel;
    QLabel* m_ttLabel;
    QLabel* m_hskichLabel;

    MonitoringTableView* m_tableView;


signals:
    void goToStartPage();
};

#endif // MONITORINGPAGE_H
