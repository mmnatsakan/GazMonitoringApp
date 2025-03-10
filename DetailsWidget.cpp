#include "DetailsWidget.h"
#include "JsonParser.h"

#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QBoxLayout>
#include <QEvent>
#include <QScrollBar>
#include <QApplication>
#include <QMouseEvent>
#include <QPushButton>

const int STEP = 5;

DetailsWidget::DetailsWidget(QWidget *parent)
    : QWidget{parent}
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
    QString abonhamar = QString("000000" + searchText).last(6);
    for(const MainData& data : mainDataList){
        if(searchAbonhamar){
            if(data.abonhamar == abonhamar)
                mainData = data;
        }
        else{
            if(data.hashvichn == searchText)
                mainData = data;
        }
    }

    if(mainData.abonhamar == QString()){
        setWidgetsHidden(true);
    }
    else{
        setWidgetsHidden(false);
        m_customerIdLabel->setText(mainData.abonhamar);
        m_nameLabel->setText(mainData.aah);
        m_addressLabel->setText(mainData.hasce);
        m_phoneLabel->setText(mainData.sot_hamar);
        m_hashvichLabel->setText(mainData.hashvich + ", " + mainData.hashvichn);
        m_kniqLabel->setText(mainData.kniq);

        setupTable(mainData.gazQanakList);
    }
}

void DetailsWidget::createMembers()
{
    m_mainWidget = new QWidget(this);
    m_dataWidget = new QWidget(m_mainWidget);

    m_customerIdLabel = new QLabel(m_dataWidget);
    m_nameLabel = new QLabel(m_dataWidget);
    m_addressLabel = new QLabel(m_dataWidget);
    m_phoneLabel = new QLabel(m_dataWidget);
    m_hashvichLabel = new QLabel(m_dataWidget);
    m_kniqLabel = new QLabel(m_dataWidget);
    m_kniqLabel->setWordWrap(true);

    m_tableWidget = new QTableWidget(m_mainWidget);
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels({"Տարի ամիս", "Հաշվեգրում", "Խախտում"});
    m_tableWidget->verticalHeader()->setVisible(false);
    // m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    // m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setShowGrid(true);
    m_tableWidget->setGridStyle(Qt::SolidLine);

    m_noDataLabel = new QLabel("Տվյալները բացակայում են", m_mainWidget);
    m_tableWidget->setDisabled(true);
    m_goUp = new QPushButton(QIcon(":/up_arrow.svg"), "", m_mainWidget);
    m_goDown = new QPushButton(QIcon(":/down_arrow.svg"), "", m_mainWidget);
}

void DetailsWidget::installStyleSheets()
{
    const QString buttonStyle = "QPushButton{border: none; outline: none; color: #000000; font-size: 14px;  font-family: Arial; font-weight: 600; background: transparent; border-radius: 5px; padding: 7px 20px;}";
                                //"QPushButton:hover{background: #02768C;}";
    m_goUp->setStyleSheet(buttonStyle);
    m_goDown->setStyleSheet(buttonStyle);

}

void DetailsWidget::setupLayout()
{
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(10, 10, 10, 10);
    gridLayout->addWidget(new QLabel("Բաժ. համար`", m_dataWidget), 0, 0);
    gridLayout->addWidget(m_customerIdLabel, 0, 1);
    gridLayout->addWidget(new QLabel("Ազգանուն Անուն`", m_dataWidget), 1, 0);
    gridLayout->addWidget(m_nameLabel, 1, 1);
    gridLayout->addWidget(new QLabel("Հասցե`", m_dataWidget), 2, 0);
    gridLayout->addWidget(m_addressLabel, 2, 1);
    gridLayout->addWidget(new QLabel("Հեռախոս`", m_dataWidget), 3, 0);
    gridLayout->addWidget(m_phoneLabel, 3, 1);
    gridLayout->addWidget(new QLabel("Հաշվիչ`", m_dataWidget), 4, 0);
    gridLayout->addWidget(m_hashvichLabel, 4, 1);
    gridLayout->addWidget(new QLabel("Կնիք`", m_dataWidget), 5, 0);
    gridLayout->addWidget(m_kniqLabel, 5, 1);    m_dataWidget->setLayout(gridLayout);

    QHBoxLayout* arrowsLayout = new QHBoxLayout();
    arrowsLayout->setSpacing(0);
    arrowsLayout->setContentsMargins(0, 0, 0, 0);
    arrowsLayout->addStretch();
    arrowsLayout->addWidget(m_goUp);
    arrowsLayout->addWidget(m_goDown);

    QVBoxLayout* mainWidgetLayout = new QVBoxLayout();
    mainWidgetLayout->setSpacing(0);
    mainWidgetLayout->setContentsMargins(0, 0, 0, 10);
    mainWidgetLayout->addWidget(m_noDataLabel, 0, Qt::AlignCenter);
    mainWidgetLayout->addWidget(m_dataWidget);
    mainWidgetLayout->addLayout(arrowsLayout);
    mainWidgetLayout->addWidget(m_tableWidget);
    m_mainWidget->setLayout(mainWidgetLayout);

    QVBoxLayout* thisLayout = new QVBoxLayout();
    thisLayout->setSpacing(0);
    thisLayout->setContentsMargins(0, 0, 0, 0);
    thisLayout->addWidget(m_mainWidget);
    this->setLayout(thisLayout);
}

void DetailsWidget::makeConnections()
{
    connect(m_goUp, &QPushButton::clicked, this, [this](){
        m_tableWidget->verticalScrollBar()->setValue(m_tableWidget->verticalScrollBar()->value() < STEP ? 0 : m_tableWidget->verticalScrollBar()->value() - STEP);
        updateArrows();
        update();
        repaint();
    });
    connect(m_goDown, &QPushButton::clicked, this, [this](){
        int value = m_tableWidget->verticalScrollBar()->maximum();
        m_tableWidget->verticalScrollBar()->setValue(m_tableWidget->verticalScrollBar()->value() > value ? value : m_tableWidget->verticalScrollBar()->value() + STEP);
        updateArrows();
        update();
        repaint();
    });
}

void DetailsWidget::setupTable(const QList<GazQanak> &gazQanakList) {
    int row = 0;
    for (const GazQanak& gazQanak : gazQanakList) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(gazQanak.taram));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(gazQanak.hashxm));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(gazQanak.xaxthash));
        ++row;
    }
    m_goUp->setDisabled(true);
}

void DetailsWidget::setWidgetsHidden(bool isHidden)
{
    m_dataWidget->setHidden(isHidden);
    m_tableWidget->setHidden(isHidden);
    m_goUp->setHidden(isHidden);
    m_goDown->setHidden(isHidden);
    m_noDataLabel->setHidden(!isHidden);
}

void DetailsWidget::updateArrows()
{
    m_goUp->setDisabled(m_tableWidget->verticalScrollBar()->value() <= 0);
    m_goDown->setDisabled(m_tableWidget->verticalScrollBar()->value() >= m_tableWidget->verticalScrollBar()->maximum());
}
