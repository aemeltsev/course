#include "jserver.h"

JServer::JServer()
{}

JServer::~JServer()
{}

void JServer::startJServer()
{
    if(this->listen(QHostAddress::Any, 5555))
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("interfaces.db");
        if(m_db.open())
        {
            qDebug() << "Listening and DB open" << '\n';
        }
        else
        {
            qDebug() << "DB not open" << '\n';
        }
    }
    else
    {
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
            //{"type":"resultSelect","result":...}
            if(m_db.isOpen())
            {
                QByteArray out = "{\"type\":\"resultSelect\",\"result\":[";

                QSqlQuery* query = new QSqlQuery(m_db);
                if(query->exec("SELECT name FROM interfaces"))
                {
                    while(query->next())
                    {
                        auto str = "{\"name\":\"" + query->value(0).toString().toStdString() + "\"},";
                        out.append(str);
                    }

                    out.remove(out.length()-1, 1);
                    out.append("]}");

                    m_socket->write(out);
                    m_socket->waitForBytesWritten(500);
                }
                else
                {
                    qDebug() << "Query not success";
                }
            }
        }
    }
}

void JServer::sockDisconect()
{
    qDebug() << "Disconnect" << '\n';
    m_socket->deleteLater();
}
