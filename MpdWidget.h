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

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <mpd/message.h>

#include <connection.h>

#include "ScrollText.h"
#include "LED.h"

class MpdWidget: public QWidget {

	Q_OBJECT

public:
	MpdWidget(QWidget *parent = 0);
	virtual ~MpdWidget();

private:
	struct mpd_connection *con;

    QWidget *mpdWdg;
    QWidget *playlistWdg;
    QStackedWidget *stackedWidget;

    void handle_error(struct mpd_connection *c);
	QTimer *timerMpd;
	QPushButton *buttonPlay, *buttonStop, *buttonNext, *buttonPrev, *buttonPlaylist, *buttonMpd;
	ScrollText *labelSender, *labelVol, *labelTitle;
	bool aktPlay, aktStop, aktNext, aktPrev;

protected:
	void resizeEvent(QResizeEvent *event);

private slots:
	void sltConnect();
	void psExit();
	void psMpdHB();
	void slotPlay();
	void slotStop();
	void slotNext();
	void slotPrev();
	void sltPlaylist();
	void sltMpd();

signals:
	void closeWdg();

};

#endif /* MPDWIDGET_H_ */
