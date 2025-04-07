#include "CheckListTextEditor.h"
#include "Constants.h"
#include "UIStyle.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>

CheckListTextEditor::CheckListTextEditor(QWidget *parent)
    : QDialog{parent}
{
    setMinimumWidth(500);
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();
    setAttribute(Qt::WA_AcceptTouchEvents);
}

void CheckListTextEditor::createMembers()
{
    m_mainWidget = new QWidget(this);
    for (const QString& meknab : MEKNAB_LIST) {
        QCheckBox* checkBox = new QCheckBox(meknab, m_mainWidget);
        m_checkBoxes.append(checkBox);
        connect(checkBox, &QCheckBox::checkStateChanged, this,[=](){
            qDebug() << checkBox->checkState() << " 000000000000000000000000000000000000";
            update();
            repaint();
        });
    }
    m_textEdit = new QTextEdit(m_mainWidget);
    m_textEdit->setPlaceholderText("Մուտքագրել տեքստ...");

    m_acceptButton = new QPushButton("Հաստատել", m_mainWidget);
    m_cancelButton = new QPushButton("Չեղարկել", m_mainWidget);
}

void CheckListTextEditor::installStyleSheets()
{
    this->setStyleSheet("QWidget{background: white;}" + TEXTBOX_STYLE_SHEET + CHECKBOX_STYLE_SHEET + PUSH_BUTTON_STYLE_SHEET);
}

void CheckListTextEditor::setupLayout()
{
    QVBoxLayout* checkBoxesLayout = new QVBoxLayout();
    checkBoxesLayout->setContentsMargins(0, 0, 0, 0);
    checkBoxesLayout->setSpacing(10);
    for(auto& checkBox : m_checkBoxes) {
        checkBoxesLayout->addWidget(checkBox);
    }

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(30);
    buttonsLayout->addWidget(m_acceptButton);
    buttonsLayout->addWidget(m_cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(30);
    mainLayout->addLayout(checkBoxesLayout);
    mainLayout->addWidget(m_textEdit);
    mainLayout->addLayout(buttonsLayout);
    m_mainWidget->setLayout(mainLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->setSpacing(0);
    thisLayout->addWidget(m_mainWidget);
    this->setLayout(thisLayout);

}

void CheckListTextEditor::makeConnections()
{
    connect(m_acceptButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}
#include <QMouseEvent>
#include <QMessageBox>
void CheckListTextEditor::mousePressEvent(QMouseEvent *event)
{
    qDebug() << m_checkBoxes[3]->pos();
    QMessageBox::information(nullptr, "CheckListTextEditor::mousePressEvent", "( " + QString::number(event->pos().x()) + ", " + QString::number(event->pos().y()) + " )");
    QDialog::mousePressEvent(event);
}

void CheckListTextEditor::setData(const QString &data)
{
    for(auto& checkBox : m_checkBoxes) {
        checkBox->setChecked(data.contains(checkBox->text()));
        checkBox->update();
        checkBox->repaint();
    }
    m_textEdit->setText(data.mid(data.indexOf("\n") + 1));
}

QString CheckListTextEditor::getData() const
{
    QStringList selectedOptions;
    for (int i = 0; i < m_checkBoxes.size(); ++i) {
        if (m_checkBoxes[i]->isChecked())
            selectedOptions << m_checkBoxes[i]->text();
    }
    return QString("%1\n%2").arg(selectedOptions.join(" "), m_textEdit->toPlainText());
}


