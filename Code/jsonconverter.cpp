#include "jsonconverter.h"

JSONConverter::JSONConverter() {}

QByteArray JSONConverter::postBodyJSON(QString deviceId, QString outPort, QString inPort, QString ip) const {
    QJsonObject mainObject;

    mainObject["priority"] = 40000;
    mainObject["timeout"] = 0;
    mainObject["isPermanent"] = true;
    mainObject["deviceId"] = "of:000000000000000" + deviceId;

    // treatment
    QJsonObject instructionsObject;
    QJsonArray instructionsArray;
    QJsonObject instructionsContent;

    instructionsContent["type"] = "OUTPUT";
    instructionsContent["port"] = outPort;
    instructionsArray.append(instructionsContent);

    instructionsObject["instructions"] = instructionsArray;
    mainObject["treatment"] = instructionsObject;

    // selector
    QJsonObject criteriaObject;
    QJsonArray criteriaArray;
    QJsonObject criteriaPort;
    QJsonObject criteriaType;
    QJsonObject criteriaIp;

    criteriaPort["type"] = "IN_PORT";
    criteriaPort["port"] = inPort;
    criteriaArray.append(criteriaPort);

    criteriaType["type"] = "ETH_TYPE";
    criteriaType["ethType"] = "0x0800";
    criteriaArray.append(criteriaType);

    criteriaIp["type"] = "IPV4_DST";
    criteriaIp["ip"] = ip;
    criteriaArray.append(criteriaIp);

    criteriaObject["criteria"] = criteriaArray;
    mainObject["selector"] = criteriaObject;

    // TODO maybe make logger that saves all POST and GET bodies to file to have history of them all
    // Add date of request and type of request etc
    // Saving JSON document to file - just testing purpouse, if structure of JSON is OK
    QJsonDocument document(mainObject);
    QByteArray data = document.toJson();
    QFile file("../Code/data.json");
    if(file.open(QIODevice::WriteOnly)) {
        qInfo() << "File opened";
        file.write(data);
    }
    file.close();

    return data;
}
