/*
 * MpdWidget.cpp
 *
 *  Created on: 07.11.2015
 *      Author: gunit
 */

#include <QTextStream>

#include "MpdWidget.h"

MpdWidget::MpdWidget(QWidget *parent) : QWidget(parent)
, aktPlay(false), aktStop(false), aktNext(false), aktPrev(false)
{

	con = NULL;
    mpdWdg = new QWidget;
    playlistWdg = new QWidget;

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(mpdWdg);
    stackedWidget->addWidget(playlistWdg);


	timerMpd = new QTimer();
	timerMpd->setInterval(100);
	connect(timerMpd, SIGNAL(timeout()), this, SLOT(psMpdHB()));
	timerMpd->start();

	QSize buttonSize(64, 64);


// MPD Design
	LED *led = new LED();
	led->setLedSize(10);

	labelSender = new ScrollText("SenderSenderSenderSenderSenderSender");
	labelVol = new ScrollText("VolVolVolVolVolVolVolVolVolVolVolVolVol");
	labelTitle = new ScrollText("TitelTitelTitelTitelTitelTitelTitelTitel");

	buttonPlay = new QPushButton("Play");
	buttonPlay->setFixedSize(buttonSize);
	connect(buttonPlay, SIGNAL(clicked()), this, SLOT(slotPlay()));
	buttonStop = new QPushButton("Stop");
	buttonStop->setFixedSize(buttonSize);
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(slotStop()));
	buttonNext = new QPushButton("Next");
	buttonNext->setFixedSize(buttonSize);
	connect(buttonNext, SIGNAL(clicked()), this, SLOT(slotNext()));
	buttonPrev = new QPushButton("Prev");
	buttonPrev->setFixedSize(buttonSize);
	connect(buttonPrev, SIGNAL(clicked()), this, SLOT(slotPrev()));
	buttonPlaylist = new QPushButton("Playlist");
	buttonPlaylist->setFixedSize(buttonSize);
	connect(buttonPlaylist, SIGNAL(clicked()), this, SLOT(sltPlaylist()));


	QBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(stackedWidget);

	QGridLayout *mpdWdgLayout = new QGridLayout(mpdWdg);
	mpdWdgLayout->addWidget(labelTitle, 0, 0, 1, 3);
	mpdWdgLayout->addWidget(led, 0, 3, Qt::AlignRight);
	mpdWdgLayout->addWidget(labelSender, 1, 0, 1, 4);
	mpdWdgLayout->addWidget(labelVol, 2, 0, 1, 4);
	mpdWdgLayout->addWidget(buttonPrev, 3, 0);
	mpdWdgLayout->addWidget(buttonPlay, 3, 1);
	mpdWdgLayout->addWidget(buttonStop, 3, 2);
	mpdWdgLayout->addWidget(buttonNext, 3, 3);
	mpdWdgLayout->addWidget(buttonPlaylist, 4, 3);


// Playlist Design
	buttonMpd = new QPushButton("Back");
	buttonMpd->setFixedSize(buttonSize);
	connect(buttonMpd, SIGNAL(clicked()), this, SLOT(sltMpd()));

	QGridLayout *playlistWdgLayout = new QGridLayout(playlistWdg);
	playlistWdgLayout->addWidget(buttonMpd, 0, 0);
	playlistWdgLayout->addWidget(new QLabel("Hallo"), 0, 1);
	playlistWdgLayout->addWidget(new QLabel("Hallo"), 1, 0);

	setLayout(mainLayout);


}

MpdWidget::~MpdWidget()
{
}

void MpdWidget::sltConnect()
{
	con = mpd_connection_new(NULL, 0, 30000);
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

	if (aktNext)
	{
		aktNext = false;
		mpd_send_command(conn, "next", NULL);
		timerMpd->start();
		return;
	}

	if (aktPrev)
	{
		aktPrev = false;
		mpd_send_command(conn, "previous", NULL);
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

void MpdWidget::slotNext()
{
	aktNext = true;
}

void MpdWidget::slotPrev()
{
	aktPrev = true;
}

void MpdWidget::psExit()
{
	emit closeWdg();
}

void MpdWidget::sltMpd()
{
	stackedWidget->setCurrentIndex(0);
}

void MpdWidget::sltPlaylist()
{
	stackedWidget->setCurrentIndex(1);
}


void MpdWidget::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);

}




