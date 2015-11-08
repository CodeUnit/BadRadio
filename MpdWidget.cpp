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
{
	listWdg = new QListWidget;

	QPushButton *pbExit = new QPushButton("Exit");
	connect(pbExit, SIGNAL(clicked()), this, SLOT(psExit()));

	QBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(listWdg);
	mainLayout->addWidget(pbExit);

	setLayout(mainLayout);

	mpd();
}

MpdWidget::~MpdWidget() {
	// TODO Auto-generated destructor stub
}


void MpdWidget::mpd()
{
	struct mpd_connection *conn;
	struct mpd_status * status;
	struct mpd_song *song;
//	const struct mpd_audio_format *audio_format;

	conn = mpd_connection_new(NULL, 0, 30000);


	if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
		return;

	for(int i=0 ; i < 3 ; i++)
		new QListWidgetItem(QString("Version %1: %2").
				arg(i).
				arg(mpd_connection_get_server_version(conn)[i]), listWdg);


	mpd_command_list_begin(conn, true);
	mpd_send_status(conn);
	mpd_send_current_song(conn);
	mpd_command_list_end(conn);


// Status
	status = mpd_recv_status(conn);
	if (status == NULL)
	{
		new QListWidgetItem("status: NULL", listWdg);
		return ;
	}


	new QListWidgetItem(QString("Volume: %1").
			arg(mpd_status_get_volume(status)), listWdg);

	if (mpd_status_get_error(status) != NULL)
		new QListWidgetItem(QString("status error: %1").
				arg(mpd_status_get_error(status)));


	if (mpd_status_get_state(status) == MPD_STATE_PLAY ||
	    mpd_status_get_state(status) == MPD_STATE_PAUSE) {
		new QListWidgetItem(QString("song: %1").
				arg(mpd_status_get_song_pos(status)));
	}

	mpd_status_free(status);
// Status

	mpd_response_next(conn);

// Song
	song = mpd_recv_song(conn);
	if (song == NULL)
	{
		new QListWidgetItem("song: NULL", listWdg);
		handle_error(conn);
		return ;
	}

	new QListWidgetItem(QString("Song URI: %1").
			arg(mpd_song_get_uri(song)), listWdg);

	unsigned int i = 0;
	QString value;

	while ((value = mpd_song_get_tag(song, MPD_TAG_TITLE, i++)) != NULL)
		new QListWidgetItem(QString("Title: %1")
				.arg(value), listWdg);

	mpd_song_free(song);
// Song

	mpd_connection_free(conn);

}


void MpdWidget::handle_error(struct mpd_connection *c)
{
	new QListWidgetItem(QString("ErrorCode: %1")
			.arg(mpd_connection_get_error_message(c)), listWdg);
	mpd_connection_free(c);
}

void MpdWidget::psExit()
{
	emit closeWdg();
}
