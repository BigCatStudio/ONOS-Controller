#ifndef TOPOLOGY_H
#define TOPOLOGY_H


#include "headers/topologyelements.h"
#include <vector>

class Topology {
private:
    std::vector<Switch> switches;   // All switches in topology
    std::vector<Host> hosts;        // All hosts in topology
    std::vector<std::vector<LinkSwitches>> linksSwitches;   // All links between switches
    // TODO think about adding links with hosts because host can be connected with more than one switch

public:
    Topology();

};

#endif // TOPOLOGY_H