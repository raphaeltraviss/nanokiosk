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
	resize(1024, 800);
	responsive_view->resize(1024, 800);
	request_list();
}


void MainWindow::setup_root_view()
{
	QQuickWidget *view = new QQuickWidget;
	view->setParent(this);
	view->setSource(QUrl("qrc:/main.qml"));
	view->setResizeMode(QQuickWidget::SizeRootObjectToView);
	responsive_view = view;
}

void MainWindow::resizeEvent(QResizeEvent * event) {
	int the_width = event->size().width();
	responsive_view->resize(the_width, responsive_view->height());
}

void MainWindow::request_list() {
	QNetworkAccessManager *net = new QNetworkAccessManager(this);
	connect(net, &QNetworkAccessManager::finished, this, &MainWindow::populate_list);

	net->get(QNetworkRequest(QUrl("http://localhost:18080/json")));
}

void MainWindow::populate_list(QNetworkReply* reply) {
	QByteArray data = reply->readAll();
	QJsonDocument the_json = QJsonDocument::fromJson(data);
  QJsonObject response = the_json.object();
	QJsonArray response_1 = response["crew"].toArray();
	qDebug() << response;
	for (int i = 0; i < response_1.count(); i++) {
		qDebug() << "HI!";
		qDebug() << response_1[i];
	}
}
