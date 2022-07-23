#ifndef TOPOLOGY_H
#define TOPOLOGY_H


#include <vector>

#include "headers/topologyelements.h"
#include "headers/jsonconverter.h"

class Topology {
    friend std::ostream &operator<<(std::ostream &stream, const Topology &Source);
private:
    std::vector<Switch> switches;   // All switches in topology
    std::vector<Host> hosts;        // All hosts in topology
    std::vector<Link> links;        // All links between switches
    // Host can be connected only with one switch, so hosts will not be regarded as Nodes when calculating paths

    // TODO create Adjacency List to store all links for every host/switch and its cost
    // Prototype: <source Node> -> [<destination Node1, cost1>, <destination Node2, cost2>, ...]
    // Adjacency List will be used as Graph representation of the topology when calculating the least costly path between hosts

    // TODO - Adjacency List indexes can be chassisId of the switches because they start with 1 and grow with step 1
    // Maybe first element of the list should be empty - not so ellegant solution !

    // Adjacency List
    // std::vector of std::vector is list of all switches in topology
    // std::vector of std::pair is list of all reachable switches with their cost
    std::vector<std::vector<std::pair<Switch, double>>> adjacencyList;

public:
    Topology();

    void setParameters(const QByteArray &hostsData, const QByteArray &switchesData, const QByteArray &linksData);
    void updateParameters();
    void displayParameters() const;
    void createFlow(const QString &srcHostIp, const QString &dstHostIp);
    std::vector<QString> shortestPath(const QString &srcHostIp, const QString &dstHostIp) const;
    void deleteFlows();
};

#endif // TOPOLOGY_H
