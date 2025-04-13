#ifndef CUSTOMKEYBOARD_H
#define CUSTOMKEYBOARD_H

#include <QWidget>

class QStackedWidget;
class NavigationBar;

class CustomKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit CustomKeyboard(QWidget *parent = nullptr);

signals:
};

#endif // CUSTOMKEYBOARD_H



// class MainWindow : public BaseFrameWidget
// {
//     Q_OBJECT

// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();

// private:
//     void createMembers();
//     void installStyleSheets();
//     void makeConnections();
//     void setupLayout();

//     QStackedWidget* m_stackedWidget;
//     NavigationBar* m_navigationBar;

// private slots:
//     void onCurrentTabChangedSlot(int index);
// };
