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

QByteArray HTTPController::getHosts(QString url) {
    QByteArray hostsData;
    if(getDataHandler(url, hostsData)) {
        return hostsData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading hosts data from server");
    }
    // QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyGetHosts);
}

QByteArray HTTPController::getSwitches(QString url) {
    QByteArray switchesData;
    if(getDataHandler(url, switchesData)) {
        return switchesData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading switches data from server");
    }
}

QByteArray HTTPController::getLinks(QString url) {
    QByteArray linksData;
    if(getDataHandler(url, linksData)) {
        return linksData;
    } else {
        throw static_cast<std::string>("Unexpected error occurred while downloading links data from server");
    }
}

void HTTPController::postFlow(QString url, QByteArray bodyData) {
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager.post(request, bodyData);
    QObject::connect(reply, &QNetworkReply::readyRead, this, &HTTPController::readyPostFlow);
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
