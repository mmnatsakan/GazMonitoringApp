#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QScrollArea;
class QRadioButton;
class DetailsWidget;


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createMembers();
    void installStyleSheets();
    void setupLayout();
    void makeConnections();
    void updateUI();

    QRadioButton* m_abonhamarRadioButton;
    QRadioButton* m_hashvichRadioButton;

    QLineEdit* m_searchLineEdit;
    QPushButton* m_searchButton;

    DetailsWidget* m_detailsWidget;

private slots:
    void onSearchButtonClickedSlot();

protected:
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
