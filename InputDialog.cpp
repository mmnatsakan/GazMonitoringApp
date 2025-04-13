#include "InputDialog.h"
#include "UIStyle.h"
#include "AndroidBridge.h"
#include "AndroidHelper.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFocusEvent>

InputDialog::InputDialog(QWidget *parent)
    : QDialog{parent}
{
    setFixedWidth(300);
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_AcceptTouchEvents);
    setWindowTitle("Փնտրել");
}

void InputDialog::setLabelText(const QString &text)
{
    m_label->setText(text);
}

QString InputDialog::getTextValue() const
{
    return m_lineEdit->text();
}

void InputDialog::createMembers()
{
    m_mainWidget = new QWidget(this);
    m_label = new QLabel(m_mainWidget);
    m_lineEdit = new QLineEdit(m_mainWidget);
    m_lineEdit->setFocusPolicy(Qt::StrongFocus);
    m_lineEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setInputMethodHints(Qt::ImhDigitsOnly);
    m_acceptButton = new QPushButton("Հաստատել", m_mainWidget);
    m_cancelButton = new QPushButton("Չեղարկել", m_mainWidget);
    // m_acceptButton = new QPushButton(QIcon(":icons/icon_accept.svg"), "", m_mainWidget);
    // m_cancelButton = new QPushButton(QIcon(":icons/icon_cancel.svg"), "", m_mainWidget);
}

void InputDialog::installStyleSheets()
{
    setStyleSheet("QWidget{background: white;}" + START_PAGE_LABEL_STYLE_SHEET + LINE_EDIT_STYLE_SHEET + PUSH_BUTTON_STYLE_SHEET);
}

void InputDialog::setupLayout()
{
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(20);
    buttonsLayout->addWidget(m_acceptButton);
    buttonsLayout->addWidget(m_cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(m_label);
    mainLayout->addWidget(m_lineEdit);
    mainLayout->addLayout(buttonsLayout);
    m_mainWidget->setLayout(mainLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->setSpacing(0);
    thisLayout->addWidget(m_mainWidget);
    this->setLayout(thisLayout);
}

void InputDialog::makeConnections()
{
    connect(m_acceptButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_lineEdit, &QLineEdit::cursorPositionChanged, this,[=](){
        update();
        repaint();
    });
    connect(AndroidBridge::instance(), &AndroidBridge::speechRecognized, this, [this](const QString& text) {
        qDebug() << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
        m_lineEdit->setText(m_lineEdit->text() + text);
    });}

bool InputDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_lineEdit and event->type() == QEvent::FocusIn){
        qDebug() << "KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK";
        AndroidHelper::startVoiceInput();
        return true;
    }
    return QDialog::eventFilter(watched, event);
}
