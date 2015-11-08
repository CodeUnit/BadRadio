#include <QApplication>
#include <QtGui>

#include "MainMenu.h"

int main(int argc, char **argv)
{

	QApplication app(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	MainMenu main;
	main.setFixedSize(320, 240);
	main.setWindowFlags(Qt::CustomizeWindowHint);
	main.show();

    return app.exec();

}
