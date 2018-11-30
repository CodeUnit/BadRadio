/*
 * MpdWidget.h
 *
 *  Created on: 07.11.2015
 *      Author: gunit
 */

#ifndef MPDWIDGET_H_
#define MPDWIDGET_H_

#include <QDialog>
#include <QtWidgets>
#include <QDebug>

#include <connection.h>

#include "ScrollText.h"
#include "LED.h"

class MpdWidget: public QWidget {

	Q_OBJECT

public:
	MpdWidget(QWidget *parent = 0);
	virtual ~MpdWidget();

private:
	void handle_error(struct mpd_connection *c);
	QTimer *timerMpd;
	QPushButton *buttonPlay, *buttonStop, *buttonNext, *buttonPrev;
	ScrollText *labelSender, *labelVol, *labelTitle;
	bool aktPlay, aktStop, aktNext, aktPrev;


private slots:
	void psExit();
	void psMpdHB();
	void slotPlay();
	void slotStop();
	void slotNext();
	void slotPrev();

signals:
	void closeWdg();

};

#endif /* MPDWIDGET_H_ */
