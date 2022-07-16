#include "httpcontroller.h"

HTTPController::HTTPController(QObject *parent) : QObject(parent) {
    connect(&manager,&QNetworkAccessManager::authenticationRequired,this,&HTTPController::authenticationRequired);
    connect(&manager,&QNetworkAccessManager::encrypted,this,&HTTPController::encrypted);
    connect(&manager,&QNetworkAccessManager::preSharedKeyAuthenticationRequired,this,&HTTPController::preSharedKeyAuthenticationRequired);
    connect(&manager,&QNetworkAccessManager::proxyAuthenticationRequired,this,&HTTPController::proxyAuthenticationRequired);
    connect(&manager,&QNetworkAccessManager::sslErrors,this,&HTTPController::sslErrors);

}

void HTTPController::get(QString location) {
    qInfo() << "Getting from server...";
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(location)));
    connect(reply,&QNetworkReply::readyRead,this,&HTTPController::readyRead);
}

void HTTPController::post(QString location, QByteArray data) {
    qInfo() << "Posting to the server...";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "test/plain"); //mime type

    // TODO These are lines to use for ONOS, the QByteArray data will be already sent to this function
    // JSON de/serializer should be made as class that creates JSON bodies for post requests
    // the body is created and sent here to be sent via HTTP POST request
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QJsonObject obj;
//    ...
//    QJsonDocument doc(obj);
//    QByteArray data = doc.toJson();

    QNetworkReply* reply = manager.post(request, data);
    connect(reply,&QNetworkReply::readyRead,this,&HTTPController::readyRead);
}

// TODO Maybe there should be different functions for GET and POST methods
void HTTPController::readyRead() {
    qInfo() << "ReadyRead";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    qInfo() << "Size of the reply: " << reply->size() << " | source url: " << reply->url();
    qInfo() << "System size of the reply: " << sizeof(*reply) << " | system type: " << typeid(*reply).name();
    qInfo() << "Content:";
    if(reply) {
        qInfo() << reply->readAll();
    }
}

void HTTPController::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator) {
    // TODO password and user login will be given by the user, when starting the program
    authenticator->setUser("Budzyn");
    authenticator->setPassword("Budzyn");
    qInfo() << "authenticationRequired";
}

void HTTPController::encrypted(QNetworkReply *reply) {
    Q_UNUSED(reply);
    qInfo() << "encrypted";
}

void HTTPController::finished(QNetworkReply *reply) {
    Q_UNUSED(reply);
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