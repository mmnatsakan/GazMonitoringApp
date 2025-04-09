#include "StartPage.h"
#include "UIStyle.h"
#include "DatabaseController.h"

#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QBoxLayout>

StartPage::StartPage(QWidget *parent)
    : QWidget{parent}
{
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_AcceptTouchEvents);
}

QMap<QString, QString> StartPage::getMainData() const
{
    QMap<QString, QString> dataMap;
    dataMap["tt"] = m_ttComboBox->currentText().trimmed();
    dataMap["hskich"] = m_hskichComboBox->currentText().trimmed();
    return dataMap;
}

void StartPage::createMembers()
{
    m_mainWidget = new QWidget(this);
    m_centralWidget = new QWidget(m_mainWidget);

    m_ttLabel = new QLabel("ԱՇԾ", m_centralWidget);
    m_hskichLabel = new QLabel("Հսկիչ", m_centralWidget);

    m_ttComboBox = new QComboBox(m_centralWidget);
    m_hskichComboBox = new QComboBox(m_centralWidget);

    m_ttComboBox->addItems(DatabaseController::instance()->getTtList());
    m_mkod = m_ttComboBox->currentText().left(2);
    m_hskichComboBox->addItems(DatabaseController::instance()->getHskichList(m_mkod));
    m_hskichkod = m_hskichComboBox->currentText().left(2);

    m_ttComboBox->setFixedSize(400, 50);
    m_hskichComboBox->setFixedSize(400, 50);

    m_enterButton = new QPushButton("Մուտք", m_centralWidget);
    m_cancelButton = new QPushButton("Չեղարկել", m_centralWidget);
    m_enterButton->setFixedSize(150, 50);
    m_cancelButton->setFixedSize(m_enterButton->size());
}

void StartPage::installStyleSheets()
{
    m_mainWidget->setStyleSheet("background: transparent;");
    m_centralWidget->setStyleSheet("QWidget{background: lightGray;}" + START_PAGE_LABEL_STYLE_SHEET + COMBOBOX_STYLE_SHEET + PUSH_BUTTON_STYLE_SHEET);
}

void StartPage::setupLayout()
{
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(50);
    gridLayout->addWidget(m_ttLabel, 0, 0, Qt::AlignRight);
    gridLayout->addWidget(m_ttComboBox, 0, 1, Qt::AlignLeft);
    gridLayout->addWidget(m_hskichLabel, 1, 0, Qt::AlignRight);
    gridLayout->addWidget(m_hskichComboBox, 1, 1, Qt::AlignLeft);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(0);
    buttonsLayout->addWidget(m_enterButton);
    buttonsLayout->addWidget(m_cancelButton);


    QVBoxLayout* centralLayout = new QVBoxLayout();
    centralLayout->setContentsMargins(50, 50, 50, 50);
    centralLayout->setSpacing(80);
    centralLayout->addLayout(gridLayout);
    centralLayout->addLayout(buttonsLayout);
    m_centralWidget->setLayout(centralLayout);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_centralWidget);
    layout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addStretch();
    mainLayout->addLayout(layout);
    mainLayout->addStretch();
    m_mainWidget->setLayout(mainLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->setSpacing(0);
    thisLayout->addWidget(m_mainWidget);
    this->setLayout(thisLayout);
}

void StartPage::makeConnections()
{
    connect(m_ttComboBox, &QComboBox::currentTextChanged, this, [=](const QString& text){
        m_hskichComboBox->clear();
        m_mkod = text.left(2);
        m_hskichComboBox->addItems(DatabaseController::instance()->getHskichList(m_mkod));
        m_hskichkod = m_hskichComboBox->currentText().left(2);
    });
    connect(m_hskichComboBox, &QComboBox::currentTextChanged, this, [=](const QString& text){
        m_hskichkod = text.left(2);
    });
    connect(m_enterButton, &QPushButton::clicked, this, [=](){
        emit mainDataReady();
        hide();
    });
    connect(m_cancelButton, &QPushButton::clicked, qApp, &QApplication::quit);
}
