#pragma once

#include <QtCore>
#include <QLocalServer>


class SocketServer : public QObject
{
  Q_OBJECT

public:
  explicit SocketServer(QObject *parent = nullptr);
  ~SocketServer();

  void startServer(QString const& name);
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
