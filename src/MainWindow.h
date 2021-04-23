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
    QKeySequence keyseq = QKeySequence("FDA"),
    bool willDemo = false,
    QString demoScene = "new"
  );
  enum KeyCommand { zoom_in, zoom_out, zoom_fit };
  enum DemoScene { raw, image_loaded };

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
  int keyFor(KeyCommand cmd);
  DemoScene sceneFor(QString sceneAbbr);
  void printKeys();
  void startDemo(QString sceneAbbr);
  QQuickWidget* ui;
  BluetoothListener* bt_server;
  QKeySequence keyseq;
	bool eventFilter(QObject *obj, QEvent *ev);
};
