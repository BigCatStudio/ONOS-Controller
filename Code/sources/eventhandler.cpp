#include "headers/eventhandler.h"

EventHandler::EventHandler() {
    // ONOS arguments
    std::string stdIp;
    std::string stdUser;
    std::string stdPassword;

    std::cout << "Enter ONOS ip:";
    std::getline(std::cin, stdIp);

    std::cout << "Enter ONOS user:";
    std::getline(std::cin, stdUser);

    std::cout << "Enter ONOS password:";
    std::getline(std::cin, stdPassword);

    ip = QString::fromStdString(stdIp);
    user = QString::fromStdString(stdUser);
    password = QString::fromStdString(stdPassword);
    controller.setAuthentication(user, password);

    // Creating topology
    QByteArray hostsData;
    QByteArray switchesData;
    QByteArray linksData;
    try {
        hostsData = controller.getHosts("http://" + ip + ":8181/onos/v1/hosts");
        switchesData = controller.getSwitches("http://" + ip + ":8181/onos/v1/devices");
        linksData = controller.getLinks("http://" + ip + ":8181/onos/v1/links");
    } catch(const std::string &exception) {
        std::cout << exception << std::endl;
    }

    topology.setParameters(hostsData, switchesData, linksData);
    std::cout << topology << std::endl;
}

void EventHandler::run() {
    bool exitLoop {false};

    while(!exitLoop) {
        std::string choice;
        std::cout << "\nActions" << std::endl;
        std::cout << "1.Create new flow" << std::endl;
        std::cout << "2.Check shortest path between hosts" << std::endl;
        std::cout << "3.Display informations about topology" << std::endl;
        std::cout << "4.End program" << std::endl;
        std::cout << "Choose action:";
        std::getline(std::cin, choice);

        try {
            switch(std::stoi(choice)) {
                case 1: {
                    std::cout << "\n1 provided" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "\n2 provided" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "\n3 provided" << std::endl;
                    break;
                }
                case 4: {
                    std::cout << "\n4 provided" << std::endl;
                    exitLoop = true;
                    break;
                }
                default: {
                    std::cerr << "\nInvalid option provided" << std::endl;
                }
            }
        } catch(const std::exception &exception) {
            std::cerr << "\nCannot convert input to numerical value" << std::endl;
            std::cerr << exception.what() << std::endl;
        }
    }
}
