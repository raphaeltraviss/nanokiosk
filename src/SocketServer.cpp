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
  emit clientConnected("test-server.sock");
}

void SocketServer::handleText() {
  QByteArray data = activeConnection->readAll();
  QString commandLine = QString::fromUtf8(data).trimmed();
  QStringList commands = commandLine.split(" ");
  qDebug() << commands;

  if (commands.isEmpty()) {
    qWarning("Skipped empty command");
    return;
  }
  
  QString command = commands.takeFirst();
  qDebug() << command;

  QStringList commandList;
  commandList << "pair" << "unpair" << "send" << "accept" << "load";

  switch (commandList.indexOf(command)) {
    case 0: // pair
      emit clientConnected("test-server.sock");
      break;
    case 1: // unpair
      emit clientDisconnected("test-server.sock");
      break;
    case 2: // send
      // @TODO: call slot with data from the app's signal
      break;
    case 3: // accept
      emit messageReceived("test-server.sock", "A Bluetooth message.");
      break;
    case 4: // load
      QString url;
      if (commands.isEmpty()) {
        url = "https://picsum.photos/2000/3000";
      }
      else {
        url = commands.takeFirst();
      }

      emit commandLoadImage("test-server.sock", url);
      break;
  }


}







