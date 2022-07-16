#include <QCoreApplication>
#include <iostream>
#include <memory>
#include "httpcontroller.h"

//to delete just testing
struct ControllerDeleter {
    void operator()(HTTPController *controller) {
        qInfo() << "Deleting controller";
        delete controller;
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Testing controller with smart pointers
//    {
//        std::unique_ptr<HTTPController, ControllerDeleter> controller(new HTTPController());
//        controller->get("https://ptsv2.com/t/o70s1-1657810062/post");
//    }

    // Normal behavior
    HTTPController controller;
    controller.get("https://ptsv2.com/t/o70s1-1657810062/post");

//    QByteArray data;
//    data.append("param1=hello");
//    data.append("&");
//    data.append("param2=foo");

//    controller.post("https://postman-echo.com/post",data);

    return a.exec();
}
