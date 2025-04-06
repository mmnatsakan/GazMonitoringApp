#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStringList>

const QStringList MONITORING_HEADERS_LIST = {
    "Բաժ.\nհամարը", "Ազգանուն Անունը", "Հասցեն", "Հաշվիչի\nհամարը", "Նախկին\nցուցմունքը", "Առկա\nցուցմունքը", "Մեկնաբա-\nնություն"
};

const QStringList MEKNAB_LIST {
    "Արկղի կնիքը բացակայում էր:", "Արկղի կնիքը վնասված էր:", "Հաշվիչն աշխատում էր ձայնով:", "Արտաքին միջամտություն:", "Հաշվիչի շրջանցում:"
};

const QString MONITORING_MODEL_BASE_QUERY = "SELECT abonhamar, TRIM(aah) AS aah, TRIM(hasce) AS hasce, TRIM(hashvichn) AS hashvichn, "
                                            "hashnaxc, hashverc, meknab, kniqner, hashxmner "
                                            "FROM cucak ";

const int ABONHAMAR_COLUMN_INDEX = 0;
const int AAH_COLUMN_INDEX = 1;
const int HASCE_COLUMN_INDEX = 2;
const int HASHVICHN_COLUMN_INDEX = 3;
const int HASHNAXC_COLUMN_INDEX = 4;
const int HASHVERC_COLUMN_INDEX = 5;
const int MEKNAB_COLUMN_INDEX = 6;
const int HASHXMNER_COLUMN_INDEX = 7;
const int KNIQNER_COLUMN_INDEX = 8;

#endif // CONSTANTS_H
