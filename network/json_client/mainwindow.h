#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QStandardItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTcpSocket* m_socket;
    QVBoxLayout* m_main_layout;
    QPushButton* m_pb_connect;
    QPushButton* m_get_list;
    QTableView* m_table;
    QByteArray m_data;

    QJsonDocument m_jdoc;
    QJsonParseError m_jdoc_error;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void sockConnect();
    void sockGetWorkers();
    void sockReady();
    void sockDisconect();

};
#endif // MAINWINDOW_H
