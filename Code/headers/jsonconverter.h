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

    // Creates JSON body of POST request for one one-direction-connection between ports (outport and inPort)
    [[ nodiscard ]] static QByteArray postBodyJSON(QString deviceId, QString outPort, QString inPort, QString ip);

    // These functions create proper std::vector<> for Topology from json files downloaded from ONOS URL
    [[ nodiscard ]] static std::vector<Host> getHostsJSON(const QByteArray &hostsData);
    [[ nodiscard ]] static std::vector<Switch> getSwitchesJSON(const QByteArray &switchesData);
    [[ nodiscard ]] static std::vector<Link> getLinksJSON(const QByteArray &linksData);
};

#endif // JSONCONVERTER_H
