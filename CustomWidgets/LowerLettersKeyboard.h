#ifndef LOWERLETTERSKEYBOARD_H
#define LOWERLETTERSKEYBOARD_H

#include "BaseKeyboard.h"

class LowerLettersKeyboard : public BaseKeyboard
{
    Q_OBJECT
public:
    explicit LowerLettersKeyboard(QWidget *parent = nullptr);

signals:
};

#endif // LOWERLETTERSKEYBOARD_H
