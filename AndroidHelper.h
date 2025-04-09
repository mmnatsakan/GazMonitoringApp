#ifndef ANDROIDHELPER_H
#define ANDROIDHELPER_H

namespace AndroidHelper {
    bool isDarkModeActive();
    void setDarkMode(bool enable);
    void applyQtDarkPalette();
    void forceLandscapeOrientation();
}

#endif // ANDROIDHELPER_H
