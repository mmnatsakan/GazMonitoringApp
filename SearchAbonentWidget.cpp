#include "SearchAbonentWidget.h"
#include "UIStyle.h"
#include "DetailsWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QRadioButton>
#include <QKeyEvent>
#include <QApplication>


SearchAbonentWidget::SearchAbonentWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Բաժանորդի փնտրման ծրագիր");
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();

    JsonParser::instance()->parseJsonFile(":output.json");
    m_searchLineEdit->setFocus();
    m_searchButton->setDisabled(true);
    m_hashvichRadioButton->setChecked(true);
    updateUI();
}

void SearchAbonentWidget::createMembers()
{
    m_detailsWidget = new DetailsWidget(this);

    m_abonhamarRadioButton = new QRadioButton("Բաժ. համար", this);
    m_abonhamarRadioButton->setAttribute(Qt::WA_AcceptTouchEvents);
    m_hashvichRadioButton = new QRadioButton("Հաշվիչի համար", this);
    m_hashvichRadioButton->setAttribute(Qt::WA_AcceptTouchEvents);

    m_searchLineEdit = new QLineEdit(this);
    m_searchLineEdit->setInputMethodHints(Qt::ImhDigitsOnly);
    m_searchLineEdit->setAttribute(Qt::WA_AcceptTouchEvents);
    m_searchButton = new QPushButton("Փնտրել", this);
    m_searchButton->setAttribute(Qt::WA_AcceptTouchEvents);
}

void SearchAbonentWidget::installStyleSheets()
{
    this->setStyleSheet(SCROLLBAR_STYLE_SHEET + RADIO_BUTTON_STYLE_SHEET + LINE_EDIT_STYLE_SHEET + LABEL_STYLE_SHEET + TABLE_WIDGET_STYLE_SHEET + PUSH_BUTTON_STYLE_SHEET);
}

void SearchAbonentWidget::setupLayout()
{
    QHBoxLayout* radioButtonsLayout = new QHBoxLayout();
    radioButtonsLayout->setContentsMargins(0, 0, 0, 0);
    radioButtonsLayout->setSpacing(20);
    radioButtonsLayout->addWidget(m_hashvichRadioButton);
    radioButtonsLayout->addWidget(m_abonhamarRadioButton);
    radioButtonsLayout->addStretch();

    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->setContentsMargins(20, 0, 20, 0);
    searchLayout->setSpacing(20);
    searchLayout->addWidget(m_searchLineEdit);
    searchLayout->addWidget(m_searchButton);

    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(10);
    topLayout->addLayout(radioButtonsLayout);
    topLayout->addLayout(searchLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_detailsWidget);
    mainLayout->addSpacing(10);
    this->setLayout(mainLayout);
}

void SearchAbonentWidget::makeConnections()
{
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, [this](const QString& text){
        m_searchButton->setDisabled(text.isEmpty());
        updateUI();
    });
    connect(m_searchButton, &QPushButton::clicked, this, &SearchAbonentWidget::onSearchButtonClickedSlot);
    connect(m_abonhamarRadioButton, &QRadioButton::toggled, this, [this](){
        m_searchLineEdit->setPlaceholderText("Բաժ. համար");
        updateUI();
    });
    connect(m_hashvichRadioButton, &QRadioButton::toggled, this, [this](){
        m_searchLineEdit->setPlaceholderText("Հաշվիչի համարը");
        updateUI();
    });
}

void SearchAbonentWidget::onSearchButtonClickedSlot()
{
    //m_detailsWidget->updateData(m_searchLineEdit->text(), m_abonhamarRadioButton->isChecked());
    updateUI();
}

void SearchAbonentWidget::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        && m_searchLineEdit->hasFocus()){
        onSearchButtonClickedSlot();
    }
    QWidget::keyReleaseEvent(event);
}

void SearchAbonentWidget::updateUI() {
    QMetaObject::invokeMethod(this, [this]() {
        this->update();
        this->repaint();
        m_abonhamarRadioButton->update();
        m_hashvichRadioButton->update();
        //m_searchLineEdit->setFocus();
        QApplication::processEvents();
    }, Qt::QueuedConnection);
}
