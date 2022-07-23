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
#include <QFile>
#include <QEventLoop>   // To synchronously wait for the all data to download from ONOS
#include <QTimer>       // Sets max time to wait for data from ONOS
#include <typeinfo> // TODO probably to remove in the future

// It has to be QObject because it uses slots to connect with QNetworkManager signals (operations are done asynchronously)
class HTTPController : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager manager;
    QString user;
    QString password;

public:
    explicit HTTPController(QObject *parent = nullptr);

    void setAuthentication(QString userGiven, QString passwordGiven);

public slots:
    // TODO add slots for other ONOS functions like routes/switches/hosts etc to
    // know what is the structure of the topology and which ports are connected

    // TODO add in every function const QString &string to save memory

    // User-defined
    [[ nodiscard ]] bool getDataHandler(const QString &url, QByteArray &data);
    [[ nodiscard ]] QByteArray getHosts(QString url);
    [[ nodiscard ]] QByteArray getSwitches(QString url);
    [[ nodiscard ]] QByteArray getLinks(QString url);
    void postFlow(QString url, QByteArray bodyData);

    // Qt-provided
    void post(QString location, QByteArray data);

private slots:
    // User-defined
    void readyPostFlow();

    // Qt-provided
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
