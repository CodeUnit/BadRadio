QT       += network widgets
#QT 	 += dbus

HEADERS   = MainMenu.h MpdWidget.h ScrollText.h LED.h	# GetIP.h
SOURCES   = main.cpp MainMenu.cpp MpdWidget.cpp ScrollText.cpp LED.cpp	# GetIP.cpp
RESOURCES = 
INCLUDEPATH += /usr/include/libnm /usr/include/mpd
LIBS += -L/usr/lib -lmpdclient
CONFIG += release		#debug_and_release 
