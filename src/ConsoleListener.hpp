#pragma once

#include "BluetoothListener.h"
#include <iostream>


class ConsoleListener: public QObject, public BluetoothListener
{
  Q_OBJECT
  Q_INTERFACES(BluetoothListener)

  QSocketNotifier* m_notify;

public:
    explicit ConsoleListener(QObject *parent = nullptr);
    ~ConsoleListener(){}

    void startServer(QBluetoothAddress const& address) = 0;
    void stopServer() = 0;

public slots:
  void sendMessage(const QString &message);

signals:
  void messageReceived(const QString &sender, const QString &message);
  void clientConnected(const QString &name);
  void clientDisconnected(const QString &name);
  void commandLoadImage(const QString &sender, const QString &url);

private slots:
  void handleText();
};
