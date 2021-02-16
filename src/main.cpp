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

  return app.exec();
}
