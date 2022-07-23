#include "headers/topology.h"

Topology::Topology() {
    // TODO call JSONConverter methods to create:
    // switches
    // hosts
    // linksSwitches
}

void Topology::setParameters(QByteArray hostsData, QByteArray switchesData, QByteArray linksData) {
    hosts = JSONConverter::getHostsJSON(hostsData);
    switches = JSONConverter::getSwitchesJSON(switchesData);
    links = JSONConverter::getLinksJSON(linksData);
}

std::ostream &operator<<(std::ostream &stream, const Topology &Source) {
    stream << "\nHosts:\n";
    for(const auto &host : Source.hosts) {
        stream << host << "\n";
    }

    stream << "\nSwitches:\n";
    for(const auto &switch_ : Source.switches) {
        stream << switch_ << "\n";
    }

    stream << "\nLinks Between Switches:\n";
    for(const auto &link : Source.links) {
        stream << link << "\n";
    }

    return stream;
}
