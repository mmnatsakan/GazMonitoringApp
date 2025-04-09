#include "MonitoringTableView.h"
#include "SqlQueryModel.h"
#include "UIStyle.h"
#include "Constants.h"
#include "CheckListTextEditor.h"
#include "DetailsWidget.h"
#include "NumericDelegate.h"

#include <QHeaderView>
#include <QScrollBar>
#include <QScroller>
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
    m_model->clear();
    m_model->setMkodHskichkod(mkod, hskichkod);

    for(int i = 0; i < MONITORING_HEADERS_LIST.count(); ++i){
        m_model->setHeaderData(i, Qt::Horizontal, MONITORING_HEADERS_LIST[i]);
    }

    setColumnWidth(AAH_COLUMN_INDEX, 150);
    setColumnWidth(HASCE_COLUMN_INDEX, 180);
    hideColumn(KNIQNER_COLUMN_INDEX);
    hideColumn(HASHXMNER_COLUMN_INDEX);
//    hideColumn(HASCE_COLUMN_INDEX);
    // NumericDelegate* editor = new NumericDelegate(this);
    // setItemDelegateForColumn(HASHVERC_COLUMN_INDEX, editor);
}

QMap<QString, QString> MonitoringTableView::getCountsInfo() const
{
    return m_model->getCountsInfo();
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
        if(currentIndex.column() == ABONHAMAR_COLUMN_INDEX || currentIndex.column() == HASHVICHN_COLUMN_INDEX){
            DetailsWidget* dlg = new DetailsWidget(m_model->getDetails(m_model->data(currentIndex, Qt::DisplayRole).toString(), currentIndex.column() == ABONHAMAR_COLUMN_INDEX), nullptr);
            dlg->setWindowFlags(Qt::Popup);
            dlg->show();
            return;
        }
        qDebug() << currentIndex << "  0000000000000000000000000000000";
        currentIndex = model()->index(currentIndex.row(), HASHVERC_COLUMN_INDEX);
        selectionModel()->clearSelection();
        selectionModel()->select(currentIndex, QItemSelectionModel::Select | QItemSelectionModel::Current);
        setCurrentIndex(currentIndex);

        qDebug() << currentIndex << "  1111111111111111111111111111111";
        edit(currentIndex);
    }
    QTableView::mousePressEvent(event);
}
