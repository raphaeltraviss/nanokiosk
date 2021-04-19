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
  MainWindow(QWidget *parent = Q_NULLPTR, QString keymap = "");

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
  QQuickWidget* ui;
  BluetoothListener* bt_server;
	bool eventFilter(QObject *obj, QEvent *ev);
};
