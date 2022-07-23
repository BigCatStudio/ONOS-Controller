#include "headers/eventhandler.h"

EventHandler::EventHandler() {
    // ONOS arguments
    std::string stdIp;
    std::string stdUser;
    std::string stdPassword;

    std::cout << "Enter ONOS ip:";
    std::getline(std::cin, stdIp);

    std::cout << "Enter ONOS User:";
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
