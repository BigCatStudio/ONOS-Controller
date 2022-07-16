#include <QCoreApplication>
#include <iostream>
#include <memory>
#include "httpcontroller.h"
#include "jsonconverter.h"

//to delete just testing
struct ControllerDeleter {
    void operator()(HTTPController *controller) {
        qInfo() << "Deleting controller";
        delete controller;
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // GET request test
    HTTPController controller;
    controller.get("https://ptsv2.com/t/o70s1-1657810062/post");

    JSONConverter converter;
    converter.postBody("1", "4", "3", "10.0.0.1/32");

    // TODO when executing GET and POST the finished method should be called to delete reply from server
    // Check if it is correctly deleted and check VoidRealms video about HTTP

    // Testing controller with smart pointer
//    {
//        std::unique_ptr<HTTPController, ControllerDeleter> controller(new HTTPController());
//        controller->get("https://ptsv2.com/t/o70s1-1657810062/post");
//    }

    // POST request test
//    QByteArray data;
//    data.append("param1=hello");
//    data.append("&");
//    data.append("param2=foo");

//    controller.post("https://postman-echo.com/post",data);

    return a.exec();
}
