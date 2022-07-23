#include "headers/httpcontroller.h"

HTTPController::HTTPController(QObject *parent) : QObject(parent) {
    QObject::connect(&manager,&QNetworkAccessManager::authenticationRequired,this,&HTTPController::authenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::encrypted,this,&HTTPController::encrypted);
    QObject::connect(&manager,&QNetworkAccessManager::preSharedKeyAuthenticationRequired,this,&HTTPController::preSharedKeyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::proxyAuthenticationRequired,this,&HTTPController::proxyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::sslErrors,this,&HTTPController::sslErrors);
}

void HTTPController::setAuthentication(QString userGiven, QString passwordGiven) {
    user = userGiven;
    password = passwordGiven;
}

bool HTTPController::getDataHandler(const QString &url, QByteArray &data) {
    QEventLoop waitLoop;
    QTimer timer;
    timer.setSingleShot(true);
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(url)));

    QObject::connect(reply, &QNetworkReply::readyRead, &waitLoop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &waitLoop, &QEventLoop::quit);
    timer.start(60000); // Default time to wait for data - 1 minute
    waitLoop.exec();    // Waits until all data is received from server

    // Code to perform after downloading data
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()) {
        if(statusCode.toInt() == 200) {
            data = reply->readAll();
            return true;
        }
    }
    return false;
}

QByteArray HTTPController::getHosts(const QString &url) {
    QByteArray hostsData;
    if(getDataHandler(url, hostsData)) {
        return hostsData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading hosts data from server");
    }
}

QByteArray HTTPController::getSwitches(const QString &url) {
    QByteArray switchesData;
    if(getDataHandler(url, switchesData)) {
        return switchesData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading switches data from server");
    }
}

QByteArray HTTPController::getLinks(const QString &url) {
    QByteArray linksData;
    if(getDataHandler(url, linksData)) {
        return linksData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading links data from server");
    }
}

void HTTPController::postFlow(const QString &url, const QByteArray &bodyData) {
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager.post(request, bodyData);
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyPostFlow);
}

// This function is created in order to delete all current flows from ONOS
// It should be called from Topology
void HTTPController::postDeleteFlows(const QString &url, const QByteArray &bodyData) {
    // This function is created in order to delete all current flows from ONOS
}

void HTTPController::readyPostFlow() {
    qInfo() << "New flow rule sent to ONOS";
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QByteArray flowData = reply->readAll();
    qInfo() << flowData;
}

void HTTPController::readyRead() {
    qInfo() << "ReadyRead";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    qInfo() << "Size of the reply: " << reply->size() << " | source url: " << reply->url();
    qInfo() << "System size of the reply: " << sizeof(*reply) << " | system type: " << typeid(*reply).name();
    qInfo() << "Content:";
    if(reply) {
        qInfo() << reply->readAll();
    }
}

void HTTPController::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator) {
    // TODO password and user login will be given by the user, when starting the program
    authenticator->setUser(user);
    authenticator->setPassword(password);
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
