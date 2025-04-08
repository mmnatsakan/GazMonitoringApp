#include "MainWindow.h"
#include "AndroidController.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef ANDROID
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    AndroidController::applyQtDarkPalette();
    AndroidController::forceLandscapeOrientation();
#endif
    QFont appFont = QApplication::font();
    appFont.setFamily("Arial");
    appFont.setStyleStrategy(QFont::PreferAntialias);
    appFont.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(appFont);

    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
