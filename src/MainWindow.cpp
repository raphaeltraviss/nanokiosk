#include "MainWindow.h"
#include "BluetoothServer.h"

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
  bt_server = new BluetoothServer(this);
}


void MainWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
  view->setStyleSheet("background-color:black;");

  view->installEventFilter(this);

  QObject::connect(view->rootObject(), SIGNAL(initPairing()), this, SLOT(doStuff()));
	responsive_view = view;
}


void MainWindow::doStuff() {
  qDebug() << "Hey there";
  bt_server->startServer();
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
