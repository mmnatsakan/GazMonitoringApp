#ifndef ANDROIDHELPER_H
#define ANDROIDHELPER_H

#include <QString>

namespace AndroidHelper {
    bool isDarkModeActive();
    void setDarkMode(bool enable);
    void applyQtDarkPalette();
    void forceLandscapeOrientation();
    void forceShowKeyboard();
    void startVoiceInput();
    void registerSpeechResultHandler(void* env);
    void speechReceivedCallback(const QString &text);

}

#endif // ANDROIDHELPER_H
