#include "GetIP.h"



// Von nm-dbus-interface.h übernommen
//
#define NM_DBUS_SERVICE 	"org.freedesktop.NetworkManager"
#define NM_DBUS_PATH 		"/org/freedesktop/NetworkManager"
#define NM_DBUS_INTERFACE	"org.freedesktop.NetworkManager"
#define NM_DBUS_INTERFACE_DEVICE		NM_DBUS_INTERFACE ".Device"
#define NM_DBUS_INTERFACE_IP4_CONFIG	NM_DBUS_INTERFACE ".IP4Config"



GetIP::GetIP(QWidget *parent) : QWidget(parent)
{
	QStringList liste;
	QStringListModel *model = new QStringListModel();

	if (getListe(liste))
			model->setStringList(liste);

	listView = new QListView();
	listView->setModel(model);

	QPushButton *pbExit = new QPushButton("Exit");
	connect(pbExit, SIGNAL(clicked()), this, SLOT(ende()));

	QBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(listView);
	mainLayout->addStretch();
	mainLayout->addWidget(pbExit);

	setLayout(mainLayout);

	listView->installEventFilter(this);
	listView->viewport()->installEventFilter(this);
}

bool GetIP::eventFilter(QObject* o, QEvent* e)
{

	bool ret = false;

	if( o == listView &&
		( e->type() == QEvent::KeyPress
		|| e->type() == QEvent::KeyRelease ) )
	{
			ret = true;
	}
	else if( o == listView->viewport() &&
		( e->type() == QEvent::MouseButtonPress
		|| e->type() == QEvent::MouseButtonRelease
		|| e->type() == QEvent::MouseMove
		|| e->type() == QEvent::MouseButtonDblClick ) )
	{
		ret = true;
	}

	return ret;
}



void GetIP::getConnections(QDBusReply<QList<QDBusObjectPath> >& liste)
{

    // Create a D-Bus proxy; NM_DBUS_* defined in NetworkManager.h
    QDBusInterface interface(
        NM_DBUS_SERVICE,
		NM_DBUS_PATH,
		NM_DBUS_INTERFACE ,
        QDBusConnection::systemBus());

    // Get connection list and find the connection with 'connectionUuid'
    liste = interface.call("GetDevices");

}


bool GetIP::getListe(QStringList &liste)
{

	bool ret = false;

	QDBusReply<QList<QDBusObjectPath> > result;
	getConnections(result);


	foreach (const QDBusObjectPath& connection, result.value())
	{
	    QDBusInterface device(NM_DBUS_SERVICE, connection.path(), NM_DBUS_INTERFACE_DEVICE, QDBusConnection::systemBus());
		QVariant ipv4config = device.property("Ip4Config");
		if ( ipv4config.isValid() )
		{
		    QDBusObjectPath path = qvariant_cast<QDBusObjectPath>(ipv4config);

		    QDBusMessage message = QDBusMessage::createMethodCall(NM_DBUS_SERVICE, path.path(),       QLatin1String("org.freedesktop.DBus.Properties"), QLatin1String("Get"));
		    QList<QVariant> arguments;
		    arguments << NM_DBUS_INTERFACE_IP4_CONFIG << "Addresses"/*"Gateway"*/;
		    message.setArguments(arguments);
		    QDBusConnection connection = QDBusConnection::systemBus();
		    QDBusMessage replay = connection.call(message);


		    if (replay.type() == QDBusMessage::ReplyMessage)
		    {
			    QList<QVariant> outArgs = replay.arguments();
			    QVariant first = outArgs.at(0);
			    QDBusVariant dbvFirst = first.value<QDBusVariant>();
			    QVariant vFirst = dbvFirst.variant();
			    const QDBusArgument dbusArgs = vFirst.value<QDBusArgument>();



				QList<QList<uint> > addresses;
				QList<uint> addr1;

				dbusArgs.beginArray();
				while ( !dbusArgs.atEnd() )
				{
					dbusArgs >> addr1 ;
					addresses << addr1 ;
				}
				dbusArgs.endArray();

				for (int j = 0; j < addresses.size(); j++)
				{
					addr1 = addresses.at(j);
					liste << QHostAddress(ntohl(addr1.at(0))).toString();
					ret = true;
		    	}

		    }

		}

	}


	return ret;
}


void GetIP::ende()
{
	emit closeWdg();
}


//#include "nmListCon.moc"


