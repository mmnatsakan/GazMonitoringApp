#include "MonitoringTableView.h"
#include "SqlQueryModel.h"
#include "UIStyle.h"
#include "Constants.h"
#include "CheckListTextEditor.h"
#include "DetailsWidget.h"
#include "InputDialog.h"
#include "NumericDelegate.h"

#include <QHeaderView>
#include <QScrollBar>
#include <QScroller>
#include <QSqlQuery>
#include <QSqlError>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QInputDialog>

MonitoringTableView::MonitoringTableView(QWidget *parent)
    : QTableView{parent}
{
    m_model = new SqlQueryModel(this);
    installStyleSheets();
    makeConnections();

    setModel(m_model);
}

void MonitoringTableView::setTableData(const QString& mkod, const QString& hskichkod)
{
    m_model->clear();

    for(int i = 0; i < MONITORING_HEADERS_LIST.count(); ++i){
        m_model->setHeaderData(i, Qt::Horizontal, MONITORING_HEADERS_LIST[i]);
    }
    m_model->setMkodHskichkod(mkod, hskichkod);

    setColumnWidth(AAH_COLUMN_INDEX, 140);
    setColumnWidth(HASCE_COLUMN_INDEX, 150);

    hideColumn(KNIQNER_COLUMN_INDEX);
    hideColumn(HASHXMNER_COLUMN_INDEX);
    hideColumn(PRIZ_STUG_COLUMN_INDEX);
    // NumericDelegate* editor = new NumericDelegate(this);
    // setItemDelegateForColumn(HASHVERC_COLUMN_INDEX, editor);
}

void MonitoringTableView::refresh(bool removeFilter)
{
    m_model->refresh(removeFilter);
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
    //verticalHeader()->setFixedWidth(50);

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    setSelectionBehavior(QTableView::SelectRows);

    verticalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    horizontalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    setStyleSheet(TABLE_VIEW_STYLE_SHEET);
}

void MonitoringTableView::makeConnections()
{
    connect(m_model, &SqlQueryModel::filledRowsCountsChanged, this, &MonitoringTableView::filledRowsCountsChanged);
    connect(this, &QTableView::clicked, this, [=](const QModelIndex &index) { edit(index); });
    connect(horizontalHeader(), &QHeaderView::sectionClicked, this, &MonitoringTableView::onHorizontalHeaderSectionClickedSlot);
}

void MonitoringTableView::showDetails(const QString &value, bool searchByAbonhamar)
{
    DetailsWidget* dlg = new DetailsWidget(m_model->getDetails(value, searchByAbonhamar), this);
    dlg->showFullScreen();
}

void MonitoringTableView::onHorizontalHeaderSectionClickedSlot(int section)
{
    if(section == ABONHAMAR_COLUMN_INDEX || section == HASHVICHN_COLUMN_INDEX){
        bool searchByAbonhamar = section == ABONHAMAR_COLUMN_INDEX;
        InputDialog dlg(this);
        dlg.setLabelText(searchByAbonhamar ? "Մուտքագրել բաժանորդային համարը" : "Մուտքագրել հաշվիչի համարը");
        if (dlg.exec() == QDialog::Accepted) {
            showDetails(dlg.getTextValue(), searchByAbonhamar);
        }
    }
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
            showDetails(m_model->data(currentIndex, Qt::DisplayRole).toString(), currentIndex.column() == ABONHAMAR_COLUMN_INDEX);
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
