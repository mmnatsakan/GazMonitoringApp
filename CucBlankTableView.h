#ifndef CUCBLANKTABLEVIEW_H
#define CUCBLANKTABLEVIEW_H

#include <QTableView>

class SqlQueryModel;


class CucBlankTableView : public QTableView
{
    Q_OBJECT
public:
    explicit CucBlankTableView(QWidget *parent = nullptr);
    void updateUiData(const QString& mkod, const QString& hskichkod, const QString& grancOr);
    QMap<QString, QString> getInfo() const;


private:
    SqlQueryModel* m_model;

    QString m_mkod;
    QString m_hskichkod;
    QString m_grancOr;

signals:
    void dataUpdated(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QList<int> &roles = QList<int>());
};

inline const QStringList HEADERS_LIST = {
    "Ազգանուն Անունը", "Հասցեն", "Բաժ.\nհամարը", "Հաշվիչի\nհամարը", "Հաշվիչի\nտիպը",
    "Նախկին\nցուցմունքը", "Առկա\nցուցմունքը", "Տարբե-\nրություն", "Կնիքներ", "Մեկնաբա-\nնություն"
};

inline const QString MODEL_BASE_QUERY = "SELECT TRIM(aah) AS aah, TRIM(hasce) AS hasce, abonhamar, TRIM(hashvichn) AS hashvichn, "
                                        "TRIM(hash_tes) AS hash_tes, hashnaxc, hashverc, hashxm, TRIM(kniq_n) AS kniq_n, meknab "
                                        "FROM cucBlank ";

#endif // CUCBLANKTABLEVIEW_H
