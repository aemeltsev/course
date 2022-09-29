#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDebug>

class weatherdata : public QObject
{
    Q_OBJECT

public:
    weatherdata();
    ~weatherdata();

    QTimer* m_tmr;

    QJsonDocument m_doc;
    QJsonObject m_temp;
    QJsonParseError m_doc_err;
    QNetworkRequest m_req;

    QNetworkAccessManager* m_net_man;

private slots:
    void send_irq();
    void slot_netw_man(QNetworkReply*);
};

#endif // WEATHERDATA_H
