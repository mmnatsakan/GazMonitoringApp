#include "DatabaseController.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

DatabaseController *DatabaseController::instance()
{
    static DatabaseController* instance = nullptr;
    if(!instance){
        instance = new DatabaseController;
    }
    return instance;
}

#ifdef ANDROID
void DatabaseController::copyDatabaseIfNeeded() {
    QString writablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << writablePath << "  0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    QString dbFilePath = writablePath + "/mydb.db";

    if (!QFile::exists(dbFilePath)) {
        QDir dir;
        if (!dir.mkpath(writablePath)) {
            qWarning() << "Failed to create directory:" << writablePath;
            return;
        }

        QFile resourceFile(":/databases/mydb.db");
        if (!resourceFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open resource database file.";
            return;
        }

        QFile newFile(dbFilePath);
        if (!newFile.open(QIODevice::WriteOnly)) {
            qWarning() << "Failed to open new database file for writing:" << dbFilePath;
            return;
        }

        newFile.write(resourceFile.readAll());
        newFile.close();
        resourceFile.close();

        qDebug() << "Database copied to:" << dbFilePath;
    } else {
        qDebug() << "Database already exists at:" << dbFilePath;
    }
}
#endif

bool DatabaseController::openDatabase() {
#ifdef ANDROID
    copyDatabaseIfNeeded();
    QString writablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFilePath = writablePath + "/mydb.db";
#else
    QString dbFilePath = "D:/CucBlank_11.sqlite";

#endif

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFilePath);

    if (!db.open()) {
        qWarning() << "Error opening database:" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Database opened successfully.";
        return true;
    }
}

void DatabaseController::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

QStringList DatabaseController::getTtList()
{
    QStringList dataList;
    QSqlQuery query;
    query.prepare(QString("SELECT %1 || '_' || %2 as name FROM %3").arg("kod", "anun", "Tt"));

    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        dataList << query.value(0).toString();
    }

    return dataList;
}

QStringList DatabaseController::getHskichList(const QString &mkod)
{
    QStringList dataList;
    QSqlQuery query;
    query.prepare(QString("SELECT %1 || '_' || %2 as name FROM %3 a "
                          " INNER JOIN (select distinct mkod, hskichkod from %4) b on a.mkod = b.mkod and a.kod = b.hskichkod "
                          " where a.mkod = %5").arg("kod", "anun", "Hskich", "cucblank", mkod));

    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        dataList << query.value(0).toString();
    }

    return dataList;
}

QStringList DatabaseController::getDateList(const QString &mkod, const QString &hskichkod)
{
    QStringList dataList;
    QSqlQuery query;
    query.prepare(QString("SELECT distinct substr(%1, 1, 10) || ' (Գույք. օր ' || %2 || ')'  as name FROM %3 where mkod = %4 and hskichkod = %5 order by %2").arg( "dat_or", "granc_or", "Cucblank", mkod, hskichkod));

    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        dataList << query.value(0).toString();
    }

    return dataList;
}

DatabaseController::DatabaseController()
{
}
