/*
 * MainMenu.cpp
 *
 *  Created on: 31.10.2015
 *      Author: gunit
 */

#include "MainMenu.h"


MainMenu::MainMenu(QWidget *parent) : QDialog(parent) //, dialogIP(NULL)
{
// Buttons
	pbIpSettings = new QPushButton("Network");

// Connections
	connect(pbIpSettings, SIGNAL(clicked()), this, SLOT(psIpSettings()));

	mpdWdg = new MpdWidget(this);

	mainLayout = new QVBoxLayout;

	mainLayout->addWidget(mpdWdg);
	mainLayout->addStretch();
//	mainLayout->addWidget(pbIpSettings);

	setLayout(mainLayout);
}

MainMenu::~MainMenu()
{
	delete pbIpSettings;
}

void MainMenu::rmWdg()
{
}

void MainMenu::psIpSettings()
{
//	dialogIP = new GetIP();
//	connect(dialogIP, SIGNAL(closeWdg()), this, SLOT(rmIpSettings()));
//	mainLayout->addWidget(dialogIP);
//
//	mpdWdg->setVisible(false);
//	pbIpSettings->setVisible(false);
}

void MainMenu::rmIpSettings()
{
////	mainLayout->removeWidget(dialogIP);
//	delete dialogIP;
//	pbIpSettings->setVisible(true);
//	mpdWdg->setVisible(true);
}

