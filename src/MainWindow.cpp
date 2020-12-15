#include "MainWindow.h"

#include <QTextStream>
#include <QDebug>

#include <QWidget>
#include <QQuickWidget>
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setup_root_view();
  resize(1200, 1920);
	responsive_view->resize(1200, 1920);
}


void MainWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
  view->setStyleSheet("background-color:black;");
	responsive_view = view;
}

void MainWindow::resizeEvent(QResizeEvent * event) {
	int the_width = event->size().width();
	responsive_view->resize(the_width, responsive_view->height());
}

