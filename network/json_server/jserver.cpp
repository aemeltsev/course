#include "jserver.h"

JServer::JServer()
{}

JServer::~JServer()
{}

void JServer::startJServer()
{
    if(this->listen(QHostAddress::Any, 5555)){
        qDebug() << "Listening" << '\n';
    }
    else{
        qDebug() << "Not listening" << '\n';
    }
}

void JServer::incomingConnection(qintptr handle)
{
    m_socket = new QTcpSocket(this);
    m_socket->setSocketDescriptor(handle);

    connect(m_socket, &QTcpSocket::readyRead, this, &JServer::sockReady);
    connect(m_socket, &QTcpSocket::disconnected, this, &JServer::sockDisconect);

    qDebug() << handle << " Client connected" << '\n';

    // json - {"key":"text" or number}
    // {"type":"connect","status":"open"}
    m_socket->write("{\"type\":\"connect\",\"status\":\"open\"}");
    qDebug() << "Send client connect status - YES" << '\n';
}

void JServer::sockReady()
{
    m_data = m_socket->readAll();
    qDebug() << "Data: " << m_data << '\n';

    // {"type":"select", "params":"interface"}
    m_jdoc = QJsonDocument::fromJson(m_data, &m_jdoc_error);
    if(m_jdoc_error.errorString().toInt() == QJsonParseError::NoError)
    {
        if((m_jdoc.object().value("type").toString() == "select")
            && (m_jdoc.object().value("params").toString() == "interface"))
        {
            auto path = QDir::currentPath();
            qDebug() << path << '\n';
            file.setFileName(path + "\\" + interfaces_file);
            if(file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QByteArray fromfile = file.readAll();
                //{"type":"resultSelect", "result":...}
                QByteArray out = "{\"type\":\"resultSelect\",\"result\":" + fromfile + "}";
                m_socket->write(out);
            }
            file.close();
        }
    }
}

void JServer::sockDisconect()
{
    qDebug() << "Disconnect" << '\n';
    m_socket->deleteLater();
}
