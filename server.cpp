#include "server.h"

Server::Server(QObject *parent) : QThread(parent)
{
}

void Server::run()
{
    m_socket = new QUdpSocket(this);
}
