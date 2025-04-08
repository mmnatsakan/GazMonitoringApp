#include "AndroidController.h"

#include <QApplication>
#include <QPalette>
#include <QStyle>

#ifdef ANDROID
#include <QJniObject>
#endif

namespace AndroidController {

    bool isDarkModeActive()
    {
    #ifdef ANDROID
        QJniObject activity = QJniObject::callStaticObjectMethod(
            "org/qtproject/qt/android/QtNative",
            "activity",
            "()Landroid/app/Activity;"
            );

        if (!activity.isValid()) {
            return false;
        }

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
            mode
            );
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

    void forceLandscapeOrientation() {
    #ifdef ANDROID

        QJniObject activity = QJniObject::callStaticObjectMethod(
            "org/qtproject/qt/android/QtNative",
            "activity",
            "()Landroid/app/Activity;"
            );
        if (activity.isValid()) {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 0); // 0 = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        }
    #endif
    }
}
