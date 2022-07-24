#include "headers/topology.h"

Topology::Topology() {
    // TODO call JSONConverter methods to create:
    // switches
    // hosts
    // linksSwitches
}

// TODO check if returning &element can be changed in function that calls methods and if element changes in vectors
Switch Topology::getSwitchChassisId(const QString &chassisId) const {
    for(const auto &switch_ : switches) {
        if(switch_.chassisId == chassisId) {
            return switch_;
        }
    }
    throw "Could not find switch of given chassis id";
}

Switch Topology::getSwitchIpAddress(const QString &ipAddress) const {
    for(const auto &host : hosts) {
        if(host.ipAddress == ipAddress) {
            return getSwitchChassisId(host.linkToSwitch.first);
        }
    }
    throw "Could not find host of given ip address";
}

Host Topology::getHost(const QString &ipAddress) const {
    for(const auto &host : hosts) {
        if(host.ipAddress == ipAddress) {
            return host;
        }
    }
    throw "Could not find host of given ip address";
}

Link Topology::getLink(const QString &srcId, const QString &dstId) const {
    for(const auto &link : links) {
        if(link.srcId == srcId && link.dstId == dstId) {
            return link;
        }
    }
    throw "Could not find link of given source id and destination id";
}

void Topology::createAdjacencyList() {
    adjacencyList.resize(switches.size() + 1);

    // TODO think about how to calculate cost of the link
    // Where should the cost be stored
    // How to update it
    // Probably most important aspect of Topology class
    for(size_t i {1};i <= adjacencyList.size();i++) {
        for(const auto &link : links) {
            if(link.srcChassisId == QString::number(i, 10)) {
                adjacencyList.at(i).emplace_back(getSwitchChassisId(link.dstChassisId), 1.0);
            }
        }
    }

    size_t index {0};
    for(const auto &srcList : adjacencyList) {
        std::cout << "Dst of " << index++ << std::endl;
        for(const auto &dst : srcList) {
            std::cout << " -> dst: " << dst.first << " | cost: " << dst.second << std::endl;
        }
    }
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
