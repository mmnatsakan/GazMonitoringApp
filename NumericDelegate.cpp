#include "NumericDelegate.h"

#include <QGuiApplication>
#include <QLineEdit>
#include <QTimer>

QWidget *NumericDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QLineEdit *editor = new QLineEdit(parent);
    forceKeyboard(editor);
    editor->setInputMethodHints(Qt::ImhDigitsOnly);
    return editor;
}

void NumericDelegate::forceKeyboard(QWidget *widget) const
{
    widget->setFocus();
    QTimer::singleShot(0, []() {
        QInputMethod *im = QGuiApplication::inputMethod();
        if (im)
            im->show();
    });
}
