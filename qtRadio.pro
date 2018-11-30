QT       += dbus network widgets
HEADERS   = GetIP.h MainMenu.h MpdWidget.h ScrollText.h LED.h
SOURCES   = main.cpp GetIP.cpp MainMenu.cpp MpdWidget.cpp ScrollText.cpp LED.cpp
RESOURCES = 
INCLUDEPATH += /usr/include/libnm /usr/include/mpd
LIBS += -L/usr/lib -lmpdclient
CONFIG += release		#debug_and_release 
