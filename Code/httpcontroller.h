#ifndef HTTPCONTROLLER_H
#define HTTPCONTROLLER_H

// TODO change qInfo() to std::cout and later change std::cout to GUI/QML output
#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <typeinfo>

// It has to be QObject because it uses slots to connect with QNetworkManager signals (operations are done asynchronously)
class HTTPController : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager manager;

public:
    explicit HTTPController(QObject *parent = nullptr);

public slots:
    // TODO add slots for other ONOS functions like routes/switches/hosts etc to
    // know what is the structure of the topology and which ports are connected
    void get(QString location);
    void post(QString location, QByteArray data);

private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

signals:
};

#endif // HTTPCONTROLLER_H
