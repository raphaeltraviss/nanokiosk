#include "SocketServer.h"


SocketServer::SocketServer(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Initializing the socket server container";
}

SocketServer::~SocketServer() {
  stopServer();
}


void SocketServer::startServer(QBluetoothAddress const& localAdapter)
{
  qWarning() << "Cleaning failed server instances, if present";
  serverHandle->removeServer("test-server.sock");
  qWarning() << "Creating the socket server";
  serverHandle = new QLocalServer(this);
  qWarning() << "Starting socket server";
  QObject::connect(serverHandle, SIGNAL(newConnection()),
                   this,         SLOT(handleConnection())); 
  serverHandle->listen("test-server.sock");
}

void SocketServer::stopServer()
{
  qWarning() << "STOPPING socket server";
  if (activeConnection) {
    activeConnection->disconnectFromServer();
    activeConnection = nullptr;
  }
  if (serverHandle) {
    serverHandle->close();
    serverHandle->removeServer("test-server.sock");
    serverHandle = nullptr;

  }
}

void SocketServer::sendMessage(QString const& name)
{
  qWarning() << "Sending socket message";
}

void SocketServer::handleConnection()
{
  qWarning() << "New client requesting connection";
  activeConnection = serverHandle->nextPendingConnection();
  QObject::connect(activeConnection, SIGNAL(readyRead()),
                   this,         SLOT(handleText())); 
}

void SocketServer::handleText() {
  qDebug() << activeConnection->readAll();
}
