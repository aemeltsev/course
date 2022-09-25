#ifndef JSERVER_H
#define JSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDir>

namespace  {
const QString interfaces_file = "interfaces.json";
}

class JServer : public QTcpServer
{
    Q_OBJECT

    QTcpSocket* m_socket; // tcp descriptor
    QByteArray m_data;    // data array

    QJsonDocument m_jdoc;
    QJsonParseError m_jdoc_error;
    QFile file;

public:
    JServer();
    ~JServer();

public slots:
    void startJServer();
    void incomingConnection(qintptr handle) override;
    void sockReady();
    void sockDisconect();
};

#endif // JSERVER_H
