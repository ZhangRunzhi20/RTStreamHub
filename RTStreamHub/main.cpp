#include <QCoreApplication>
#include "QStrSvr.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
void signalHandler(int signum){
    printf("Interrupt signal (%d) received.\n",signum);
    fflush(stdout);
    QCoreApplication::quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    signal(SIGINT,signalHandler);
    signal(SIGTERM,signalHandler);

    QStrSvr temp;
    temp.initVar();

    return a.exec();
}
