#include "weatherdata.h"

weatherdata::weatherdata()
{
    m_net_man = new QNetworkAccessManager(this);
    connect(m_net_man, &QNetworkAccessManager::finished, this, &weatherdata::slot_netw_man);

    m_req.setUrl(QUrl("http://api.openweathermap.org/data/2.5/forecast?id=524925&cnt=3&appid={Your API key}"));
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
        m_temp = m_doc.object();
        m_value = m_temp.value("list");
        m_arr = m_value.toArray();

        if(!m_arr.empty())
        {
            foreach(const QJsonValue& v, m_arr)
            {
                auto date_info = v.toObject();
                auto data = unix_time2human_time(date_info.value("dt").toInt());
                qDebug() << "Date: " << data.date << "/" << data.month << "/" << data.year << '\n';

                auto temp_info = date_info.value("main").toObject();
                auto temp = temp_info.value("temp").toDouble() - 273;
                auto feel_like = temp_info.value("feels_like").toDouble() - 273;
                auto temp_min = temp_info.value("temp_min").toDouble() - 273;
                auto temp_max = temp_info.value("temp_max").toDouble() - 273;
                auto pressure = temp_info.value("pressure").toDouble() / 1.333;
                auto humidity = temp_info.value("humidity").toDouble();
                qDebug() << "Temperature: " << temp << '\n';
                qDebug() << "Temperature feel like: " << feel_like << '\n';
                qDebug() << "Temperature min: " << temp_min << '\n';
                qDebug() << "Temperature max: " << temp_max << '\n';
                qDebug() << "Pressure: " << pressure << '\n';
                qDebug() << "Humidity: " << humidity << '\n';

                auto weather_info = date_info.value("weather").toArray();
                QString weather_main = "";
                QString weather_desc = "";
                if(!weather_info.empty())
                {
                    foreach(const QJsonValue& w, weather_info)
                    {
                        auto tmp = w.toObject();
                        weather_main = tmp.value("main").toString();
                        weather_desc = tmp.value("description").toString();
                        qDebug() << "Weather: " << weather_main << '\n';
                        qDebug() << "Weather description: " << weather_desc << '\n';
                    }
                }

                auto clouds_info = date_info.value("clouds").toObject();
                auto clouds = clouds_info.value("all").toInt();
                qDebug() << "Clouds: " << clouds << '\n';

                auto wind_info = date_info.value("wind").toObject();
                auto wind_speed = wind_info.value("speed").toDouble();
                auto wind_degree = wind_info.value("deg").toInt();
                auto wind_gust = wind_info.value("gust").toDouble();
                qDebug() << "Wind speed: " << wind_speed << '\n';
                qDebug() << "Wind degree: " << wind_degree << '\n';
                qDebug() << "Wind gust: " << wind_gust << '\n';

                auto visibility_info = date_info.value("visibility").toInt();
                qDebug() << "Visibility: " << visibility_info << '\n';

                auto pop_info = date_info.value("pop").toDouble() * 100;
                qDebug() << "Probability of precipitation: " << pop_info << "%" << '\n';

                auto rain_info = date_info.value("rain").toObject();
                auto rain_3h = rain_info.value("3h").toDouble() * 100;
                qDebug() << "Rain volume for last 3 hours: " << rain_3h << "%" << '\n';

//                auto snow_info = date_info.value("snow").toObject();
//                auto snow_3h = snow_info.value("3h").toInt();
//                qDebug() << "Snow volume for last 3 hours: " << snow_3h << '\n';

                auto sys_info = date_info.value("sys").toObject();
                auto pod = sys_info.value("pod").toString();
                qDebug() << "Part of the day: " << pod << '\n';
            }
        }
        else{
            qDebug() << "The list is empty";
        }
    }
}

weatherdata::date_time weatherdata::unix_time2human_time(qint64 seconds)
{
    date_time result;

    const qint16 days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    qint64 curr_year, days_till_now, extra_time, extra_days, index,
        date, month;
    bool flag = false;

    // Calculate total days unix time T
    days_till_now = seconds / (86400); //24 * 60 * 60
    extra_time = seconds % (86400); //24 * 60 * 60
    curr_year = 1970;

    // Calculating current year
    while(days_till_now >= 365)
    {
        if(curr_year % 400 == 0 || (curr_year % 4 == 0 && curr_year % 100 != 0))
        {
            days_till_now -= 366;
        }
        else{
            days_till_now -= 365;
        }
        curr_year += 1;
    }

    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extra_days = days_till_now + 1;

    if(curr_year % 400 == 0 || (curr_year % 4 == 0 && curr_year % 100 != 0))
    {
        flag = true;
    }

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag)
    {
        while(true)
        {
            if (index == 1)
            {
                if (extra_days - 29 < 0) break;
                month += 1;
                extra_days -= 29;
            }
            else
            {
                if ((extra_days - days_of_month[index]) < 0) break;
                month += 1;
                extra_days -= days_of_month[index];
            }
            index += 1;
        }
    }
    else
    {
        while(true)
        {
            if ((extra_days - days_of_month[index]) < 0) break;
            month += 1;
            extra_days -= days_of_month[index];
            index += 1;
        }
    }

    // Current Month
    if (extra_days > 0)
    {
        month += 1;
        date = extra_days;
    }
    else
    {
        if (month == 2 && flag == 1) date = 29;
        else {date = days_of_month[month - 1];}
    }

    // Calculating HH:MM:YYYY
    result.hours = extra_time / 3600;
    result.minutes = (extra_time % 3600) / 60;
    result.seconds = (extra_time % 3600) % 60;

    result.date = date;
    result.month = month;
    result.year = curr_year;

    return result;
}
