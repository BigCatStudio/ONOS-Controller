#include "headers/topology.h"

Topology::Topology() {
    // TODO call JSONConverter methods to create:
    // switches
    // hosts
    // linksSwitches
}

void Topology::setParameters(const QByteArray &hostsData, const QByteArray &switchesData, const QByteArray &linksData) {
    hosts = JSONConverter::getHostsJSON(hostsData);
    switches = JSONConverter::getSwitchesJSON(switchesData);
    links = JSONConverter::getLinksJSON(linksData);
}

void Topology::updateParameters() {

}

void Topology::displayParameters() const {

}

void Topology::createFlow(const QString &srcHostIp, const QString &dstHostIp) {

}

std::vector<QString> Topology::shortestPath(const QString &srcHostIp, const QString &dstHostIp) const {

}

void Topology::deleteFlows() {

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
