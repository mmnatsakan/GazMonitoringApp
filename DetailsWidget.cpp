#include "DetailsWidget.h"
#include "UIStyle.h"

#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QBoxLayout>
#include <QScrollBar>
#include <QApplication>
#include <QPushButton>
#include <QDebug>


DetailsWidget::DetailsWidget(const MainData &mainData, QWidget *parent)
    : QDialog(parent)
{
    setMinimumWidth(700);
    createMembers();
    installStyleSheets();
    setupLayout();
    updateData(mainData);
}

void DetailsWidget::updateData(const MainData& mainData)
{
        m_tableWidget->setDisabled(false);
        m_customerLabel->setText(mainData.abonhamar + ", " + mainData.aah + ", " +
                                 mainData.hasce + ", Հեռ`0" + mainData.sot_hamar + ", Ցուցմունք՝ " + mainData.hashnaxc);
        m_tableWidget->setUpdatesEnabled(false);
        m_tableWidget->setRowCount(0);
        int rowCount = mainData.tableDataList.size();
        m_tableWidget->setRowCount(rowCount);

        for (int row = 0; row < rowCount; ++row) {
            const AmisData &amisData = mainData.tableDataList[row];

            QTableWidgetItem *item0 = new QTableWidgetItem(amisData.taram);
            item0->setFlags(item0->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            m_tableWidget->setItem(row, 0, item0);
            QTableWidgetItem *item1 = new QTableWidgetItem(amisData.hashxm);
            item1->setFlags(item1->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            m_tableWidget->setItem(row, 1, item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(amisData.xaxthash);
            item2->setFlags(item2->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            m_tableWidget->setItem(row, 2, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(amisData.hashvichn);
            item3->setFlags(item3->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            m_tableWidget->setItem(row, 3, item3);
            QTableWidgetItem *item4 = new QTableWidgetItem(amisData.kniqner);
            item3->setFlags(item4->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
            m_tableWidget->setItem(row, 4, item4);
        }
        m_tableWidget->setUpdatesEnabled(true);
}

void DetailsWidget::createMembers()
{
    m_mainWidget = new QWidget(this);
    m_customerLabel = new QLabel(m_mainWidget);
    m_customerLabel->setWordWrap(true);

    m_tableWidget = new QTableWidget(m_mainWidget);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ "Տարամ", "գազ", "Խախտ", "Հաշվիչ", "Կնիքներ" });
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->setShowGrid(true);
    m_tableWidget->setGridStyle(Qt::SolidLine);
    m_tableWidget->setWordWrap(true);
    m_tableWidget->setMouseTracking(true);


    m_tableWidget->setDisabled(true);
}

void DetailsWidget::installStyleSheets()
{
    m_customerLabel->setStyleSheet(LABEL_STYLE_SHEET);
    m_tableWidget->setStyleSheet(TABLE_WIDGET_STYLE_SHEET + SCROLLBAR_STYLE_SHEET);
}

void DetailsWidget::setupLayout()
{
    QVBoxLayout* mainWidgetLayout = new QVBoxLayout();
    mainWidgetLayout->setSpacing(20);
    mainWidgetLayout->setContentsMargins(10, 10, 10, 10);
    mainWidgetLayout->addWidget(m_customerLabel);
    mainWidgetLayout->addWidget(m_tableWidget);
    m_mainWidget->setLayout(mainWidgetLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setSpacing(0);
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->addWidget(m_mainWidget);
    setLayout(thisLayout);
}
