#include "MainWindow.h"
#include "AndroidController.h"

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
#ifdef ANDROID
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    AndroidController::applyQtDarkPalette();
    AndroidController::forceLandscapeOrientation();
#endif
    QScreen *screen = a.primaryScreen();
    qDebug() << "DPI:" << screen->logicalDotsPerInch();
    qDebug() << "Physical DPI:" << screen->physicalDotsPerInch();
    qDebug() << "Device Pixel Ratio:" << screen->devicePixelRatio();
    qDebug() << "Screen Geometry:" << screen->geometry();

    QFont appFont = QApplication::font();
    appFont.setFamily("Arial");
    appFont.setStyleStrategy(QFont::PreferAntialias);
    appFont.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(appFont);

    MainWindow w;
    w.show();
    return a.exec();
}
