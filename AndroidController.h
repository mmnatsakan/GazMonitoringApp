#ifndef ANDROIDCONTROLLER_H
#define ANDROIDCONTROLLER_H

namespace AndroidController {
    bool isDarkModeActive();
    void setDarkMode(bool enable);
    void applyQtDarkPalette();
    void forceLandscapeOrientation();
}

#endif // ANDROIDCONTROLLER_H
