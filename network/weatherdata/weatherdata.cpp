#include "weatherdata.h"

weatherdata::weatherdata()
{
    m_net_man = new QNetworkAccessManager(this);
    connect(m_net_man, &QNetworkAccessManager::finished, this, &weatherdata::slot_netw_man);

    m_req.setUrl(QUrl("http://api.openweathermap.org/data/2.5/weather?id=524925&appid={your api key}"));
    m_tmr = new QTimer();
    m_tmr->setInterval(120000);
    connect(m_tmr, &QTimer::timeout, this, &weatherdata::send_irq);
    m_tmr->start(120000);
    qDebug() << "Timer started";
}

weatherdata::~weatherdata()
{
    m_tmr->stop();
    m_tmr->deleteLater();

    delete m_net_man;
}

void weatherdata::send_irq()
{
    qDebug() << "OK";
    m_net_man->get(m_req);
}

void weatherdata::slot_netw_man(QNetworkReply *rep)
{
    rep->waitForReadyRead(1000);

    m_doc = QJsonDocument::fromJson(rep->readAll(), &m_doc_err);

    if(m_doc_err.errorString().toInt() == QJsonParseError::NoError)
    {
        m_temp = m_doc.object().value("main").toObject();
        auto out = m_temp.value("temp").toDouble() - 273;
        qDebug() << "Temp: " << out;
    }
}
