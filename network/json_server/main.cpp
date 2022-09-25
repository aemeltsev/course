#include <QCoreApplication>
#include "jserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JServer server;
    server.startJServer();

    return a.exec();
}
