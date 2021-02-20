#include "SocketServer.h"


SocketServer::SocketServer(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Creating the socket server";
  serverHandle = new QLocalServer(this);
}

SocketServer::~SocketServer() {
  stopServer();
}


void SocketServer::startServer(QBluetoothAddress const& localAdapter)
{
  qWarning() << "Starting socket server";
  QObject::connect(serverHandle, SIGNAL(newConnection()),
                   this,         SLOT(handleConnection())); 
  serverHandle->listen("test-server.sock");
}

void SocketServer::stopServer()
{
  qWarning() << "STOPPING socket server";
}

void SocketServer::sendMessage(QString const& name)
{
  qWarning() << "Sending socket message";
}

void SocketServer::handleConnection()
{
  qWarning() << "New client requesting connection";
}
