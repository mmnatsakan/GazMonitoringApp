QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AndroidBridge.cpp \
    AndroidHelper.cpp \
    CheckListTextEditor.cpp \
    CustomTextEdit.cpp \
    CustomWidgets/BaseKeyboard.cpp \
    CustomWidgets/CustomKeyboard.cpp \
    CustomWidgets/ExtendedSymbolsKeyboard.cpp \
    CustomWidgets/KeyboardFactory.cpp \
    CustomWidgets/LowerLettersKeyboard.cpp \
    CustomWidgets/MainSymbolsKeyboard.cpp \
    CustomWidgets/NumpadKeyboard.cpp \
    CustomWidgets/UpperLettersKeyboard.cpp \
    DatabaseController.cpp \
    DetailsWidget.cpp \
    InputDialog.cpp \
    MainWindow.cpp \
    MonitoringPage.cpp \
    MonitoringTableView.cpp \
    NumericDelegate.cpp \
    SqlQueryModel.cpp \
    StartPage.cpp \
    main.cpp

HEADERS += \
    AndroidBridge.h \
    AndroidHelper.h \
    CheckListTextEditor.h \
    Constants.h \
    CustomTextEdit.h \
    CustomWidgets/BaseKeyboard.h \
    CustomWidgets/CustomKeyboard.h \
    CustomWidgets/ExtendedSymbolsKeyboard.h \
    CustomWidgets/KeyboardFactory.h \
    CustomWidgets/LowerLettersKeyboard.h \
    CustomWidgets/MainSymbolsKeyboard.h \
    CustomWidgets/NumpadKeyboard.h \
    CustomWidgets/UpperLettersKeyboard.h \
    DatabaseController.h \
    DetailsWidget.h \
    InputDialog.h \
    MainWindow.h \
    MonitoringPage.h \
    MonitoringTableView.h \
    NumericDelegate.h \
    SqlQueryModel.h \
    StartPage.h \
    UIStyle.h \
    Utils.h

# ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
# ANDROID_EXTRA_LIBS = $$OUT_PWD/libGazMonitoringApp_arm64-v8a.so
# QMAKE_LFLAGS += -Wl,-soname,libGazMonitoringApp_arm64-v8a.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/libs.xml \
    android/res/xml/qtprovider_paths.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

