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

#include "ScrollText.h"

class MpdWidget: public QWidget {

	Q_OBJECT

public:
	MpdWidget(QWidget *parent = 0);
	virtual ~MpdWidget();

private:
	void handle_error(struct mpd_connection *c);
	QTimer *timerMpd;
	QPushButton *buttonPlay, *buttonStop;
	ScrollText *labelSender, *labelVol, *labelTitle;
	bool aktPlay, aktStop;


private slots:
	void psExit();
	void psMpdHB();
	void slotPlay();
	void slotStop();

signals:
	void closeWdg();

};

#endif /* MPDWIDGET_H_ */
