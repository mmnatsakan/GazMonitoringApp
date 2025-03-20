#include "CucBlankTableView.h"
#include "SqlQueryModel.h"
#include <UIStyle.h>

#include <QHeaderView>
#include <QScrollBar>
#include <QSqlQuery>
#include <QSqlError>

CucBlankTableView::CucBlankTableView(QWidget *parent)
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

    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(50);

    verticalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);
    horizontalScrollBar()->setStyleSheet(SCROLLBAR_STYLE_SHEET);

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    setAlternatingRowColors(true);
    setStyleSheet(TABLE_VIEW_STYLE_SHEET);

    setModel(m_model);
    connect(m_model, &QSqlQueryModel::dataChanged, this, &CucBlankTableView::dataUpdated);
}

void CucBlankTableView::updateUiData(const QString& mkod, const QString& hskichkod, const QString& grancOr)
{
    m_mkod = mkod;
    m_hskichkod = hskichkod;
    m_grancOr = grancOr;

    m_model->clear();
    //m_model->setFilter(QString("mkod = %1 and hskichkod = %2 and granc_or = %3").arg(mkod, hskichkod, grancOr));
    //m_model->setSort("mkod, hert, bnakvajr, poxoc, tun, bnakaran, abonhamar, hashvichn");
    m_model->setBaseQuery(MODEL_BASE_QUERY +
                          QString(" WHERE mkod = %1 and hskichkod = %2 and granc_or = %3").arg(mkod, hskichkod, grancOr) +
                          " ORDER BY mkod, hert, bnakvajr, poxoc, tun, bnakaran, abonhamar, hashvichn", mkod);

    for(int i = 0; i < HEADERS_LIST.count(); ++i){
        m_model->setHeaderData(i, Qt::Horizontal, HEADERS_LIST[i]);
    }

    setColumnWidth(0, 200);
    setColumnWidth(1, 200);
}

QMap<QString, QString> CucBlankTableView::getInfo() const
{
    QSqlQuery countQuery;
    countQuery.prepare("SELECT sum(iif(hashverc is not null, 1, 0)) as filledCount, COUNT(*) as totalCount, sum(hashxm) as totalHashxm FROM cucBlank "
                       "WHERE mkod = :mkod AND hskichkod = :hskichkod AND granc_or = :grancOr");
    countQuery.bindValue(":mkod", m_mkod);
    countQuery.bindValue(":hskichkod", m_hskichkod);
    countQuery.bindValue(":grancOr", m_grancOr);
    countQuery.exec();

    QMap<QString, QString> infoMap;
    if (countQuery.next()) {
        infoMap["filledCount"] = QString::number(countQuery.value(0).toInt());
        infoMap["totalCount"] =  QString::number(countQuery.value(1).toInt());
        infoMap["totalHashxm"] = QString::number(countQuery.value(2).toDouble(), 'f', 2);
    }
    return infoMap;
}

