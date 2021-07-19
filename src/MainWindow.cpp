#include "MainWindow.h"
#include "BluetoothServer.h"
#include "SocketServer.h"
#include "SerialServer.h"
#include "ConsoleListener.hpp"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>


MainWindow::MainWindow(
    QWidget *parent,
    QKeySequence keyseq,
    bool willDemo,
    QString stateAbbr
)
	: QMainWindow(parent)
{
  setupRootView();
  attachView();
  attachComms();

  if (keyseq.count() > 0) {
    this->keyseq = keyseq;
    printKeys();
  }

  if (willDemo) {
    startDemo(stateAbbr);
  }
}

MainWindow::UIState MainWindow::stateFor(QString stateSymbol) {
  MainWindow::UIState state;

  if (stateSymbol == "idle") {
    state = MainWindow::UIState::idle;
  }
  else if (stateSymbol == "pair") {
    state = MainWindow::UIState::pairing;
  }
  else if (stateSymbol == "conn") {
    state = MainWindow::UIState::connected;
  }
  else if (stateSymbol == "img") {
    state = MainWindow::UIState::image_loaded;
  }
  else {
    state = MainWindow::UIState::idle;
  }

  return state;
}

int MainWindow::keyFor(MainWindow::KeyCommand cmd) {
  if (keyseq.count() < cmd) { return 0; }
  return keyseq[cmd];
}

void MainWindow::printKeys() {
  QStringList humanKey = keyseq.toString().split(",");

  qDebug() << "Keymap provided via command-line option...";
  qDebug() << "Zoom In bound to key: " << humanKey.at(0);
  qDebug() << "Zoom Out bound to key: " << humanKey.at(1);
  qDebug() << "Zoom Fit bound to key: " << humanKey.at(2);

  qDebug().noquote() << "\n";
}

void MainWindow::startDemo(QString stateSymbol) {
  MainWindow::UIState state = stateFor(stateSymbol);

  switch (state) {
    case MainWindow::UIState::idle:
      qDebug("setting up idle state");
      break;
    case MainWindow::UIState::pairing:
      qDebug("setting up pairing state");
      break;
    case MainWindow::UIState::connected:
      qDebug("setting up connected state");
      break;
    case MainWindow::UIState::image_loaded:
      qDebug("setting up image_loaded state");

      // This URL works:
      //QUrl url("https://picsum.photos/2000/3000");

      // This one doesn't:
      QUrl url("faderhead_orig");

      // Neither does this one:
      //QUrl url = QUrl::fromLocalFile("assets/faderhead_orig.jpeg");

      QMetaObject::invokeMethod(ui->rootObject(), "loadImage",
        Q_ARG(QVariant, url));
      break;
  }
}

void MainWindow::setupRootView()
{
	QQuickWidget *view = new QQuickWidget;

	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
  view->setStyleSheet("background-color:black;");
  view->installEventFilter(this);

  resize(1200, 1300);
  view->resize(this->width(), this->height());

	ui = view;
}

void MainWindow::attachView() {
  QObject::connect(ui->rootObject(), SIGNAL(pleaseOpenConnection()), this, SLOT(openConnection()));
  QObject::connect(ui->rootObject(), SIGNAL(pleaseCloseConnection()), this, SLOT(closeConnection()));
}

void MainWindow::attachComms() {
  //bt_server = new SocketServer(this);
  bt_server = new ConsoleListener(this);

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(messageReceived(const QString, const QString)),
               this, SLOT(logMessage(QString const&)));

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(clientConnected(const QString)),
               this, SLOT(pairClient(QString const&)));

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(clientDisconnected(const QString)),
               this, SLOT(unpairClient(QString const&)));

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(commandLoadImage(const QString, const QString)),
               this, SLOT(setImageUrl(QString const&, QString const&)));
}

void MainWindow::openConnection() {
  QList<QBluetoothHostInfo> localAdapters = QBluetoothLocalDevice::allDevices();
  QBluetoothAddress bt_addr = localAdapters.at(0).address();

  bt_server->startServer(bt_addr);
}

void MainWindow::closeConnection() {
  bt_server->stopServer();
  // @TODO: check that it was stopped successfully
  QMetaObject::invokeMethod(ui->rootObject(), "toIdle");
}

void MainWindow::logMessage(QString const& subject) {
  qDebug() << "Received bluetooth event: " << subject;
}

void MainWindow::pairClient(QString const& subject) {
  qDebug() << "Paired with client: " << subject;
  QMetaObject::invokeMethod(ui->rootObject(), "toConnected");
}

void MainWindow::unpairClient(QString const& subject) {
  qDebug() << "Unpaired client: " << subject;
}

void MainWindow::setImageUrl(QString const& sender, QString const& url) {
  qDebug() << sender << " is setting the image URL to" << url;
  QMetaObject::invokeMethod(ui->rootObject(), "loadImage",
     Q_ARG(QVariant, url));
}

void MainWindow::resizeEvent(QResizeEvent * event) {
	int the_width = event->size().width();
	ui->resize(the_width, ui->height());
}


bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

    const int keyValue = keyEvent->key();

    qDebug() << "key" << keyValue << " press on " << object;

    if (
        keyValue == keyFor(MainWindow::KeyCommand::zoom_in)
        ||
        keyValue == 43 // hard-coded plus
      ) {
      QMetaObject::invokeMethod(ui->rootObject(), "zoomIn");
    }
    else if (
        keyValue == keyFor(MainWindow::KeyCommand::zoom_out)
        ||
        keyValue == 45 // hard-coded minus
      ) {
      QMetaObject::invokeMethod(ui->rootObject(), "zoomOut");
    }
    else if (keyValue == keyFor(MainWindow::KeyCommand::zoom_fit)) {
      QMetaObject::invokeMethod(ui->rootObject(), "scaleToFit");
    }

    return true;
  }
  return false;
}
