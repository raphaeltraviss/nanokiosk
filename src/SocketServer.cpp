#include "SocketServer.h"


SocketServer::SocketServer(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Creating the socket server";
  serverHandle = new QLocalServer(this);


  QObject::connect(serverHandle, SIGNAL(newConnection),
                   this,         SLOT(handleConnection)); 
}

SocketServer::~SocketServer() {
  stopServer();
}


void SocketServer::startServer(QBluetoothAddress const& localAdapter)
{
  qWarning() << "Starting socket server";
  serverHandle->listen("test-server");
}

void SocketServer::stopServer()
{
  qWarning() << "Starting socket server";
}

void SocketServer::sendMessage(QString const& name)
{
  qWarning() << "Sending socket message";
}

void SocketServer::handleConnection()
{
  qWarning() << "New client requesting connection";
}
