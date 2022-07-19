#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QString>
#include <QFile>

class JSONConverter {
public:
    JSONConverter();

    // Creates JSON body of POST request for one one-direction-connection between ports (outport and inPort)
    static QByteArray postBodyJSON(QString deviceId, QString outPort, QString inPort, QString ip);
};

#endif // JSONCONVERTER_H
