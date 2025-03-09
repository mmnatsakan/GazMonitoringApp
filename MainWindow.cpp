#include "MainWindow.h"
#include "DatabaseController.h"
#include "StartPage.h"
#include "CucBlankPage.h"

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
}

void MainWindow::createMembers()
{
    m_stackedWidget = new QStackedWidget(this);
    m_startPage = new StartPage(m_stackedWidget);
    m_cucBlankPage = new CucBlankPage(m_stackedWidget);

    m_stackedWidget->addWidget(m_startPage);
    m_stackedWidget->addWidget(m_cucBlankPage);
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::makeConnections()
{
    connect(m_startPage, &StartPage::mainDataReady, this, [this](){
        m_cucBlankPage->updateData(m_startPage->getMainData());
        m_stackedWidget->setCurrentIndex(1);
    } );
    connect(m_cucBlankPage, &CucBlankPage::goToStartPage, this, [this](){

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
