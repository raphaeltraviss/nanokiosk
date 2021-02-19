#pragma once

#include <QtCore>
#include <QtBluetooth>
#include "BluetoothListener.h"


class BluetoothServer : public QObject, public BluetoothListener
{
  Q_OBJECT
  Q_INTERFACES(BluetoothListener)

public:
  explicit BluetoothServer(QObject *parent = nullptr);
  ~BluetoothServer();

  void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
  void stopServer();

public slots:
  void sendMessage(const QString &message);

signals:
  void messageReceived(const QString &sender, const QString &message);
  void clientConnected(const QString &name);
  void clientDisconnected(const QString &name);

private slots:
  void clientConnected();
  void clientDisconnected();
  void readSocket();

private:
    QBluetoothServer *rfcommServer = nullptr;
    QBluetoothServiceInfo serviceInfo;
    QList<QBluetoothSocket *> clientSockets;
};
