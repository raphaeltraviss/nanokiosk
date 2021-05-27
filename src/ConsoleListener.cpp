#include "ConsoleListener.hpp"



// Initializer

ConsoleListener::ConsoleListener(QObject *parent)
  : QObject(parent)
{
  m_notify = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}


// Native object methods

void ConsoleListener::startServer(QBluetoothAddress const& addr) {
  qWarning() << "Starting the console listener";
  connect(m_notify, SIGNAL(activated(int)), this, SLOT(handleText()));
}

void ConsoleListener::stopServer() {
  qWarning() << "Stopping the console listener";
}


// MARK: public slots


void ConsoleListener::sendMessage(QString const& message) {
  qWarning() << "Sending message... " << message;
}


// MARK: private slots

void ConsoleListener::handleText()
{
  std::string line;
  std::getline(std::cin, line);
  if (std::cin.eof() || line == "quit") {
      std::cout << "Good bye!" << std::endl;
      emit clientDisconnected("console");
  } else {
      std::cout << "Echo: " << line << std::endl;
      std::cout << "> " << std::flush;
      emit messageReceived("console", QString::fromStdString(line));
  }
}

