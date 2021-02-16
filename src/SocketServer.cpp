#include "SocketServer.h"

#include <QtCore>
#include <QLocalServer>



SocketServer::SocketServer(QObject *parent)
  : QObject(parent)
{}

SocketServer::~SocketServer() {
  stopServer();
}


void SocketServer::startServer(QString const& name)
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
