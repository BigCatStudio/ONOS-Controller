#include "headers/jsonconverter.h"

JSONConverter::JSONConverter() {}

QByteArray JSONConverter::postBodyJSON(QString deviceId, QString outPort, QString inPort, QString ip) {
    QJsonObject mainObject;

    mainObject["priority"] = 40000;         // Constant value to prioritise all flows equally
    mainObject["timeout"] = 0;
    mainObject["isPermanent"] = true;
    mainObject["deviceId"] = deviceId;      // deviceId should be full id: "of:000000000000000x"

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
    QFile file("../Code/onos-rest-json/data.json");
    if(file.open(QIODevice::WriteOnly)) {
        qInfo() << "File opened";
        file.write(data);
    }
    file.close();

    return data;
}

std::vector<Host> JSONConverter::getHostsJSON(QByteArray hostsData) {
    std::vector<Host> hosts;
    QJsonDocument document = QJsonDocument::fromJson(hostsData);
    QJsonObject mainObject = document.object();

    QJsonArray hostsArray = mainObject["hosts"].toArray();
    for(size_t i {0};i < hostsArray.size();i++) {
        QJsonObject hostObject = hostsArray[i].toObject();

        QString id = hostObject["id"].toString();
        bool configured = hostObject["configured"].toBool();

        QJsonArray ipAddressesArray = hostObject["ipAddresses"].toArray();
        QString ipAddress = ipAddressesArray[0].toString();

        QJsonArray locationsArray = hostObject["locations"].toArray();
        QJsonObject locationObject = locationsArray[0].toObject();
        std::pair<QString, QString> linkToSwitch = {locationObject["elementId"].toString(), locationObject["port"].toString()};

        hosts.emplace_back(id, ipAddress, configured, linkToSwitch);
    }
    return hosts;
}

std::vector<Switch> JSONConverter::getSwitchesJSON(QByteArray switchesData) {
    std::vector<Switch> switches;
    QJsonDocument document = QJsonDocument::fromJson(switchesData);
    QJsonObject mainObject = document.object();

    QJsonArray switchesArray = mainObject["devices"].toArray();
    for(size_t i {0};i < switchesArray.size();i++) {
        QJsonObject switchObject = switchesArray[i].toObject();

        if(switchObject["type"].toString() == "SWITCH") {
            QString id = switchObject["id"].toString();
            bool available = switchObject["available"].toBool();
            QString chassisId = switchObject["chassisId"].toString();

            switches.emplace_back(id, chassisId, available);
        }
    }
    return switches;
}

std::vector<LinkSwitches> JSONConverter::getLinksSwitchesJSON(QByteArray linksData) {
    std::vector<LinkSwitches> linksSwitches;
    QJsonDocument document = QJsonDocument::fromJson(linksData);
    QJsonObject mainObject = document.object();

    QJsonArray linksArray = mainObject["links"].toArray();
    for(size_t i {0};i < linksArray.size();i++) {
        QJsonObject linkObject = linksArray[i].toObject();

        QJsonObject srcObject = linkObject["src"].toObject();
        QString srcId = srcObject["device"].toString();
        QString srcPort = srcObject["port"].toString();

        QJsonObject dstObject = linkObject["dst"].toObject();
        QString dstId = dstObject["device"].toString();
        QString dstPort = dstObject["port"].toString();

        QString type = linkObject["type"].toString();
        QString state = linkObject["state"].toString();

        linksSwitches.emplace_back(srcId, srcPort, dstId, dstPort, type, state);
    }
    return linksSwitches;
}
