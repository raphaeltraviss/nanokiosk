#pragma once

#include "BluetoothListener.h"

#include <QtCore>
#include <QLocalServer>
#include <QtBluetooth>


class SocketServer : public QObject, public BluetoothListener
{
  Q_OBJECT
  Q_INTERFACES(BluetoothListener)

public:
  explicit SocketServer(QObject *parent = nullptr);
  ~SocketServer();

  void startServer(QBluetoothAddress const& localAdapter);
  void stopServer();

public slots:
  void sendMessage(const QString &message);

signals:
  void messageReceived(const QString &sender, const QString &message);
  void clientConnected(const QString &name);
  void clientDisconnected(const QString &name);

private:
    QLocalServer* serverHandle = nullptr;
};
