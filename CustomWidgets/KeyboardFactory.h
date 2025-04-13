#ifndef KEYBOARDFACTORY_H
#define KEYBOARDFACTORY_H

#include <QString>


class BaseKeyboard;
class QWidget;

class KeyboardFactory
{
public:
    static BaseKeyboard* createKeyboard(const QString& name, QWidget* parent = nullptr);
};

#endif // KEYBOARDFACTORY_H
