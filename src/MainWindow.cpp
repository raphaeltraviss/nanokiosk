#include "MainWindow.h"
#include "BluetoothServer.h"
#include "SocketServer.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>


constexpr int up = 16777236;
constexpr int down = 16777234;
constexpr int released = 16777250;



MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
  setupRootView();
  resize(1200, 1920);
  ui->resize(1200, 1920);
}


void MainWindow::setupRootView()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
  view->setStyleSheet("background-color:black;");

  view->installEventFilter(this);

	ui = view;

  attachComms();
}


void MainWindow::attachComms() {
  bt_server = new SocketServer(this);

  QObject::connect(ui->rootObject(), SIGNAL(pleaseOpenConnection()), this, SLOT(openConnection()));
  QObject::connect(ui->rootObject(), SIGNAL(pleaseCloseConnection()), this, SLOT(closeConnection()));


  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(messageReceived(const QString, const QString)),
               this, SLOT(logMessage(QString const&)));

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(clientConnected(const QString)),
               this, SLOT(pairClient(QString const&)));

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(clientDisconnected(const QString)),
               this, SLOT(unpairClient(QString const&)));
}

void MainWindow::openConnection() {
  qDebug() << "Opening the client connection";

  QList<QBluetoothHostInfo> localAdapters = QBluetoothLocalDevice::allDevices();
  foreach (QBluetoothHostInfo bt_dev, localAdapters) {
    qDebug() << bt_dev.name();
    qDebug() << bt_dev.address();
  }
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

    if (keyValue == up) {
      ui->rootObject()->setProperty("myState", "UP WAS PRESSED");
    }
    else if (keyValue == down) {
      qDebug() << "down was pressed!";
    }

    return true;
  }
  return false;
}
