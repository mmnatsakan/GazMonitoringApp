#include "LowerLettersKeyboard.h"

LowerLettersKeyboard::LowerLettersKeyboard(QWidget *parent)
    : BaseKeyboard{parent}
{
    QList<QStringList> rows = {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {"0", ".", "Հետ"}
    };
    createButtons(rows);
}


