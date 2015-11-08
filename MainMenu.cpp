/*
 * MainMenu.cpp
 *
 *  Created on: 31.10.2015
 *      Author: gunit
 */

#include <GetIP.h>
#include "MainMenu.h"


MainMenu::MainMenu(QWidget *parent) : QDialog(parent)
, dialogIP(NULL), dialogMpdWdg(NULL)
{
// Buttons
	pbIpSettings = new QPushButton("Network");
	pbMpdWidget = new QPushButton("MPD");

// Connections
	connect(pbIpSettings, SIGNAL(clicked()), this, SLOT(psIpSettings()));
	connect(pbMpdWidget, SIGNAL(clicked()), this, SLOT(psMpdWidget()));

	mainLayout = new QVBoxLayout;

	mainLayout->addStretch();
	mainLayout->addWidget(pbIpSettings);
	mainLayout->addWidget(pbMpdWidget);

	setLayout(mainLayout);
}

MainMenu::~MainMenu()
{
	delete pbIpSettings;
	delete pbMpdWidget;
}

void MainMenu::rmWdg()
{
	mainLayout->removeWidget(pbIpSettings);
	mainLayout->removeWidget(pbMpdWidget);

	pbIpSettings->setVisible(false);
	pbMpdWidget->setVisible(false);
}

void MainMenu::psIpSettings()
{
	dialogIP = new GetIP();
	connect(dialogIP, SIGNAL(closeWdg()), this, SLOT(rmIpSettings()));
//	mainLayout->removeWidget(pbIpSettings);
//	pbIpSettings->setVisible(false);
//	delete pbIpSettings;
	rmWdg();
	mainLayout->addWidget(dialogIP);

}

void MainMenu::psMpdWidget()
{
	dialogMpdWdg = new MpdWidget(this);
	connect(dialogMpdWdg, SIGNAL(closeWdg()), this, SLOT(rmMpdWidget()));
	rmWdg();

	mainLayout->addWidget(dialogMpdWdg);

}

void MainMenu::rmIpSettings()
{
	mainLayout->removeWidget(dialogIP);
	delete dialogIP;
	pbIpSettings->setVisible(true);
	pbMpdWidget->setVisible(true);
}

void MainMenu::rmMpdWidget()
{
	mainLayout->removeWidget(dialogMpdWdg);
	delete dialogMpdWdg;
	pbIpSettings->setVisible(true);
	pbMpdWidget->setVisible(true);
}
