#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef ANDROID
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QFont appFont = QApplication::font();
    appFont.setFamily("Arial");
    appFont.setStyleStrategy(QFont::PreferAntialias);
    appFont.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(appFont);

    MainWindow w;
    w.show();
    return a.exec();
}
