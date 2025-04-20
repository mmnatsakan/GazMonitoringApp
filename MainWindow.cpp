#include "MainWindow.h"
#include "DatabaseController.h"
#include "StartPage.h"
#include "MonitoringPage.h"

#include <QStackedWidget>
#include <QBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    DatabaseController::instance()->openDatabase();
    createMembers();
    makeConnections();
    setupLayout();
#ifdef ANDROID
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_AcceptTouchEvents);
#endif
}

void MainWindow::createMembers()
{
    m_stackedWidget = new QStackedWidget(this);
    m_startPage = new StartPage(m_stackedWidget);
    m_monitoringPage = new MonitoringPage(m_stackedWidget);

    m_stackedWidget->addWidget(m_startPage);
    m_stackedWidget->addWidget(m_monitoringPage);
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::makeConnections()
{
    connect(m_startPage, &StartPage::mainDataReady, this, [this](){
        m_monitoringPage->updateData(m_startPage->getMainData());
        m_stackedWidget->setCurrentIndex(1);
    } );
    connect(m_monitoringPage, &MonitoringPage::goToStartPage, this, [this](){

        m_stackedWidget->setCurrentIndex(0);
    });
}

void MainWindow::setupLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_stackedWidget);
    this->setLayout(mainLayout);
}
