#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QTableWidget>


class CustomTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit CustomTableWidget(QWidget *parent = nullptr);

private:
    void updateUI();
    double m_stepSize;
    // QWidget interface
protected:
    //void wheelEvent(QWheelEvent *event);

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // CUSTOMTABLEWIDGET_H
