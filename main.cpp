#include "MainWindow.h"
#include "AndroidHelper.h"
#include "InputDialog.h"

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#ifdef Q_OS_ANDROID
#include <jni.h>
#include <QJniEnvironment>

extern "C" {
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *);
}
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef ANDROID
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    AndroidHelper::applyQtDarkPalette();
    AndroidHelper::forceLandscapeOrientation();
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
    //InputDialog w;
    MainWindow w;
    w.show();
    return a.exec();
}

#ifdef Q_OS_ANDROID
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *)
{
    Q_UNUSED(vm);
    QJniEnvironment env;
    AndroidHelper::registerSpeechResultHandler(env.jniEnv());
    return JNI_VERSION_1_6;
}
#endif
