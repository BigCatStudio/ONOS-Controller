#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <string>
#include <memory>
#include <QString>

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
};

#endif // EVENTHANDLER_H
