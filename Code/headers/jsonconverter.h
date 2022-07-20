#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <utility>
#include <vector>

#include "headers/topologyelements.h"

class JSONConverter {
public:
    JSONConverter();

    // TODO all methods of this class should be marked as static and called without creating any JSONConverter object
    // Example: HTTPController object uses post(url, body) like JSONConverter::postBodyJSON(...);

    // Creates JSON body of POST request for one one-direction-connection between ports (outport and inPort)
    static QByteArray postBodyJSON(QString deviceId, QString outPort, QString inPort, QString ip);

    static std::vector<Host> getHostsJSON(QByteArray hostsData);
    static std::vector<Switch> getSwitchesJSON(QByteArray switchesData);
    static std::vector<LinkSwitches> getLinksSwitchesJSON(QByteArray linksData);
};

#endif // JSONCONVERTER_H
