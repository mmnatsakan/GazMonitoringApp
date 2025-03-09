#ifndef CUCBLANKPAGE_H
#define CUCBLANKPAGE_H

#include <QWidget>

class QLabel;
class QPushButton;
class CucBlankTableView;

class CucBlankPage : public QWidget
{
    Q_OBJECT
public:
    explicit CucBlankPage(QWidget *parent = nullptr);
    void updateData(QMap<QString, QString> topWidgetDataMap);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();

    void updateCounts();

    QWidget* m_mainWidget;

    QPushButton* m_goToStartPageButton;
    QLabel* m_abonentCountLabel;
    QLabel* m_ttLabel;
    QLabel* m_hskichLabel;
    QLabel* m_dateLabel;
    QLabel* m_totalHashxmLabel;

    CucBlankTableView* m_tableView;

    int m_maxSparum;

signals:
    void goToStartPage();
};

#endif // CUCBLANKPAGE_H
