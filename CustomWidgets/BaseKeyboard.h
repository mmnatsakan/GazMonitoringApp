#ifndef BASEKEYBOARD_H
#define BASEKEYBOARD_H

#include <QWidget>

class QGridLayout;
class BaseKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit BaseKeyboard(QWidget *parent = nullptr);

signals:
    void keyPressed(const QString &key);

protected:
    QGridLayout *layout;
    void createButtons(const QList<QStringList> &rows);

};

#endif // BASEKEYBOARD_H
