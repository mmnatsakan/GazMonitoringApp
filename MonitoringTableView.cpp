#include "MonitoringTableView.h"
#include "SqlQueryModel.h"
#include "UIStyle.h"
#include "Constants.h"
#include "CheckListTextEditor.h"
#include "DetailsWidget.h"
#include "NumericDelegate.h"

#include <QHeaderView>
#include <QScrollBar>
#include <QSqlQuery>
#include <QSqlError>
#include <QKeyEvent>
#include <QMouseEvent>

MonitoringTableView::MonitoringTableView(QWidget *parent)
    : QTableView{parent}
{
    m_model = new SqlQueryModel(this);
    installStyleSheets();
    makeConnections();

    setModel(m_model);
}

void MonitoringTableView::updateUiData(const QString& mkod, const QString& hskichkod)
{
    m_mkod = mkod;
    m_hskichkod = hskichkod;

    m_model->clear();
    m_model->setBaseQuery(MONITORING_MODEL_BASE_QUERY +
                          QString(" WHERE mkod = %1 and hskichkod = %2 ").arg(mkod, hskichkod) +
                          " ORDER BY Id", mkod);

    for(int i = 0; i < MONITORING_HEADERS_LIST.count(); ++i){
        m_model->setHeaderData(i, Qt::Horizontal, MONITORING_HEADERS_LIST[i]);
    }

    setColumnWidth(1, 180);
    setColumnWidth(2, 180);
    hideColumn(KNIQNER_COLUMN_INDEX);
    hideColumn(HASHXMNER_COLUMN_INDEX);
//    hideColumn(HASCE_COLUMN_INDEX);
    // NumericDelegate* editor = new NumericDelegate(this);
    // setItemDelegateForColumn(HASHVERC_COLUMN_INDEX, editor);
}

QMap<QString, QString> MonitoringTableView::getInfo() const
{
    QSqlQuery countQuery;
    countQuery.prepare("SELECT sum(iif(hashverc is not null, 1, 0)) as filledCount, COUNT(*) as totalCount FROM cucak "
                       "WHERE mkod = :mkod AND hskichkod = :hskichkod");
    countQuery.bindValue(":mkod", m_mkod);
    countQuery.bindValue(":hskichkod", m_hskichkod);
    qDebug() << countQuery.lastQuery();
    countQuery.exec();

    QMap<QString, QString> infoMap;
    if (countQuery.next()) {
        infoMap["filledCount"] = QString::number(countQuery.value(0).toInt());
        infoMap["totalCount"] =  QString::number(countQuery.value(1).toInt());
    }
    return infoMap;
}

void MonitoringTableView::installStyleSheets()
{
    setAlternatingRowColors(true);
    setMouseTracking(true);
    setWordWrap(true);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    horizontalHeader()->setFixedHeight(50);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
    horizontalHeader()->setStretchLastSection(true);

    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(50);

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    setSelectionBehavior(QTableView::SelectRows);

    verticalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    horizontalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    setStyleSheet(TABLE_VIEW_STYLE_SHEET);
}

void MonitoringTableView::makeConnections()
{
    connect(m_model, &QSqlQueryModel::dataChanged, this, &MonitoringTableView::dataUpdated);
    connect(this, &QTableView::clicked, this, [=](const QModelIndex &index) { edit(index); });
}

void MonitoringTableView::showDetailsWidget(int row)
{
    MainData mainData;
    mainData.abonhamar = m_model->data(m_model->index(row, ABONHAMAR_COLUMN_INDEX), Qt::DisplayRole).toString();
    mainData.aah = m_model->data(m_model->index(row, AAH_COLUMN_INDEX), Qt::DisplayRole).toString();
    mainData.hasce = m_model->data(m_model->index(row, HASCE_COLUMN_INDEX), Qt::DisplayRole).toString();
    mainData.hashvichn = m_model->data(m_model->index(row, HASHVICHN_COLUMN_INDEX), Qt::DisplayRole).toString();
    mainData.hashnaxc = m_model->data(m_model->index(row, HASHNAXC_COLUMN_INDEX), Qt::DisplayRole).toString();
    AmisData amisData;
    QStringList gazList = m_model->data(m_model->index(row, HASHXMNER_COLUMN_INDEX), Qt::DisplayRole).toString().split(";");
    QStringList kniqList = m_model->data(m_model->index(row, KNIQNER_COLUMN_INDEX), Qt::DisplayRole).toString().split(";");
    for(int i = 0; i < gazList.count() - 1; ++i){
        if(!gazList.at(i).isEmpty()){
            QStringList gazQanakData = gazList.at(i).split("_");
            amisData.taram = gazQanakData.at(0);
            amisData.hashxm = gazQanakData.at(1);
            amisData.xaxthash = gazQanakData.at(2);
        }
        if(i < kniqList.count() && !kniqList.at(i).isEmpty()){
            QStringList kniqData = kniqList.at(i).split("_");
            amisData.hashvichn = kniqData.at(1);
            amisData.kniqner = kniqData.at(2);
        }
        mainData.tableDataList << amisData;
    }
    DetailsWidget* dlg = new DetailsWidget(mainData, nullptr);
    dlg->setWindowFlags(Qt::Popup);
    dlg->show();
}

void MonitoringTableView::mouseReleaseEvent(QMouseEvent *event)
{
    QModelIndex currentIndex = indexAt(event->pos());
    if (currentIndex.isValid()) {
        if(currentIndex.column() == MEKNAB_COLUMN_INDEX){
            CheckListTextEditor* dlg = new CheckListTextEditor(nullptr);
            dlg->setData(m_model->data(currentIndex).toString());
            if(dlg->exec() == QDialog::Accepted)
                m_model->setData(currentIndex, dlg->getData(), Qt::EditRole);
            dlg->deleteLater();
            return;
        }
        if(currentIndex.column() == ABONHAMAR_COLUMN_INDEX){
            showDetailsWidget(currentIndex.row());
            return;
        }
        qDebug() << currentIndex << "  0000000000000000000000000000000";
        currentIndex = model()->index(currentIndex.row(), HASHVERC_COLUMN_INDEX);
        selectionModel()->clearSelection();
        selectionModel()->select(currentIndex, QItemSelectionModel::Select | QItemSelectionModel::Current);
        setCurrentIndex(currentIndex);

        qDebug() << currentIndex << "  1111111111111111111111111111111";
        //edit(currentIndex);
    }
    QTableView::mousePressEvent(event);
}
