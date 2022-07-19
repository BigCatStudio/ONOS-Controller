#ifndef TOPOLOGYELEMENTS_H
#define TOPOLOGYELEMENTS_H


#include <vector>
#include <tuple>
#include <string>

struct Switch {
    std::string id;         // Full id of the switch
    std::string chassisId;  // Only the usefull part of the id - example of:0000000013 -> chassisId = 13
    bool available;         // Status of the switch
    std::vector<std::string> ports;     // All ports that switch contains

    Switch();
};

struct Host {
    std::string id;         // Id of the host is configuration of: MAC & vlan
    std::string ipAddress;  // Ip address of the host - usually 10.0.0.x
    bool configured;        // Status of the host - configured as server, client, none
    std::vector<std::string> ports;     // All ports that host contains
    std::vector <std::tuple<Switch, std::string>> linksHostSwitches;    // All switches and their ports that host is connected to
                                                                        // std::tuple<Switch - struct, port - std::string>
    Host();
};

struct LinkSwitches {
    std::string srcId;      // Id of the source switch
    std::string srcPort;    // Port of the source switch
    std::string dstId;      // Id of the destination switch
    std::string dstPort;    // Port of the destination switch
                            // src(id, port) -> dst(id, port) - one direction connection

    // TODO maybe type and state should be stored as enum Type, State because std::string might take too much memory
    // Check in onos API all possible options of status and state
    std::string type;
    std::string state;

    LinkSwitches();
};

#endif // TOPOLOGYELEMENTS_H
