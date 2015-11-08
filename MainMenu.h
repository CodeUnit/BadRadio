/*
 * MainMenu.h
 *
 *  Created on: 31.10.2015
 *      Author: gunit
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <QDialog>
#include <QtGui>

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
	QPushButton *pbIpSettings, *pbMpdWidget;
	QBoxLayout *mainLayout;
	GetIP *dialogIP;
	MpdWidget *dialogMpdWdg;


private slots:
	void psIpSettings();
	void psMpdWidget();
	void rmIpSettings();
	void rmMpdWidget();

};

#endif /* MAINMENU_H_ */
