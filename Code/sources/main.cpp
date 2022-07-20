#include <QCoreApplication>
#include <iostream>

#include "headers/httpcontroller.h"
#include "headers/jsonconverter.h"
#include "headers/topology.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    HTTPController controller;

    Topology topo;
    std::cout << topo;


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
