#include "ConsoleListener.hpp"



// Initializer

ConsoleListener::ConsoleListener(QObject *parent)
  : QObject(parent)
{
  qWarning() << "Initializing the console listener";
}


// Native object methods

void ConsoleListener::startServer(QBluetoothAddress const& addr) {
  qWarning() << "Starting the console listener";
}

void ConsoleListener::stopServer() {
  qWarning() << "Stopping the console listener";
}


// MARK: public slots


void ConsoleListener::sendMessage(QString const& message) {
  qWarning() << "Sending message... " << message;
}


// MARK: private slots

void ConsoleListener::handleConnection()
{
  qWarning() << "New serial client requesting connection";
  emit clientConnected("SOME_IDENTIFIER");
}

void ConsoleListener::handleText()
{
  qWarning() << "New serial client requesting connection";
  emit commandLoadImage("console", "https://picsum.photos/2000/3000");
}

