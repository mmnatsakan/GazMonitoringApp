#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>

struct CucBlankFields{
    CucBlankFields() {}
    QString aah;
    QString hasce;
    QString abonhamar;
    QString hashvichn;
    QString hashtip;
    double hashnaxc;
    double cucmunq;
    double hashxm;
    QString kniqner;
    QString meknab;
};

class DatabaseController : public QObject
{
public:
    static DatabaseController* instance();
#ifdef ANDROID
    void copyDatabaseIfNeeded();
#endif
    bool openDatabase();
    void closeDatabase();

    QStringList getTtList();
    QStringList getHskichList(const QString& mkod);
    QStringList getDateList(const QString& mkod, const QString& hskichkod);
    QList<CucBlankFields> getCucBlankTableData(const QString& mkod, const QString& hskichkod, const QString& grancOr) const;

private:
    DatabaseController();
    //remove copy constructor and assignment operator for Singleton
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController& operator=(const DatabaseController&) = delete;

    QSqlDatabase m_db;

};

#endif // DATABASECONTROLLER_H
