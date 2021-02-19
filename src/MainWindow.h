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
  void handleInitPairing();
  void logMessage(QString const& subject);

protected:
	void resizeEvent(QResizeEvent * event);

private:
	void setup_root_view();
  QQuickWidget* responsive_view;
  BluetoothListener* bt_server;
	bool eventFilter(QObject *obj, QEvent *ev);
};
