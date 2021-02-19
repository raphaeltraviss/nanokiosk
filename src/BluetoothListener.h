#pragma once

#include <QtCore>
#include <QtBluetooth>


class BluetoothListener {
public:
    virtual ~BluetoothListener(){}

    virtual void startServer(QBluetoothAddress const& address) = 0;
    virtual void stopServer() = 0;

signals:
    virtual void sendMessage(const QString &message) = 0;
    virtual void messageReceived(const QString &sender, const QString &message) = 0;
    virtual void clientConnected(const QString &name) = 0;
    virtual void clientDisconnected(const QString &name) = 0;
};

Q_DECLARE_INTERFACE(BluetoothListener, "BluetoothListener");
