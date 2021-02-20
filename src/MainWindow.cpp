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
  setup_root_view();
  resize(1200, 1920);
  responsive_view->resize(1200, 1920);

}


void MainWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
  view->setStyleSheet("background-color:black;");

  view->installEventFilter(this);

  QObject::connect(view->rootObject(), SIGNAL(initPairing()), this, SLOT(handleInitPairing()));
	responsive_view = view;

  bt_server = new SocketServer(this);
}


void MainWindow::handleInitPairing() {
  qDebug() << "Initializing bluetooth peripheral server";

  QList<QBluetoothHostInfo> localAdapters = QBluetoothLocalDevice::allDevices();
  foreach (QBluetoothHostInfo bt_dev, localAdapters) {
    qDebug() << bt_dev.name();
    qDebug() << bt_dev.address();
  }
  QBluetoothAddress bt_addr = localAdapters.at(0).address();

  QObject::connect(dynamic_cast<QObject*>(bt_server), SIGNAL(messageReceived(const QString, const QString)),
               this, SLOT(logMessage(QString const&)));

  bt_server->startServer(bt_addr);
}

void MainWindow::logMessage(QString const& subject) {
  qDebug() << "Received bluetooth event: " << subject;
}


void MainWindow::resizeEvent(QResizeEvent * event) {
	int the_width = event->size().width();
	responsive_view->resize(the_width, responsive_view->height());
}


bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

    const int keyValue = keyEvent->key();

    qDebug() << "key" << keyValue << " press on " << object;

    if (keyValue == up) {
      responsive_view->rootObject()->setProperty("myState", "UP WAS PRESSED");
    }
    else if (keyValue == down) {
      qDebug() << "down was pressed!";
    }

    return true;
  }
  return false;
}
