#include "MonitoringPage.h"
#include "MonitoringTableView.h"
#include "UIStyle.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>


MonitoringPage::MonitoringPage(QWidget *parent)
    : QWidget{parent}
    , m_maxSparum(1000)
{
    //setFixedSize(1200, 800);

    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();

}

void MonitoringPage::updateData(QMap<QString, QString> topWidgetDataMap)
{
    m_ttLabel->setText(topWidgetDataMap["tt"]);
    m_hskichLabel->setText(topWidgetDataMap["hskich"]);
    m_tableView->updateUiData(topWidgetDataMap["tt"].left(2), topWidgetDataMap["hskich"].left(2));
    updateCounts();
}

void MonitoringPage::createMembers()
{
    m_mainWidget = new QWidget(this);

    m_goToStartPageButton = new QPushButton("Հետ", m_mainWidget);
    m_goToStartPageButton->setFixedSize(100, 50);

    m_abonentCountLabel = new QLabel(m_mainWidget);
    m_ttLabel = new QLabel(m_mainWidget);
    m_hskichLabel = new QLabel(m_mainWidget);

    m_tableView = new MonitoringTableView(m_mainWidget);
}

void MonitoringPage::installStyleSheets()
{
    m_goToStartPageButton->setStyleSheet(PUSH_BUTTON_STYLE_SHEET);
    m_abonentCountLabel->setStyleSheet("font-size: 18px; color: green; font-weight: 600; border: none;");
    m_ttLabel->setStyleSheet("font-size: 18px; color: black; font-weight: 600; border: none;");
    m_hskichLabel->setStyleSheet("font-size: 18px; color: black; font-weight: 600; border: none;");
}

void MonitoringPage::setupLayout()
{
    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(50);
    topLayout->addWidget(m_goToStartPageButton);
    topLayout->addStretch();
    topLayout->addWidget(m_abonentCountLabel);
    topLayout->addStretch();
    topLayout->addWidget(m_ttLabel);
    topLayout->addStretch();
    topLayout->addWidget(m_hskichLabel);
    topLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(30);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_tableView);
    m_mainWidget->setLayout(mainLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->setSpacing(0);
    thisLayout->addWidget(m_mainWidget);
    this->setLayout(thisLayout);
}

void MonitoringPage::makeConnections()
{
    connect(m_goToStartPageButton, &QPushButton::clicked, this, &MonitoringPage::goToStartPage);
    connect(m_tableView, &MonitoringTableView::dataUpdated, this, &MonitoringPage::updateCounts);
}

void MonitoringPage::updateCounts()
{
    QMap<QString, QString> infoMap = m_tableView->getInfo();

    m_abonentCountLabel->setText(infoMap["filledCount"] + " / " + infoMap["totalCount"]);
}
