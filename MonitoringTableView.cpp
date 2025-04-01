#include "MonitoringTableView.h"
#include "SqlQueryModel.h"
#include <UIStyle.h>

#include <QHeaderView>
#include <QScrollBar>
#include <QSqlQuery>
#include <QSqlError>
#include <QKeyEvent>

MonitoringTableView::MonitoringTableView(QWidget *parent)
    : QTableView{parent}
{
    m_model = new SqlQueryModel();

    setMouseTracking(true);
    setWordWrap(true);

    horizontalHeader()->setFixedHeight(50);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    horizontalHeader()->setStretchLastSection(true);
    setSelectionBehavior(QTableView::SelectRows);

    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeader()->setDefaultSectionSize(150);

    verticalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    horizontalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    setAlternatingRowColors(true);
    setStyleSheet(TABLE_VIEW_STYLE_SHEET);

    setModel(m_model);
    connect(m_model, &QSqlQueryModel::dataChanged, this, &MonitoringTableView::dataUpdated);
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

    setColumnWidth(1, 200);
    setColumnWidth(2, 200);
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
    qDebug() << infoMap;
    return infoMap;
}

void MonitoringTableView::clearCell(const QModelIndex &index)
{
    QString fieldName = m_model->headerData(index.column(), Qt::Horizontal).toString();

    // Prepare SQL query
    QSqlQuery query;
    query.prepare(QString("UPDATE cucak SET %1 = NULL WHERE mkod = :mkod AND hskichkod = :hskichkod")
                      .arg(fieldName));

    query.bindValue(":mkod", m_mkod);
    query.bindValue(":hskichkod", m_hskichkod);
    qDebug() << query.lastQuery();

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return;
    }

    m_model->refresh();
}

void MonitoringTableView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QModelIndex currentIndex = this->currentIndex();
        if (currentIndex.isValid()) {
            m_model->setData(currentIndex, QVariant(QVariant::String), Qt::EditRole);
            //clearCell(currentIndex);
        }
    } else {
        QTableView::keyPressEvent(event);
    }
}

