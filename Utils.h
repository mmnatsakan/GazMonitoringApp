#ifndef UTILS_H
#define UTILS_H

#include <QStringList>

namespace Utils {
    struct AmisData{
        AmisData() {}
        QString taram;
        QString hashxm;
        QString xaxthash;
        QString hashvichn;
        QString kniqner;
    };

    struct MainData
    {
        MainData() {}
        QString abonhamar;
        QString aah;
        QString hasce;
        QString sot_hamar;
        QString hashvich;
        QString hashvichn;
        QString hashnaxc;
        QString kniq;
        QList<AmisData> tableDataList;
    };
}

#endif // UTILS_H
