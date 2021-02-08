#pragma once

#include <QtWidgets>
#include <QtQuick>
#include <QQuickWidget>

class MainWindow : public QMainWindow
{
		Q_OBJECT

public:
  MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
  void doStuff();

protected:
	void resizeEvent(QResizeEvent * event);

private:
	void setup_root_view();
	QQuickWidget * responsive_view;
	bool eventFilter(QObject *obj, QEvent *ev);

};
