#ifndef TOPOLOGYELEMENTS_H
#define TOPOLOGYELEMENTS_H


#include <QString>
#include <vector>
#include <utility>  // Needed to use std::pair<>
#include <iostream>

struct Switch {
    QString id;         // Full id of the switch
    QString chassisId;  // Only the usefull part of the id - example of:0000000013 -> chassisId = 13
    bool available;         // Status of the switch
    // TODO add std::vector<QString> ports;     // All ports that switch contains

    Switch(QString idGiven, QString chassisIdGiven, bool availableGiven);
};

struct Host {
    QString id;         // Id of the host is combination of: MAC & vlan
    QString ipAddress;  // Ip address of the host - usually 10.0.0.x
    bool configured;        // Status of the host - configured as server, client, none
    std::pair<QString, QString> linkToSwitch;    // Switch and port that host is connected to
                                                 // std::pair<chassisId - QString, port - QString>
    Host(QString idGiven, QString ipAddressGiven, bool configuredGiven, std::pair<QString, QString> linkToSwitchGiven);
};

// TODO change name LinkSwitches and all linkSwitch to just Link, links etc
struct Link {
    QString srcId;      // Id of the source switch
    QString srcPort;    // Port of the source switch
    QString dstId;      // Id of the destination switch
    QString dstPort;    // Port of the destination switch
                            // src(id, port) -> dst(id, port) - one direction connection

    QString srcChassisId;
    QString dstChassisId;

    // TODO maybe type and state should be stored as enum Type, State because std::string might take too much memory
    // Check in onos API all possible options of status and state
    QString type;
    QString state;

    Link(QString srcIdGiven, QString srcPortGiven, QString dstIdGiven, QString dstPortGiven, QString typeGiven, QString stateGiven);
};

std::ostream &operator<<(std::ostream &stream, const Switch &Source);

std::ostream &operator<<(std::ostream &stream, const Host &Source);

std::ostream &operator<<(std::ostream &stream, const Link &Source);

#endif // TOPOLOGYELEMENTS_H
