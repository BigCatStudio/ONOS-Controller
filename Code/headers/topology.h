#ifndef TOPOLOGY_H
#define TOPOLOGY_H


#include <vector>

#include "headers/topologyelements.h"

// TODO delete these headers later - only test purpouses
#include <QFile>
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


public:
    Topology();

};

#endif // TOPOLOGY_H
