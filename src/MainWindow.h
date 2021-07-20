#pragma once

#include <QtWidgets>
#include <QtQuick>
#include <QQuickWidget>
#include "BluetoothServer.h"
#include "BluetoothListener.h"

class MainWindow : public QMainWindow
{
		Q_OBJECT


public:
  MainWindow(
    QWidget *parent = Q_NULLPTR,
    QString keymap = "",
    bool willDemo = false,
    QString demoScene = ""
  );
  enum KeyCommand { zoom_in, zoom_out, zoom_fit };
  enum UIState {
    idle,
    pairing,
    connected,
    image_loaded
  };

public slots:
  void openConnection();
  void closeConnection();
  void logMessage(QString const& subject);
  void pairClient(QString const& subject);
  void unpairClient(QString const& subject);
  void setImageUrl(QString const& sender, QString const& url);

protected:
	void resizeEvent(QResizeEvent * event);

private:
	void setupRootView();
	void attachComms();
	void attachView();
  UIState stateFor(QString stateAbbr);
  void printKeys();
  void startDemo(QString stateAbbr);
  QQuickWidget* ui;
  BluetoothListener* bt_server;
  QList<QKeySequence> keyseq;
  QKeySequence keyEventToSequence(QKeyEvent* keyEvent);
	bool eventFilter(QObject *obj, QEvent *ev);
};
