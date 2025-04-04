#include "MainWindow.h"
#include "SearchAbonentWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont appFont = QApplication::font();
    appFont.setFamily("Arial");
    appFont.setStyleStrategy(QFont::PreferAntialias);
    appFont.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(appFont);

    MainWindow w;
    //SearchAbonentWidget w;
    w.show();
    return a.exec();
}
