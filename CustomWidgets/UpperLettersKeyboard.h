#ifndef UPPERLETTERSKEYBOARD_H
#define UPPERLETTERSKEYBOARD_H

#include "BaseKeyboard.h"

class UpperLettersKeyboard : public BaseKeyboard
{
    Q_OBJECT
public:
    explicit UpperLettersKeyboard(QWidget *parent = nullptr);

signals:
};

#endif // UPPERLETTERSKEYBOARD_H
