#include "SocketServer.h"


SocketServer::SocketServer(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Creating the socket server";
}

SocketServer::~SocketServer() {
  stopServer();
}


void SocketServer::startServer(QBluetoothAddress const& localAdapter)
{
  qWarning() << "Starting socket server";
}

void SocketServer::stopServer()
{
  qWarning() << "Starting socket server";
}

void SocketServer::sendMessage(QString const& name)
{
  qWarning() << "Sending socket message";
}
