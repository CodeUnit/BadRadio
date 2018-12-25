/*
 * MpdWidget.cpp
 *
 *  Created on: 07.11.2015
 *      Author: gunit
 */

#include <QTextStream>

#include "MpdWidget.h"

MpdWidget::MpdWidget(QWidget *parent) : QWidget(parent)
, aktPlay(false), aktStop(false), aktNext(false), aktPrev(false), toggleBool(false)
{
	QSize buttonSize(64, 64);

	mpdWdg = new QWidget;
    playlistWdg = new QWidget;

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(mpdWdg);
    stackedWidget->addWidget(playlistWdg);


	timerMpd = new QTimer();
	timerMpd->setInterval(500);
	connect(timerMpd, SIGNAL(timeout()), this, SLOT(sltMpdHB()));
	timerMpd->start();

	mpdSocket = new QTcpSocket;
	connect(mpdSocket, SIGNAL(connected()),this, SLOT(sltConnected()));
	connect(mpdSocket, SIGNAL(disconnected()),this, SLOT(sltDisconnected()));
	connect(mpdSocket, SIGNAL(readyRead()),this, SLOT(sltReadyRead()));
	connect(mpdSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(sltBytesWritten(qint64)));


// MPD Design
	led = new LED();
	led->setLedSize(10);
	connect(led, SIGNAL(clicked()), this, SLOT(sltMpdConnect()));

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
	buttonLeiser = new QPushButton("Leiser");
	connect(buttonLeiser, SIGNAL(clicked()), this, SLOT(slotLeiser()));
	buttonLeiser->setFixedSize(buttonSize);
	buttonLauter = new QPushButton("Lauter");
	connect(buttonLauter, SIGNAL(clicked()), this, SLOT(slotLauter()));
	buttonLauter->setFixedSize(buttonSize);
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
	mpdWdgLayout->addWidget(buttonLeiser, 4, 1);
	mpdWdgLayout->addWidget(buttonLauter, 4, 2);
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


	sltMpdConnect();

}

MpdWidget::~MpdWidget()
{

}

void MpdWidget::sltMpdConnect()
{
	if (mpdSocket->state() != QAbstractSocket::UnconnectedState)
		return;

	mpdSocket->connectToHost(QHostAddress("127.0.0.1"), 6600);
}

void MpdWidget::sltConnected()
{
	qDebug() << __FUNCTION__;
	led->setState(true);
}
void MpdWidget::sltDisconnected()
{
	qDebug() << "Disconnected!!!";
	led->setState(false);
}

void MpdWidget::sltReadyRead()
{
	qDebug() << "reading...";
	QByteArray data = mpdSocket->readAll();

	QStringList liste = QString::fromStdString(data.data()).split('\n');

	qDebug() << liste;

	for (int i = 0; i < liste.size(); i++)
	{
		if (liste.at(i).contains("Title: "))
		{
			QString tmpStr = QString(liste.at(i)).remove("Title: ");
			if (labelTitle->text().compare(tmpStr) != 0)
				labelTitle->setText(tmpStr);
		}

		if (liste.at(i).contains("Name: "))
		{
			QString tmpStr = QString(liste.at(i)).remove("Name: ");
			if (labelSender->text().compare(tmpStr) != 0)
				labelSender->setText(tmpStr);
		}

		if (liste.at(i).contains("volume: "))
		{
			QString tmpStr = QString(liste.at(i)).remove("volume: ");
			if (labelVol->text().compare(tmpStr) != 0)
				labelVol->setText(tmpStr);
		}


	}

}

void MpdWidget::sltBytesWritten(qint64 size)
{
	qDebug() << "Sended Size: " << size;
}

void MpdWidget::sltMpdHB()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	if (toggleBool)
		mpdSocket->write("currentsong\n");
	else
		mpdSocket->write("status\n");

	toggleBool = !toggleBool;
}



void MpdWidget::slotPlay()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	mpdSocket->write("play\n");
	mpdSocket->write("playlist\n");

}

void MpdWidget::slotStop()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	mpdSocket->write("stop\n");

}

void MpdWidget::slotNext()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	mpdSocket->write("next\n");

}

void MpdWidget::slotPrev()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	mpdSocket->write("previous\n");

}

void MpdWidget::slotLeiser()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	int vol = labelVol->text().toInt() - 10;
	if (vol < 0)
		vol = 0;
	mpdSocket->write(QString("setvol %1\n").arg(vol).toLatin1());
}

void MpdWidget::slotLauter()
{
	if (mpdSocket->state() != QAbstractSocket::ConnectedState)
		return;

	int vol = labelVol->text().toInt() + 10;
	if (vol > 100)
		vol = 100;
	mpdSocket->write(QString("setvol %1\n").arg(vol).toLatin1());

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
	QApplication::quit();
	stackedWidget->setCurrentIndex(1);
}


void MpdWidget::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);

}



