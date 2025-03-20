#include "CucBlankPage.h"
#include "CucBlankTableView.h"
#include "UIStyle.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>


CucBlankPage::CucBlankPage(QWidget *parent)
    : QWidget{parent}
    , m_maxSparum(1000)
{
    //setFixedSize(1200, 800);

    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();

}

void CucBlankPage::updateData(QMap<QString, QString> topWidgetDataMap)
{
    m_ttLabel->setText(topWidgetDataMap["tt"]);
    m_hskichLabel->setText(topWidgetDataMap["hskich"]);
    m_dateLabel->setText(topWidgetDataMap["date"]);
    m_tableView->updateUiData(topWidgetDataMap["tt"].left(2), topWidgetDataMap["hskich"].left(2), topWidgetDataMap["date"].right(2).left(1));
    updateCounts();
}

void CucBlankPage::createMembers()
{
    m_mainWidget = new QWidget(this);

    m_goToStartPageButton = new QPushButton("Հետ", m_mainWidget);
    m_goToStartPageButton->setFixedSize(100, 50);

    m_abonentCountLabel = new QLabel(m_mainWidget);
    m_ttLabel = new QLabel(m_mainWidget);
    m_hskichLabel = new QLabel(m_mainWidget);
    m_dateLabel = new QLabel(m_mainWidget);
    m_totalHashxmLabel = new QLabel(m_mainWidget);

    m_tableView = new CucBlankTableView(m_mainWidget);
}

void CucBlankPage::installStyleSheets()
{
    m_goToStartPageButton->setStyleSheet(PUSH_BUTTON_STYLE_SHEET);
    m_abonentCountLabel->setStyleSheet("font-size: 18px; color: green; font-weight: 600; border: none;");
    m_ttLabel->setStyleSheet("font-size: 18px; color: black; font-weight: 600; border: none;");
    m_hskichLabel->setStyleSheet("font-size: 18px; color: black; font-weight: 600; border: none;");
    m_dateLabel->setStyleSheet("font-size: 18px; color: black; font-weight: 600; border: none;");
    m_totalHashxmLabel->setStyleSheet("font-size: 18px; color: green; font-weight: 600; border: none;");
}

void CucBlankPage::setupLayout()
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
    topLayout->addWidget(m_dateLabel);
    topLayout->addStretch();
    topLayout->addWidget(m_totalHashxmLabel);

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

void CucBlankPage::makeConnections()
{
    connect(m_goToStartPageButton, &QPushButton::clicked, this, &CucBlankPage::goToStartPage);
    connect(m_tableView, &CucBlankTableView::dataUpdated, this, &CucBlankPage::updateCounts);
}

void CucBlankPage::updateCounts()
{
    QMap<QString, QString> infoMap = m_tableView->getInfo();

    m_abonentCountLabel->setText(infoMap["filledCount"] + " / " + infoMap["totalCount"]);
    m_totalHashxmLabel->setText("Ընդ. " + infoMap["totalHashxm"] + " խմ");
}
