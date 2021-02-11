#include "BluetoothServer.h"

#include <QtCore>
#include <QtBluetooth>

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

BluetoothServer::BluetoothServer(QObject *parent)
  :  QObject(parent)
{}

BluetoothServer::~BluetoothServer()
{
  stopServer();
}

void BluetoothServer::startServer(const QBluetoothAddress& localAdapter)
{
  if (rfcommServer) return;

  rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
  connect(rfcommServer, &QBluetoothServer::newConnection,
          this, QOverload<>::of(&BluetoothServer::clientConnected));
  bool result = rfcommServer->listen(localAdapter);
  if (!result) {
    qWarning() << "Cannot bind chat server to" << localAdapter.toString();
    return;
  }

  QBluetoothServiceInfo::Sequence profileSequence;
  QBluetoothServiceInfo::Sequence classId;
  classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
  classId << QVariant::fromValue(quint16(0x100));
  profileSequence.append(QVariant::fromValue(classId));
  serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
                            profileSequence);

  classId.clear();
  classId << QVariant::fromValue(QBluetoothUuid(serviceUuid));
  classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));

  serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);

  serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Nanokiosk"));
  serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                            tr("Art visualization device"));
  serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("skyleafdesign.com"));

  serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));

  QBluetoothServiceInfo::Sequence publicBrowse;
  publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
  serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                            publicBrowse);

  QBluetoothServiceInfo::Sequence protocolDescriptorList;
  QBluetoothServiceInfo::Sequence protocol;
  protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
  protocolDescriptorList.append(QVariant::fromValue(protocol));
  protocol.clear();
  protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
            << QVariant::fromValue(quint8(rfcommServer->serverPort()));
  protocolDescriptorList.append(QVariant::fromValue(protocol));
  serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                            protocolDescriptorList);

  serviceInfo.registerService(localAdapter);
}

void BluetoothServer::stopServer()
{
  serviceInfo.unregisterService();

  qDeleteAll(clientSockets);

  delete rfcommServer;
  rfcommServer = nullptr;
}

void BluetoothServer::sendMessage(const QString &message)
{
  QByteArray text = message.toUtf8() + '\n';

  for (QBluetoothSocket *socket : qAsConst(clientSockets))
    socket->write(text);
}

void BluetoothServer::clientConnected()
{
  QBluetoothSocket *socket = rfcommServer->nextPendingConnection();
  if (!socket) return;

  connect(socket, &QBluetoothSocket::readyRead, this, &BluetoothServer::readSocket);
  connect(socket, &QBluetoothSocket::disconnected, this, QOverload<>::of(&BluetoothServer::clientDisconnected));
  clientSockets.append(socket);
  emit clientConnected(socket->peerName());
}

void BluetoothServer::clientDisconnected()
{
  QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
  if (!socket) return;

  emit clientDisconnected(socket->peerName());

  clientSockets.removeOne(socket);

  socket->deleteLater();
}

void BluetoothServer::readSocket()
{
  QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
  if (!socket) return;

  while (socket->canReadLine()) {
    QByteArray line = socket->readLine().trimmed();
    emit messageReceived(
      socket->peerName(),
      QString::fromUtf8(
        line.constData(),
        line.length()
      )
    );
  }
}
