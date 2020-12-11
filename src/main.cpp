#include <QtWidgets>
#include "MainWindow.h"



int main(int argc, char *argv[])
{
  QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
  QApplication app(argc, argv);
  MainWindow the_window;
  the_window.show();

  return app.exec();
}
