QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CucBlankPage.cpp \
    CucBlankTableView.cpp \
    DatabaseController.cpp \
    DetailsWidget.cpp \
    JsonParser.cpp \
    MainWindow.cpp \
    MonitoringPage.cpp \
    MonitoringTableView.cpp \
    SearchAbonentWidget.cpp \
    SqlQueryModel.cpp \
    StartPage.cpp \
    main.cpp

HEADERS += \
    CucBlankPage.h \
    CucBlankTableView.h \
    DatabaseController.h \
    DetailsWidget.h \
    Json/Json.h \
    JsonParser.h \
    MainWindow.h \
    MonitoringPage.h \
    MonitoringTableView.h \
    SearchAbonentWidget.h \
    SqlQueryModel.h \
    StartPage.h \
    UIStyle.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    ANDROID_APP_NAME = "Gaz_Malatya"
    TARGET = Gaz_Malatya
    QT_ANDROID_PACKAGE_NAME = com.MMV.Gaz_Malatya
}


RESOURCES += \
    Resources.qrc

DISTFILES +=

