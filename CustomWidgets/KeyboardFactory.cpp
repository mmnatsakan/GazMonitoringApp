#include "KeyboardFactory.h"
#include "NumpadKeyboard.h"
#include "UpperLettersKeyboard.h"
#include "LowerLettersKeyboard.h"
#include "MainSymbolsKeyboard.h"
#include "ExtendedSymbolsKeyboard.h"
#include "BaseKeyboard.h"

#include <QWidget>

BaseKeyboard *KeyboardFactory::createKeyboard(const QString &name, QWidget* parent)
{
    if(name == "Numpad")
        return new NumpadKeyboard(parent);
    else if(name == "UpperLetters")
        return new UpperLettersKeyboard(parent);
    else if(name == "LowerLetters")
        return new LowerLettersKeyboard(parent);
    else if(name == "MainSymbols")
        return new MainSymbolsKeyboard(parent);
    else if(name == "ExtendedSymbols")
        return new ExtendedSymbolsKeyboard(parent);

    return new BaseKeyboard(parent);
}
