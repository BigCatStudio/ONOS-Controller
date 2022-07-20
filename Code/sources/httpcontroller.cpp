#include "headers/httpcontroller.h"

HTTPController::HTTPController(QObject *parent) : QObject(parent) {
    QObject::connect(&manager,&QNetworkAccessManager::authenticationRequired,this,&HTTPController::authenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::encrypted,this,&HTTPController::encrypted);
    QObject::connect(&manager,&QNetworkAccessManager::preSharedKeyAuthenticationRequired,this,&HTTPController::preSharedKeyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::proxyAuthenticationRequired,this,&HTTPController::proxyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::sslErrors,this,&HTTPController::sslErrors);
}

void HTTPController::getHosts(QString url) {
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyGetHosts);
}

void HTTPController::getSwitches(QString url) {
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyGetSwitches);
}

void HTTPController::getLinks(QString url) {
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyGetLinks);
}

void HTTPController::postFlow(QString url, QByteArray bodyData) {
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager.post(request, bodyData);
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyPostFlow);
}

void HTTPController::get(QString location) {
    qInfo() << "Getting from server...";
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(location)));
    QObject::connect(reply,&QNetworkReply::readyRead,this,&HTTPController::readyRead);
}

void HTTPController::post(QString location, QByteArray data) {
    qInfo() << "Posting to the server...";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // TODO These are lines to use for ONOS, the QByteArray data will be already sent to this function
    // JSON de/serializer should be made as class that creates JSON bodies for post requests
    // the body is created and sent here to be sent via HTTP POST request   

    QNetworkReply* reply = manager.post(request, data);
    QObject::connect(reply,&QNetworkReply::readyRead,this,&HTTPController::readyRead);
}

void HTTPController::readyGetHosts() {
    qInfo() << "Received hosts from ONOS";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()) {
        if(statusCode == 200) {
            QByteArray hostsData = reply->readAll();
            qInfo() << hostsData;
            return;
        }
    }
    // TODO maybe add exception to handle unexpected outcome
    qWarning() << "Error occurred when executing method - status code: " << statusCode;
}

// TODO add status_code checking like in readyGetHosts()
// TODO think how to send QByteArray data to JSONConverter and then to Topology
// JSONConverter methods shoudld not call HTTP functions because it would be unproffesional and messy - JSON only for JSON
void HTTPController::readyGetSwitches() {
    qInfo() << "Received switches from ONOS";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QByteArray switchesData = reply->readAll();
    qInfo() << switchesData;
}

void HTTPController::readyGetLinks() {
    qInfo() << "Received links from ONOS";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QByteArray linksData = reply->readAll();
    qInfo() << linksData;
}

void HTTPController::readyPostFlow() {
    qInfo() << "New flow rule sent to ONOS";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QByteArray flowData = reply->readAll();
    qInfo() << flowData;
}

// TODO Maybe there should be different functions for GET and POST methods
void HTTPController::readyRead() {
    qInfo() << "ReadyRead";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "Size of the reply: " << reply->size() << " | source url: " << reply->url();
    qInfo() << "System size of the reply: " << sizeof(*reply) << " | system type: " << typeid(*reply).name();
    qInfo() << "Content:";
//    if(reply) {
//        qInfo() << reply->readAll();
//    }
    QByteArray data = reply->readAll();

    QFile file("../Code/onos-rest-json/flows.json");
    if(file.open(QIODevice::WriteOnly)) {
        qInfo() << "File opened";
        file.write(data);
    }
    file.close();
}

void HTTPController::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator) {
    // TODO password and user login will be given by the user, when starting the program
    authenticator->setUser("karaf");
    authenticator->setPassword("karaf");
    qInfo() << "authenticationRequired";
}

void HTTPController::encrypted(QNetworkReply *reply) {
    Q_UNUSED(reply);
    qInfo() << "encrypted";
}

void HTTPController::finished(QNetworkReply *reply) {
    qInfo() << "finished";
    reply->deleteLater();
}

void HTTPController::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator) {
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo() << "preSharedKeyAuthenticationRequired";
}

void HTTPController::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator) {
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
    qInfo() << "proxyAuthenticationRequired";
}

void HTTPController::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    Q_UNUSED(reply);
    Q_UNUSED(errors);
    qInfo() << "sslErrors";
}
