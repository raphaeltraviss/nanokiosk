#include "SerialServer.h"


SerialServer::SerialServer(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Initializing the socket server container";
}

SerialServer::~SerialServer() {
  stopServer();
}


void SerialServer::startServer(QBluetoothAddress const& localAdapter)
{
  if (!serialPort) {
		qDebug() << "Serial port already opened!";
    return
  }

  activePort = new QSerialPort(this);

	activePort->setPortName("COM3");
	activePort->setBaudRate(QSerialPort::Baud9600);
	activePort->setDataBits(QSerialPort::Data8);
	activePort->setParity(QSerialPort::NoParity);
	activePort->setStopBits(QSerialPort::OneStop);
	activePort->setFlowControl(QSerialPort::NoFlowControl);

	if (!serialPort->open(QIODevice::ReadOnly)) {
		qDebug() << "Serial port cannot be opened!";
		stopServer();
	}
}

void SerialServer::stopServer()
{
  qWarning() << "STOPPING serial server";
  if (activePort) {
    activePort = nullptr;
  }
}

void SerialServer::sendMessage(QString const& name)
{
  qWarning() << "Sending serial message";
}

void SerialServer::handleConnection()
{
  qWarning() << "New serial client requesting connection";
  emit clientConnected("COM3");
}

void SerialServer::handleText() {
  // @TODO read command line from serial port
  // QByteArray data = activeConnection->readAll();
  // QString commandLine = QString::fromUtf8(data).trimmed();
  QString commandLine = "load https://picsum.photos/3000/4000";
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







