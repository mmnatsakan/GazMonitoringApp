#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CustomTextEdit(QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *event);
};

#endif // CUSTOMTEXTEDIT_H
