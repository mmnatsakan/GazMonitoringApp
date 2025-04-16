#include "JsonParser.h"
#include "Json/Json.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <fstream>

#include <QJsonDocument>
#include <QJsonArray>

JsonParser::JsonParser()
{
}

JsonParser* JsonParser::instance()
{
    static JsonParser* instance = nullptr;
    if(!instance){
        instance = new JsonParser;
    }
    return instance;
}

bool JsonParser::parseJsonFile(const QString& jsonFilePath)
{
    QFile uiLayoutFile(jsonFilePath);

    if(!uiLayoutFile.open(QIODevice::ReadOnly)){
        return false;
    }

    QJsonDocument document = QJsonDocument::fromJson(uiLayoutFile.readAll());
    if (document.isArray()) {
        QJsonArray rootArray = document.array();
        for(int i = 0; i < rootArray.size(); ++i){
            QJsonObject obj = rootArray.at(i).toObject();
            MainData mainData;

            mainData.abonhamar = obj.value("abonhamar").toString();
            mainData.aah = obj.value("aah").toString();
            mainData.hasce = obj.value("hasce").toString();
            mainData.sot_hamar = obj.value("sot_hamar").toString();
            mainData.hashvich = obj.value("hashvich").toString();
            mainData.hashvichn = obj.value("hashvichn").toString();
            mainData.hashnaxc = obj.value("hashnaxc").toString();

            AmisData amisData;
            QStringList gazList = obj.value("gaz").toString().split(";");
            QStringList kniqList = obj.value("kniqner").toString().split(";");
            for(int i = 0; i < gazList.count() - 1; ++i){
                if(!gazList.at(i).isEmpty()){
                    QStringList gazQanakData = gazList.at(i).split("_");
                    amisData.taram = gazQanakData.at(0);
                    amisData.hashxm = gazQanakData.at(1);
                    amisData.xaxthash = gazQanakData.at(2);
                }
                if(i < kniqList.count() && !kniqList.at(i).isEmpty()){
                    QStringList kniqData = kniqList.at(i).split("_");
                    amisData.hashvichn = kniqData.at(1);
                    amisData.kniqner = kniqData.at(2);
                }
                mainData.tableDataList << amisData;
            }
            m_mainData << mainData;
        }

        return true;
    }
    else {
        return false;
    }
}

QList<MainData> JsonParser::getMainData() const
{
    return m_mainData;
}
