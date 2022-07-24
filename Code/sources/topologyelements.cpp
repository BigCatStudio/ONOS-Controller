#include "../headers/topologyelements.h"

// TODO add proper constructors for these structs
Switch::Switch(QString idGiven, QString chassisIdGiven, bool availableGiven)
    : id{idGiven}, chassisId{chassisIdGiven}, available{availableGiven} {}

Host::Host(QString idGiven, QString ipAddressGiven, bool configuredGiven, std::pair<QString, QString> linkToSwitchGiven)
    : id{idGiven}, ipAddress{ipAddressGiven}, configured{configuredGiven}, linkToSwitch{linkToSwitchGiven} {}

Link::Link(QString srcIdGiven, QString srcPortGiven, QString dstIdGiven, QString dstPortGiven, QString typeGiven, QString stateGiven)
    : srcId{srcIdGiven}, srcPort{srcPortGiven}, dstId{dstIdGiven}, dstPort{dstPortGiven}, type{typeGiven}, state{stateGiven} {

    // Creating chassisId from full id to not call switches
    srcChassisId = srcIdGiven.sliced(3, 16);
    dstChassisId = dstIdGiven.sliced(3, 16);

    while(srcChassisId.at(0) == '0') {
        srcChassisId.remove(0, 1);
    }

    while(dstChassisId.at(0) == '0') {
        dstChassisId.remove(0, 1);
    }
}

std::ostream &operator<<(std::ostream &stream, const Switch &Source) {
    stream << " -> ID: " << Source.id.toStdString() << " | Chassis ID: " << Source.chassisId.toStdString() << " | Available: " << Source.available;
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Host &Source) {
    stream << " -> ID: " << Source.id.toStdString() << " | IP: " << Source.ipAddress.toStdString() << " | Configured: " << Source.configured << " | Switch ID: " << Source.linkToSwitch.first.toStdString() << " | Switch Port: " << Source.linkToSwitch.second.toStdString();
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Link &Source) {
    stream << " -> Source ID: " << Source.srcId.toStdString() << " | Source Port: " << Source.srcPort.toStdString() << " | Destination ID: " << Source.dstId.toStdString() << " | Destination Port: " << Source.dstPort.toStdString() << " | Type: " << Source.type.toStdString() << " | State: " << Source.state.toStdString();
    return stream;
}
