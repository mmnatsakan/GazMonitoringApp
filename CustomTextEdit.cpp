#include "CustomTextEdit.h"
#include "AndroidBridge.h"
#include "AndroidHelper.h"

#include <QFocusEvent>

CustomTextEdit::CustomTextEdit(QWidget *parent)
    : QTextEdit{parent}
{
    connect(AndroidBridge::instance(), &AndroidBridge::speechRecognized, this, [this](const QString& text) {
        append("\n" + text);
    });
}

void CustomTextEdit::focusInEvent(QFocusEvent *event)
{
    qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    AndroidHelper::startVoiceInput();
    event->ignore();

}
