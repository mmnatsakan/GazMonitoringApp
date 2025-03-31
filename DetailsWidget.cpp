#include "DetailsWidget.h"
#include "JsonParser.h"

#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QBoxLayout>
#include <QScrollBar>
#include <QApplication>
#include <QPushButton>
#include <QDebug>

//const int STEP = 5;

DetailsWidget::DetailsWidget(QWidget *parent)
    : QWidget(parent)
{
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();
    setWidgetsHidden(true);
}

void DetailsWidget::updateData(const QString &searchText, bool searchAbonhamar)
{
    MainData mainData;
    QList<MainData> mainDataList = JsonParser::instance()->getMainData();

    // Use explicit formatting for a 6-digit number with leading zeros.
    QString formattedAbonhamar;
    if (searchAbonhamar) {
        bool ok = false;
        int number = searchText.toInt(&ok);
        if (ok) {
            formattedAbonhamar = QString("%1").arg(number, 6, 10, QLatin1Char('0'));
        } else {
            // Fallback to original logic if conversion fails.
            formattedAbonhamar = QString("000000" + searchText).right(6);
        }
    }

    // Loop through mainDataList and exit early when a match is found.
    for (const MainData &data : mainDataList) {
        if (searchAbonhamar) {
            if (data.abonhamar == formattedAbonhamar) {
                mainData = data;
                break;
            }
        } else {
            if (data.hashvichn == searchText) {
                mainData = data;
                break;
            }
        }
    }

    if (mainData.abonhamar.isEmpty()) {
        setWidgetsHidden(true);
    } else {
        setWidgetsHidden(false);
        // Enable the table widget for interaction when data is available.
        m_tableWidget->setDisabled(false);
        m_customerLabel->setText(mainData.abonhamar + ", " + mainData.aah + ", " +
                                 mainData.hasce + ", Հեռ`0" + mainData.sot_hamar + ", Ցուցմունք՝ " + mainData.hashnaxc);
        setupTable(mainData.tableDataList);
    }
}

void DetailsWidget::createMembers()
{
    m_mainWidget = new QWidget(this);
    m_customerLabel = new QLabel(m_mainWidget);
    m_customerLabel->setWordWrap(true);

    m_tableWidget = new QTableWidget(m_mainWidget);
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels({"Տարամ", "գազ", "Խախտ", "Հաշվիչ\nԿնիքներ"});
    m_tableWidget->verticalHeader()->setVisible(false);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->setShowGrid(true);
    m_tableWidget->setGridStyle(Qt::SolidLine);
    m_tableWidget->setWordWrap(true);

    m_noDataLabel = new QLabel("Տվյալները բացակայում են", m_mainWidget);
    m_tableWidget->setDisabled(true);
    // m_goUp = new QPushButton(QIcon(":/up_arrow.svg"), "", m_mainWidget);
    // m_goDown = new QPushButton(QIcon(":/down_arrow.svg"), "", m_mainWidget);
}

void DetailsWidget::installStyleSheets()
{
    const QString buttonStyle =
        "QPushButton {"
        "    border: none; "
        "    outline: none; "
        "    color: #000000; "
        "    font-size: 14px; "
        "    font-family: Arial; "
        "    font-weight: 600; "
        "    background: transparent; "
        "    border-radius: 5px; "
        "    padding: 7px 20px;"
        "}";
    // m_goUp->setStyleSheet(buttonStyle);
    // m_goDown->setStyleSheet(buttonStyle);
}

void DetailsWidget::setupLayout()
{
    // QHBoxLayout* arrowsLayout = new QHBoxLayout();
    // arrowsLayout->setSpacing(0);
    // arrowsLayout->setContentsMargins(0, 0, 0, 0);
    // arrowsLayout->addStretch();
    // arrowsLayout->addWidget(m_goUp);
    // arrowsLayout->addWidget(m_goDown);

    QVBoxLayout* mainWidgetLayout = new QVBoxLayout();
    mainWidgetLayout->setSpacing(0);
    mainWidgetLayout->setContentsMargins(0, 0, 0, 10);
    mainWidgetLayout->addWidget(m_noDataLabel, 0, Qt::AlignCenter);
    mainWidgetLayout->addWidget(m_customerLabel);
    // mainWidgetLayout->addLayout(arrowsLayout);
    mainWidgetLayout->addWidget(m_tableWidget);
    m_mainWidget->setLayout(mainWidgetLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setSpacing(0);
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->addWidget(m_mainWidget);
    setLayout(thisLayout);
}

void DetailsWidget::makeConnections()
{
    // connect(m_goUp, &QPushButton::clicked, this, [this]() {
    //     int newValue = m_tableWidget->verticalScrollBar()->value() - STEP;
    //     m_tableWidget->verticalScrollBar()->setValue(qMax(0, newValue));
    //     updateArrows();
    // });

    // connect(m_goDown, &QPushButton::clicked, this, [this]() {
    //     int newValue = m_tableWidget->verticalScrollBar()->value() + STEP;
    //     m_tableWidget->verticalScrollBar()->setValue(qMin(newValue, m_tableWidget->verticalScrollBar()->maximum()));
    //     updateArrows();
    // });
}

void DetailsWidget::setupTable(const QList<AmisData> &tableDataList)
{
    m_tableWidget->setUpdatesEnabled(false);
    m_tableWidget->setRowCount(0); // Clear previous rows

    int rowCount = tableDataList.size();
    m_tableWidget->setRowCount(rowCount); // Preallocate rows

    for (int row = 0; row < rowCount; ++row) {
        const AmisData &amisData = tableDataList[row];

        QTableWidgetItem *item0 = new QTableWidgetItem(amisData.taram);
        item0->setFlags(item0->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
        m_tableWidget->setItem(row, 0, item0);
        QTableWidgetItem *item1 = new QTableWidgetItem(amisData.hashxm);
        item1->setFlags(item1->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
        m_tableWidget->setItem(row, 1, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem(amisData.xaxthash);
        item2->setFlags(item2->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
        m_tableWidget->setItem(row, 2, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(amisData.hashvichn + "\n" + amisData.kniqner);
        item3->setFlags(item3->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEnabled));
        m_tableWidget->setItem(row, 3, item3);
    }
    m_tableWidget->setUpdatesEnabled(true);
    // m_goUp->setDisabled(true);
}

void DetailsWidget::setWidgetsHidden(bool isHidden)
{
    m_tableWidget->setHidden(isHidden);
    // m_goUp->setHidden(isHidden);
    // m_goDown->setHidden(isHidden);
    m_noDataLabel->setHidden(!isHidden);
}

void DetailsWidget::updateArrows()
{
    // m_goUp->setDisabled(m_tableWidget->verticalScrollBar()->value() <= 0);
    // m_goDown->setDisabled(m_tableWidget->verticalScrollBar()->value() >= m_tableWidget->verticalScrollBar()->maximum());
}
