#include "AndroidBridge.h"

AndroidBridge::AndroidBridge(QObject* parent) : QObject(parent) {}

AndroidBridge* AndroidBridge::instance()
{
    static AndroidBridge inst;
    return &inst;
}
