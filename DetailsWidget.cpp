#include "DetailsWidget.h"
#include "JsonParser.h"
#include "CustomTableWidget.h"

#include <QLabel>
#include <QHeaderView>
#include <QBoxLayout>
#include <QEvent>
#include <QScroller>
#include <QScrollBar>


DetailsWidget::DetailsWidget(QWidget *parent)
    : QWidget{parent}
{
    createMembers();
    installStyleSheets();
    setupLayout();
    makeConnections();
    setWidgetsHidden(true);
    m_tableWidget->verticalScrollBar()->installEventFilter(this);
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

    m_tableWidget = new CustomTableWidget(m_mainWidget);

    m_noDataLabel = new QLabel("Տվյալները բացակայում են", m_mainWidget);
}

void DetailsWidget::installStyleSheets()
{

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
    m_dataWidget->setLayout(gridLayout);

    QVBoxLayout* mainWidgetLayout = new QVBoxLayout();
    mainWidgetLayout->setSpacing(0);
    mainWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mainWidgetLayout->addWidget(m_noDataLabel, 0, Qt::AlignCenter);
    mainWidgetLayout->addWidget(m_dataWidget);
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

}

void DetailsWidget::setupTable(const QList<GazQanak> &gazQanakList) {
    m_tableWidget->setUpdatesEnabled(false);
    m_tableWidget->clearContents();
    m_tableWidget->setRowCount(gazQanakList.size());

    int row = 0;
    for (const GazQanak& gazQanak : gazQanakList) {
        //m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(gazQanak.taram));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(gazQanak.hashxm));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(gazQanak.xaxthash));
        ++row;
    }
    m_tableWidget->setUpdatesEnabled(true);
}

void DetailsWidget::setWidgetsHidden(bool isHidden)
{
    m_dataWidget->setHidden(isHidden);
    m_tableWidget->setHidden(isHidden);
    m_noDataLabel->setHidden(!isHidden);
}

bool DetailsWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_tableWidget->verticalScrollBar())
        if (event->type() == QEvent::Wheel)
            qDebug() << event->type();

    return QWidget::eventFilter(watched, event);
}
