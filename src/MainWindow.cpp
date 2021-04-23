#include "MainWindow.h"
#include "BluetoothServer.h"
#include "SocketServer.h"
#include "SerialServer.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>


MainWindow::MainWindow(QWidget *parent, QKeySequence keyseq, bool willDemo, QString sceneAbbr)
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
    startDemo(sceneAbbr);
  }
}

MainWindow::DemoScene MainWindow::sceneFor(QString sceneAbbr) {
  MainWindow::DemoScene scene;

  if (sceneAbbr == "raw") {
    scene = MainWindow::DemoScene::raw;
  }
  else if (sceneAbbr == "img") {
    scene = MainWindow::DemoScene::image_loaded;
  }
  else {
    scene = MainWindow::DemoScene::raw;
  }

  return scene;
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

void MainWindow::startDemo(QString sceneAbbr) {
  MainWindow::DemoScene scene = sceneFor(sceneAbbr);

  qDebug() << "Demo mode activated!";
  qDebug() << "Setting up scene " << scene;
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
  bt_server = new SocketServer(this);

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

    //qDebug() << "key" << keyValue << " press on " << object;

    if (keyValue == keyFor(MainWindow::KeyCommand::zoom_in)) {
      QMetaObject::invokeMethod(ui->rootObject(), "zoomIn");
    }
    else if (keyValue == keyFor(MainWindow::KeyCommand::zoom_out)) {
      QMetaObject::invokeMethod(ui->rootObject(), "zoomOut");
    }
    else if (keyValue == keyFor(MainWindow::KeyCommand::zoom_fit)) {
      QMetaObject::invokeMethod(ui->rootObject(), "scaleToFit");
    }

    return true;
  }
  return false;
}
