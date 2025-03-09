#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QStackedWidget;
class CucBlankPage;
class StartPage;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createMembers();
    void makeConnections();
    void setupLayout();

    QStackedWidget* m_stackedWidget;
    CucBlankPage* m_cucBlankPage;
    StartPage* m_startPage;

signals:
};

#endif // MAINWIDGET_H
