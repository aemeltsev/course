#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(0, 0, 242, 270);
    m_main_layout = new QVBoxLayout();
    m_table = new QTableView(this);
    m_table->setGeometry(2, 2, 238, 200);
    m_main_layout->addWidget(m_table);

    m_pb_connect = new QPushButton(this);
    m_pb_connect->setGeometry(2, 210, 238, 25);
    m_pb_connect->setText("Connect with server");
    m_main_layout->addWidget(m_pb_connect);

    m_get_list = new QPushButton(this);
    m_get_list->setGeometry(2, 240, 238, 25);
    m_get_list->setText("Get worker list");
    m_main_layout->addWidget(m_get_list);

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::sockReady);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::sockDisconect);
    connect(m_pb_connect, &QPushButton::clicked, this, &MainWindow::sockConnect);
    connect(m_get_list, &QPushButton::clicked, this, &MainWindow::sockGetWorkers);
}

MainWindow::~MainWindow()
{}

void MainWindow::sockConnect()
{
    m_socket->connectToHost("127.0.0.1", 5555);
}

void MainWindow::sockGetWorkers()
{
    if(m_socket->isOpen())
    {
        m_socket->write("{\"type\":\"select\", \"params\":\"interface\"}");
        m_socket->waitForBytesWritten(500);
    }
    else{
        QMessageBox::information(this, "Info", "Сonnection not established");
    }
}

void MainWindow::sockReady()
{
    if(m_socket->waitForConnected(500)){
        m_socket->waitForReadyRead(500);
        m_data = m_socket->readAll();

        m_jdoc = QJsonDocument::fromJson(m_data, &m_jdoc_error);

        if(m_jdoc_error.errorString().toInt() == QJsonParseError::NoError){
            if((m_jdoc.object().value("type").toString() == "connect")
                && (m_jdoc.object().value("status").toString() == "open")){
                QMessageBox::information(this, "Info", "Success connect");
            }
            else if(m_jdoc.object().value("type").toString() == "resultSelect")
            {
                QStandardItemModel* model = new QStandardItemModel(nullptr);
                model->setHorizontalHeaderLabels(QStringList() << "name");

                QJsonArray docAr = m_jdoc.object().value("result").toArray();
                for(int i=0; i<docAr.count(); ++i)
                {
                    QStandardItem* col = new QStandardItem(docAr[i].toObject().value("name").toString());
                    model->appendRow(col);
                }
                m_table->setModel(model);
            }
            else{
                QMessageBox::information(this, "Info", "Сonnection not established");
            }
        }
        else{
            QMessageBox::information(this, "Info", "Error with format of data transmission");
        }
    }
}

void MainWindow::sockDisconect()
{
    m_socket->deleteLater();
}

