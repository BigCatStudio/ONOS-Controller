#include <QCoreApplication>
#include <iostream>
#include <string>

#include "headers/eventhandler.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // HTTPController GET method test for synchronous wait for data
//    HTTPController controller;
//    QByteArray hostsData;
//    try {
//        hostsData = controller.getHosts("http://192.168.0.113:8181/onos/v1/hosts");
//    } catch(std::string exception) {
//        std::cout << exception << std::endl;
//    }


//    std::vector<Host> hosts = JSONConverter::getHostsJSON(hostsData);
//    for(const auto &host : hosts) {
//        std::cout << host << std::endl;
//    }

    EventHandler eventHandler;

    /*********************
    TODO always when the topo is chose use pingall to detect all hosts
    otherwise the getHosts will not work
    *********************/

// controller.get("https://ptsv2.com/t/o70s1-1657810062/post");

//    JSONConverter converter;
//    QByteArray data = converter.postBodyJSON("1", "4", "3", "10.0.0.1/32");

//    controller.post("ONOS url", data);

    // controller.get("http://192.168.0.113:8181/onos/v1/flows");

    // TODO add function that deletes all current routes in topology - script on pendrive

    // TODO when executing GET and POST the finished method should be called to delete reply from server
    // Check if it is correctly deleted and check VoidRealms video about HTTP

    // TODO make all comments start with big letter

    return a.exec();
}
