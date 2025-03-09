#ifndef SEARCHABONENTWIDGET_H
#define SEARCHABONENTWIDGET_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QScrollArea;
class QRadioButton;
class DetailsWidget;


class SearchAbonentWidget : public QWidget
{
    Q_OBJECT

public:
    SearchAbonentWidget(QWidget *parent = nullptr);

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
#endif // SEARCHABONENTWIDGET_H
