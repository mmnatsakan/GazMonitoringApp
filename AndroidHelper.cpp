#include "AndroidHelper.h"
#include "AndroidBridge.h"

#include <QApplication>
#include <QPalette>
#include <QStyle>
#include <QDebug>

#ifdef ANDROID
#include <QJniObject>
#include <jni.h>
extern "C" JNIEXPORT void JNICALL
Java_org_qtproject_example_GazMonitoringApp_SpeechResultHandler_onSpeechResult(JNIEnv *env, jobject obj, jstring result);
#endif

namespace AndroidHelper {

bool isDarkModeActive()
{
#ifdef ANDROID
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");
    if (!activity.isValid()) return false;

    QJniObject resources = activity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
    QJniObject config = resources.callObjectMethod("getConfiguration", "()Landroid/content/res/Configuration;");
    jint uiMode = config.getField<jint>("uiMode");

    const int UI_MODE_NIGHT_MASK = 0x30;
    const int UI_MODE_NIGHT_YES = 0x20;

    return (uiMode & UI_MODE_NIGHT_MASK) == UI_MODE_NIGHT_YES;
#else
    return false;
#endif
}

void setDarkMode(bool enable)
{
#ifdef ANDROID
    int mode = enable ? 2 /* MODE_NIGHT_YES */ : 1 /* MODE_NIGHT_NO */;
    QJniObject::callStaticMethod<void>(
        "androidx/appcompat/app/AppCompatDelegate",
        "setDefaultNightMode",
        "(I)V",
        mode);
#endif
}

void applyQtDarkPalette()
{
#ifdef ANDROID
    QPalette palette;

    if (isDarkModeActive()) {
        palette.setColor(QPalette::Window, QColor(53, 53, 53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(42, 42, 42));
        palette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53, 53, 53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
    } else {
        palette = QApplication::style()->standardPalette();
    }

    qApp->setPalette(palette);
#endif
}

void forceLandscapeOrientation()
{
#ifdef ANDROID
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");
    if (activity.isValid()) {
        activity.callMethod<void>("setRequestedOrientation", "(I)V", 0); // Landscape
    }
#endif
}

void forceShowKeyboard()
{
#ifdef ANDROID
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");

    if (!activity.isValid())
        return;

    QJniObject inputMethodManager = activity.callObjectMethod(
        "getSystemService",
        "(Ljava/lang/String;)Ljava/lang/Object;",
        QJniObject::fromString("input_method").object<jstring>());

    QJniObject currentFocus = activity.callObjectMethod("getCurrentFocus", "()Landroid/view/View;");

    if (inputMethodManager.isValid() && currentFocus.isValid()) {
        inputMethodManager.callMethod<jboolean>(
            "showSoftInput",
            "(Landroid/view/View;I)Z",
            currentFocus.object<jobject>(),
            0
            );
    }
#endif
}


void startVoiceInput()
{
#ifdef ANDROID
    qDebug() << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM";
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");
    if (activity.isValid()) {
        QJniObject::callStaticMethod<void>(
            "org/qtproject/example/GazMonitoringApp/SpeechRecognizerHelper",
            "init",
            "(Landroid/app/Activity;)V",
            activity.object<jobject>());
        QJniObject::callStaticMethod<void>(
            "org/qtproject/example/GazMonitoringApp/SpeechRecognizerHelper",
            "startListening",
            "()V");
    }
#endif
}

void registerSpeechResultHandler(void* env)
{
    qDebug() << "77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777";
#ifdef ANDROID
    JNIEnv* e = static_cast<JNIEnv*>(env);
    JNINativeMethod methods[] = {
        {"onSpeechResult", "(Ljava/lang/String;)V", reinterpret_cast<void*>(
                                                        Java_org_qtproject_example_GazMonitoringApp_SpeechResultHandler_onSpeechResult)}
    };
    jclass clazz = e->FindClass("org/qtproject/example/GazMonitoringApp/SpeechResultHandler");
    if (clazz) {
        e->RegisterNatives(clazz, methods, 1);
    } else {
        qWarning() << "Failed to find SpeechResultHandler class";
    }
#endif
}


void speechReceivedCallback(const QString &text)
{
    qDebug() << "[AndroidHelper] Recognized Armenian Speech:" << text << "  88888888888888888888888888888888888888888888888888888";
    emit AndroidBridge::instance()->speechRecognized(text);
}

#ifdef ANDROID
extern "C" JNIEXPORT void JNICALL
Java_org_qtproject_example_GazMonitoringApp_SpeechResultHandler_onSpeechResult(JNIEnv *env, jobject /*obj*/, jstring result)
{
    const char *chars = env->GetStringUTFChars(result, nullptr);
    QString recognizedText = QString::fromUtf8(chars);
    env->ReleaseStringUTFChars(result, chars);
    qDebug() << "00000000000000000000000000000000000000000000000000000000000000000000000000000";
    speechReceivedCallback(recognizedText);
}
#endif

}
