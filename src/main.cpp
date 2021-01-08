#include <QtWidgets>
#include <QDebug>
#include "MainWindow.h"
#include "BluetoothServer.h"



int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow the_window;
  //the_window.showFullScreen();
  the_window.show();

  QList<QBluetoothHostInfo> localAdapters = QBluetoothLocalDevice::allDevices();
  foreach (QBluetoothHostInfo bt_dev, localAdapters) {
    qDebug() << bt_dev.name();
    qDebug() << bt_dev.address();
  }

  BluetoothServer* bt = new BluetoothServer(&the_window);
  QBluetoothAddress bt_addr = localAdapters.at(0).address();
  bt->startServer(bt_addr);

  return app.exec();
}
