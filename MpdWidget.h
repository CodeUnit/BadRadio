/*
 * MpdWidget.h
 *
 *  Created on: 07.11.2015
 *      Author: gunit
 */

#ifndef MPDWIDGET_H_
#define MPDWIDGET_H_

#include <QDialog>
#include <QtGui>

#include <connection.h>

class MpdWidget: public QWidget {

	Q_OBJECT

public:
	MpdWidget(QWidget *parent = 0);
	virtual ~MpdWidget();

private:
	void mpd();
	void handle_error(struct mpd_connection *c);
	QListWidget *listWdg;

private slots:
	void psExit();

signals:
	void closeWdg();

};

#endif /* MPDWIDGET_H_ */
