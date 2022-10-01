#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    QJsonValue m_value;

    QJsonArray m_arr;
    QJsonParseError m_doc_err;

    QNetworkRequest m_req;

    QNetworkAccessManager* m_net_man;

private slots:
    void send_irq();
    void slot_netw_man(QNetworkReply*);

private:

    struct date_time
    {
        quint64 date;
        quint64 month;
        quint64 year;
        quint64 hours;
        quint64 minutes;
        quint64 seconds;
    };

    date_time unix_time2human_time(qint64 seconds);


};

#endif // WEATHERDATA_H
