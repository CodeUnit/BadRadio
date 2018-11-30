/*
 * nmListCon.h
 *
 *  Created on: 27.10.2015
 *      Author: gunit
 */
#ifndef GETIP_H_
#define GETIP_H_

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMetaType>
#include <QtDBus/QDBusReply>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtNetwork/QHostAddress>
#include <QListView>
#include <QDialog>
#include <QtWidgets>

#include "arpa/inet.h"


class GetIP : public QWidget
{
	Q_OBJECT

public:
	GetIP(QWidget *parent = 0);

private:
	void getConnections(QDBusReply<QList<QDBusObjectPath> >& liste);
	bool getListe(QStringList &liste);

	QListView *listView;

protected:
	bool eventFilter(QObject* q, QEvent* e);

private slots:
	void ende();

signals:
	void closeWdg();
};





#endif /* GETIP_H_ */
