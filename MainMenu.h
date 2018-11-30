/*
 * MainMenu.h
 *
 *  Created on: 31.10.2015
 *      Author: gunit
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <QDialog>
#include <QtWidgets>

#include "GetIP.h"
#include "MpdWidget.h"

class MainMenu: public QDialog
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = 0);
	virtual ~MainMenu();


private:
	void rmWdg();
	QPushButton *pbIpSettings;
	QBoxLayout *mainLayout;
	GetIP *dialogIP;
	MpdWidget *mpdWdg;


private slots:
	void psIpSettings();
	void rmIpSettings();

};

#endif /* MAINMENU_H_ */
