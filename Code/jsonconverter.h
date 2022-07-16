#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QByteArray>
#include <QString>
#include <fstream>
#include <QFile>

class JSONConverter {
public:
    JSONConverter();

    QByteArray postBody(QString deviceId, QString outPort, QString inPort, QString ip) const;
};

#endif // JSONCONVERTER_H
