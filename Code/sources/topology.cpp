#include "headers/topology.h"

Topology::Topology() {
    // TODO call JSONConverter methods to create:
    // switches
    // hosts
    // linksSwitches

    // TODO change getting data from files to getting data from given URL
    QFile fileHosts("../Code/onos-rest-json/hosts.json");
    if(fileHosts.open(QIODevice::ReadOnly)) {
        hosts = JSONConverter::getHostsJSON(fileHosts.readAll());
    }
    fileHosts.close();

    QFile fileSwitches("../Code/onos-rest-json/devices.json");
    if(fileSwitches.open(QIODevice::ReadOnly)) {
        switches = JSONConverter::getSwitchesJSON(fileSwitches.readAll());
    }
    fileSwitches.close();

    QFile fileLinksSwitches("../Code/onos-rest-json/links.json");
    if(fileLinksSwitches.open(QIODevice::ReadOnly)) {
        linksSwitches = JSONConverter::getLinksSwitchesJSON(fileLinksSwitches.readAll());
    }
    fileLinksSwitches.close();
}

std::ostream &operator<<(std::ostream &stream, const Topology &Source) {
    stream << "Hosts:\n";
    for(const auto &host : Source.hosts) {
        stream << host << "\n";
    }

    stream << "\nSwitches:\n";
    for(const auto &switch_ : Source.switches) {
        stream << switch_ << "\n";
    }

    stream << "\nLinks Between Switches:\n";
    for(const auto &linkSwitches : Source.linksSwitches) {
        stream << linkSwitches << "\n";
    }

    return stream;
}
