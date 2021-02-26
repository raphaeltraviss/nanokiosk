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
  MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
  void openConnection();
  void closeConnection();
  void logMessage(QString const& subject);
  void pairClient(QString const& subject);
  void unpairClient(QString const& subject);

protected:
	void resizeEvent(QResizeEvent * event);

private:
	void setupRootView();
	void attachComms();
  QQuickWidget* ui;
  BluetoothListener* bt_server;
	bool eventFilter(QObject *obj, QEvent *ev);
};
