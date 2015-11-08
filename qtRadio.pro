QT       += dbus network
HEADERS   = GetIP.h MainMenu.h MpdWidget.h ScrollText.h
SOURCES   = main.cpp GetIP.cpp MainMenu.cpp MpdWidget.cpp ScrollText.cpp 
RESOURCES = 
INCLUDEPATH += /usr/include/libnm /usr/include/mpd
LIBS += -L/usr/lib -lmpdclient
CONFIG += release		#debug_and_release 
