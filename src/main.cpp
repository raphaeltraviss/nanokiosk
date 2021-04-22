#include <QtWidgets>
#include <QDebug>
#include <QCommandLineParser>
#include "MainWindow.h"
#include "BluetoothServer.h"



int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("nanokiosk");
  QCoreApplication::setApplicationVersion("0.8.8");

  QCommandLineParser parser;
  parser.setApplicationDescription("Nanokiosk graphic terminal");
  parser.addHelpOption();
  parser.addVersionOption();


  QCommandLineOption windowOption(QStringList() << "w" << "windowed",
            QCoreApplication::translate("main", "Windowed mode for local dev"));
  parser.addOption(windowOption);

  QCommandLineOption keymapOption(QStringList() << "k" << "keymap",
            QCoreApplication::translate("main", "Keymap of command index to physical key binding"));
  keymapOption.setValueName("keymap");
  parser.addOption(keymapOption);

  parser.process(app);

  QString keymap = parser.value(keymapOption);
  QKeySequence keyseq(keymap);
  MainWindow the_window(Q_NULLPTR, keyseq);

  bool isWindowed = parser.isSet(windowOption);

  if (isWindowed) {
    the_window.show();
  }
  else {
    the_window.showFullScreen();
  }

  return app.exec();
}
