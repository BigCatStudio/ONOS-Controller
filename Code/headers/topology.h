#ifndef TOPOLOGY_H
#define TOPOLOGY_H


#include "headers/topologyelements.h"
#include <vector>

class Topology {
private:
    std::vector<Switch> switches;   // All switches in topology
    std::vector<Host> hosts;        // All hosts in topology
    std::vector<std::vector<LinkSwitches>> linksSwitches;

public:
    Topology();

};

#endif // TOPOLOGY_H
