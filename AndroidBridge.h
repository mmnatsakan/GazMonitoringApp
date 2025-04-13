#ifndef ANDROIDBRIDGE_H
#define ANDROIDBRIDGE_H

#include <QObject>

class AndroidBridge : public QObject
{
    Q_OBJECT

public:
    static AndroidBridge* instance();

signals:
    void speechRecognized(const QString& text);

private:
    explicit AndroidBridge(QObject* parent = nullptr);
};

#endif // ANDROIDBRIDGE_H
