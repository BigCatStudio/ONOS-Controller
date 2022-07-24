#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <string>       // Used when using std I/O operations and transforming them to QString
#include <memory>       // TODO maybe use with controller and topology but not sure by now
#include <exception>

#include "headers/topology.h"
#include "headers/httpcontroller.h"
#include "headers/jsonconverter.h"

class EventHandler {
private:
    // TODO declare HTTPController and Topology as std::unique_ptr<>
    HTTPController controller;
    Topology topology;
    QString ip;
    QString user;
    QString password;

public:
    EventHandler();

    void run();
};

#endif // EVENTHANDLER_H
