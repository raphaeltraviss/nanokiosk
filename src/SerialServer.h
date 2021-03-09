#pragma once

#include "BluetoothListener.h"

#include <QtCore>
#include <QIODevice>
#include <QtBluetooth>
#include <QSerialPort>


class SerialServer : public QObject, public BluetoothListener
{
  Q_OBJECT
  Q_INTERFACES(BluetoothListener)

public:
  explicit SerialServer(QObject *parent = nullptr);
  ~SerialServer();

  // @TODO: remove address spec from interface; should just be a string ID
  void startServer(QBluetoothAddress const& localAdapter);
  void stopServer();

public slots:
  void sendMessage(const QString &message);

signals:
  void messageReceived(const QString &sender, const QString &message);
  void clientConnected(const QString &name);
  void clientDisconnected(const QString &name);
  void commandLoadImage(const QString &sender, const QString &url);

private:
  QSerialPort* activePort = nullptr;

private slots:
  void handleConnection();
  void handleText();
};
