/*
 * MpdWidget.cpp
 *
 *  Created on: 07.11.2015
 *      Author: gunit
 */

#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <mpd/message.h>

#include "MpdWidget.h"

MpdWidget::MpdWidget(QWidget *parent) : QWidget(parent)
, aktPlay(false), aktStop(false)
{

	timerMpd = new QTimer();
	timerMpd->setInterval(100);
	connect(timerMpd, SIGNAL(timeout()), this, SLOT(psMpdHB()));
	timerMpd->start();


	labelSender = new ScrollText();
	labelVol = new ScrollText();
	labelTitle = new ScrollText();

	buttonPlay = new QPushButton("Play");
	connect(buttonPlay, SIGNAL(clicked()), this, SLOT(slotPlay()));
	buttonStop = new QPushButton("Stop");
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(slotStop()));

	QBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(buttonPlay);
	buttonLayout->addWidget(buttonStop);

	QBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(labelTitle);
	mainLayout->addWidget(labelSender);
	mainLayout->addWidget(labelVol);
	mainLayout->addLayout(buttonLayout);



	setLayout(mainLayout);


}

MpdWidget::~MpdWidget()
{
}


void MpdWidget::psMpdHB()
{

	timerMpd->stop();


	QString dataSender, dataVol, dataTitle;

	struct mpd_connection *conn;
	struct mpd_status * status;
	struct mpd_song *song;
//	const struct mpd_audio_format *audio_format;

	conn = mpd_connection_new(NULL, 0, 30000);


	if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
	{
		timerMpd->start();
		return;
	}

	if (aktPlay)
	{
		aktPlay = false;
		mpd_send_command(conn, "play", NULL);
		timerMpd->start();
		return;
	}

	if (aktStop)
	{
		aktStop = false;
		mpd_send_command(conn, "stop", NULL);
		timerMpd->start();
		return;
	}


	mpd_command_list_begin(conn, true);
	mpd_send_status(conn);
	mpd_send_current_song(conn);
	mpd_command_list_end(conn);


// Status
	status = mpd_recv_status(conn);
	if (status == NULL)
	{
		timerMpd->start();
		return ;
	}



// Volume
	dataVol.number(mpd_status_get_volume(status));
	if (labelVol->text().compare(dataVol) != 0)
		labelVol->setText(dataVol);

	if (mpd_status_get_error(status) != NULL)
		new QListWidgetItem(QString("status error: %1").
				arg(mpd_status_get_error(status)));



	mpd_status_free(status);
// Status

	mpd_response_next(conn);

// Song
	song = mpd_recv_song(conn);
	if (song == NULL)
	{
		handle_error(conn);
		timerMpd->start();
		return ;
	}


// Title
	dataTitle = mpd_song_get_uri(song);
	if (labelTitle->text().compare(dataTitle) != 0)
		labelTitle->setText(dataTitle);




	unsigned int i = 0;
	QString value;

	while ((value = mpd_song_get_tag(song, MPD_TAG_TITLE, i++)) != NULL)
	{
		if (i > 0)
			dataSender.append("  ");
		dataSender.append(value);
	}

	if (labelSender->text().compare(dataSender) != 0)
	{
		labelSender->setText(dataSender);
		qDebug() << "refresh";
	}

	mpd_song_free(song);
// Song

	mpd_connection_free(conn);

	timerMpd->start();
}


void MpdWidget::handle_error(struct mpd_connection *c)
{
//	new QListWidgetItem(QString("ErrorCode: %1")
//			.arg(mpd_connection_get_error_message(c)), listWdg);
	mpd_connection_free(c);
}

void MpdWidget::slotPlay()
{
	aktPlay = true;
}

void MpdWidget::slotStop()
{
	aktStop = true;
}

void MpdWidget::psExit()
{
	emit closeWdg();
}

