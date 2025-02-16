#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonObject>

struct GazQanak{
    GazQanak() {}
    QString taram;
    QString hashxm;
    QString xaxthash;
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
    QList<GazQanak> gazQanakList;
};

class QJsonArray;

class JsonParser
{
public:
    static JsonParser* instance();
    bool parseJsonFile(const QString& jsonFilePath);

    QList<MainData> getMainData() const;


private:
    JsonParser();
    //remove copy constructor and assignment operator for Singleton
    JsonParser(const JsonParser&) = delete;
    JsonParser& operator=(const JsonParser&) = delete;
    void clearAll();

    QList<MainData> m_mainData;

};

#endif // JSONPARSER_H
