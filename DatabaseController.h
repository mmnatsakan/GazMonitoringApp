#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseController : public QObject
{
public:
    static DatabaseController* instance();
    bool openDatabase();
    void closeDatabase();

    QStringList getTtList();
    QStringList getHskichList(const QString& mkod);

private:
    DatabaseController();
    //remove copy constructor and assignment operator for Singleton
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController& operator=(const DatabaseController&) = delete;
#ifdef ANDROID
    bool copyDatabaseIfNeeded();
#endif

    QSqlDatabase m_db;

};

#endif // DATABASECONTROLLER_H
