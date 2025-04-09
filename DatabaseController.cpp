#include "DatabaseController.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QApplication>

#ifdef ANDROID
    #include <QJniObject>
    #include <QJniEnvironment>
#endif

DatabaseController *DatabaseController::instance()
{
    static DatabaseController* instance = nullptr;
    if(!instance){
        instance = new DatabaseController;
    }
    return instance;
}

#ifdef ANDROID
bool DatabaseController::copyDatabaseIfNeeded() {
    QString fileName = "Monitoring.sqlite";
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString destFile = appDataPath + "/" + fileName;

    if (QFile::exists(destFile)) {
        if(QMessageBox::question(nullptr, "Database exists.", "Remove existing database?") == QMessageBox::No){
            return true;
        }
        else if (!QFile::remove(destFile)) {
            QMessageBox::information(nullptr, "Failed to remove existing file:", destFile);
            qDebug() << "Failed to remove existing file:" << destFile;
            return false;
        }
    }

    QDir dir;
    if (!dir.exists(appDataPath)) {
        if (!dir.mkpath(appDataPath)) {
            QMessageBox::information(nullptr, "Failed to create directory:", appDataPath);
            qDebug() << "Failed to create directory:" << appDataPath;
            return false;
        }
    }

    QString sourceFile = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + fileName;
    if (!QFile::exists(sourceFile)) {
        QMessageBox::information(nullptr, "Error", "Source database does not exist.");
        return false;
    }
    if (!QFile::copy(sourceFile, destFile)) {
        QMessageBox::information(nullptr, "Failed to copy file.", sourceFile + " *** " + destFile);
        return false;
    }
    return true;
}

void requestPermission(const QString &permissionStr, int requestCode = 1234)
{
    QMessageBox::information(nullptr, "File succes000000000000000000sfully copied from", "sourceFile");

    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;"
        );

    QJniEnvironment env;
    jobjectArray permissionsArray = env->NewObjectArray(1,
                                                        env->FindClass("java/lang/String"),
                                                        env->NewStringUTF(permissionStr.toUtf8().constData()));

    QJniObject::callStaticMethod<void>(
        "androidx/core/app/ActivityCompat",
        "requestPermissions",
        "(Landroid/app/Activity;[Ljava/lang/String;I)V",
        activity.object(),
        permissionsArray,
        requestCode
        );
}
#endif

bool DatabaseController::openDatabase() {
#ifdef ANDROID
    // if(!copyDatabaseIfNeeded())
    //     QApplication::quit();
    //QString writablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFilePath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/Monitoring.sqlite";
#else
    QString dbFilePath = "D:/Monitoring.sqlite";

#endif

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbFilePath);

    if (!m_db.open()) {
        //QMessageBox::information(nullptr, "Error opening database:", m_db.lastError().text());
        qWarning() << "Error opening database:" << m_db.lastError().text();
        return false;
    } else {
        //QMessageBox::information(nullptr, "Database opened successfully.", dbFilePath);
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
        QMessageBox::information(nullptr, "Query execution failed:", query.lastError().text());
        qWarning() << "Query execution failed:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        dataList << query.value(0).toString();
    }
    //QMessageBox::information(nullptr, "Query execution!:", "OKOKOKOKOKOKOKOKOK");

    return dataList;
}

QStringList DatabaseController::getHskichList(const QString &mkod)
{
    QStringList dataList;
    QSqlQuery query;
    query.prepare(QString("SELECT %1 || '_' || %2 as name FROM %3 a "
                          " INNER JOIN (select distinct mkod, hskichkod from %4) b on a.mkod = b.mkod and a.kod = b.hskichkod "
                          " where a.mkod = %5").arg("kod", "anun", "Hskich", "cucak", mkod));

    if (!query.exec()) {
        QMessageBox::information(nullptr, "HSKICH Query execution failed:", query.lastError().text());
        qWarning() << "Query execution failed:" << query.lastError().text();
        return dataList;
    }

    while (query.next()) {
        dataList << query.value(0).toString();
    }
    //QMessageBox::information(nullptr, "HSKICH Query execution!:", "OKOKOKOKOKOKOKOKOK");

    return dataList;
}

DatabaseController::DatabaseController()
{
}
