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
#include <QTcpSocket>
#include <QHostAddress>

#include "ScrollText.h"
#include "LED.h"

class MpdWidget: public QWidget {

	Q_OBJECT

public:
	MpdWidget(QWidget *parent = 0);
	virtual ~MpdWidget();

private:
	LED *led;
	QTcpSocket *mpdSocket;
	QWidget *mpdWdg;
    QWidget *playlistWdg;
    QStackedWidget *stackedWidget;
	QTimer *timerMpd;
	QPushButton *buttonPlay, *buttonStop, *buttonNext, *buttonPrev, *buttonLeiser,
	*buttonLauter, *buttonPlaylist, *buttonMpd;
	ScrollText *labelSender, *labelVol, *labelTitle;
	bool aktPlay, aktStop, aktNext, aktPrev;
	bool toggleBool;
	quint8 volume;

protected:
	void resizeEvent(QResizeEvent *event);

private slots:
	void sltMpdConnect();
	void psExit();
	void sltMpdHB();
	void slotPlay();
	void slotStop();
	void slotNext();
	void slotPrev();
	void slotLeiser();
	void slotLauter();
	void sltPlaylist();
	void sltMpd();

	void sltConnected();
	void sltDisconnected();
	void sltReadyRead();
	void sltBytesWritten(qint64);

signals:
	void closeWdg();

};

#endif /* MPDWIDGET_H_ */
