#include "CustomTableWidget.h"

#include <QHeaderView>
#include <QEvent>
#include <QScroller>
#include <QWheelEvent>
#include <QTimer>
#include <QApplication>
#include <QScrollBar>


CustomTableWidget::CustomTableWidget(QWidget *parent)
    : QTableWidget{parent}
{
    setColumnCount(3);
    setHorizontalHeaderLabels({"Տարի ամիս", "Հաշվեգրում", "Խախտում"});
    verticalHeader()->setVisible(false);
    setSelectionMode(QAbstractItemView::NoSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setShowGrid(true);
    setGridStyle(Qt::SolidLine);
    QScroller::grabGesture(viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(viewport(), QScroller::TouchGesture);
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
    m_stepSize = 0;
    verticalScrollBar()->installEventFilter(this);
    //connect(verticalScrollBar(), )
}

// void CustomTableWidget::wheelEvent(QWheelEvent *event)
// {
//     //updateUI();
//     //QTableWidget::wheelEvent(event);
//     //int stepSize = 0;  // Adjust this for smoother or more rigid scrolling
//     // int delta = event->angleDelta().y() / 120;  // 120 = standard mouse wheel step
//     // m_stepSize += delta;
//     // qDebug() << "Delta: " << delta << ", step: " << m_stepSize;
//     // if(m_stepSize < 10)
//     //     return;

//     // if (delta > 0) {
//     //     qDebug() << "Scrolling Up by" << m_stepSize << "steps";
//     //     verticalScrollBar()->setValue(verticalScrollBar()->value() - m_stepSize);
//     // } else if (delta < 0) {
//     //     qDebug() << "Scrolling Down by" << m_stepSize << "steps";
//     //     verticalScrollBar()->setValue(verticalScrollBar()->value() + m_stepSize);
//     // }
//     updateUI();
//     event->accept();
// }

bool CustomTableWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == verticalScrollBar()) {
        //qDebug() << event;
        if (event->type() == QEvent::MouseMove) {
            qDebug() << event << "   0000000000000000000000";
            updateUI();
            // QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
            // this->wheelEvent(wheelEvent);  // Pass event to the existing handler
            //return true;
        }
        if (event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchUpdate) {
            qDebug() << "Touch Scrolling Detected!";
            updateUI();
            //return true;  // Prevent unnecessary propagation
        }
    }
    return QTableWidget::eventFilter(watched, event);
}

void CustomTableWidget::updateUI() {
    // QTimer::singleShot(10, this, [this]() {
    //     this->update();
    //     QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    // });
    qDebug() << "111111111111111111111111111";
    QMetaObject::invokeMethod(this, [this]() {
    qDebug() << "22222222222222222222222222222";
        this->update();
        this->repaint();
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
    }, Qt::QueuedConnection);
}
