#ifndef NUMPADKEYBOARD_H
#define NUMPADKEYBOARD_H

#include "BaseKeyboard.h"

class NumpadKeyboard : public BaseKeyboard
{
    Q_OBJECT
public:
    explicit NumpadKeyboard(QWidget *parent = nullptr);

};

#endif // NUMPADKEYBOARD_H
