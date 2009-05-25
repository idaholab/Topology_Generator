/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
/**
* \file MainWindow.cpp
* \brief The main windows file.
* \author Pierre Weiss
* \date 2009
*/

#include <iostream>

#include "MainWindow.h"
#include "DragWidget.h"
#include "DragObject.h"

QAction* MainWindow::delAction = NULL;
Generator* MainWindow::gen = NULL;

MainWindow::MainWindow(const std::string &simulationName)
{
  
  this->dw = NULL;
  this->config = NULL;
  MainWindow::gen = new Generator(simulationName);
  
  //
  // Menu
  //
  QMenu *menuFichier = menuBar()->addMenu("&File");
  menuFichier->addAction("Open");
  menuFichier->addAction("New");
  menuFichier->addAction("Save");
  menuFichier->addAction("Save As");
  menuFichier->addAction("Save Picture");
     
  QAction *actionQuitter = menuFichier->addAction("Quit");
  connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdition = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdition->addAction("Configuration");
  connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 
     
  QMenu *menuAffichage = menuBar()->addMenu("&Generate");
  menuAffichage->addAction("C++");
  menuAffichage->addAction("Python");
     
  QAction *menuAbout = menuBar()->addAction("About");
  connect(menuAbout, SIGNAL(triggered()), this, SLOT(About())); 
     
  menuAbout = menuAbout;
     
  //
  // toolbar for add equipements.
  //
  QToolBar *toolBarFichier = addToolBar("");
  //Delete button
  QIcon delIcon(":/Ico/Del.png");
  QString delString("Delete");
  MainWindow::delAction = toolBarFichier->addAction(delIcon, delString);
  MainWindow::delAction->setDisabled (true);  
  connect(MainWindow::delAction, SIGNAL(triggered()), this, SLOT(deleteObject()));
  //PC
  QIcon pcIcon(":/Ico/Pc.png");
  QString pcString("Terminal");  
  QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
  connect(pcAction, SIGNAL(triggered()), this, SLOT(CreatePc()));
  //PC-Emu
  QIcon emuIcon(":/Ico/Emu.png");
  QString emuString("PC with emu");  
  QAction *emuAction = toolBarFichier->addAction(emuIcon, emuString);
  connect(emuAction, SIGNAL(triggered()), this, SLOT(CreateEmu()));
  //PC-Tap
  QIcon tapIcon(":/Ico/Tap.png");
  QString tapString("PC with tap");  
  QAction *tapAction = toolBarFichier->addAction(tapIcon, tapString);
  connect(tapAction, SIGNAL(triggered()), this, SLOT(CreateTap()));
  //AP-Wifi
  QIcon apIcon(":/Ico/Ap-Wifi.png");
  QString apString("AP Wifi");  
  QAction *apAction = toolBarFichier->addAction(apIcon, apString);
  connect(apAction, SIGNAL(triggered()), this, SLOT(CreateAp()));
  //StationWifi
  QIcon stasIcon(":/Ico/StationWifi.png");
  QString stasString("Station Wifi");  
  QAction *stasAction = toolBarFichier->addAction(stasIcon, stasString);
  connect(stasAction, SIGNAL(triggered()), this, SLOT(CreateStation()));
  //Hub
  QIcon hubIcon(":/Ico/Hub.png");
  QString hubString("Hub");  
  QAction *hubAction = toolBarFichier->addAction(hubIcon, hubString);
  connect(hubAction, SIGNAL(triggered()), this, SLOT(CreateHub()));
  //Switch
  QIcon switchIcon(":/Ico/Switch.png");
  QString switchString("Switch");  
  QAction *switchAction = toolBarFichier->addAction(switchIcon, switchString);
  connect(switchAction, SIGNAL(triggered()), this, SLOT(CreateSwitch()));
  //Router
  QIcon routerIcon(":/Ico/Router.png");
  QString routerString("Router");  
  QAction *routerAction = toolBarFichier->addAction(routerIcon, routerString);
  connect(routerAction, SIGNAL(triggered()), this, SLOT(CreateRouter()));
     
  //
  // Creation of Drag N Drop Area.
  //
  QHBoxLayout *dragLayout = new QHBoxLayout;
  this->dw = new DragWidget();
  dragLayout->addWidget(dw);
     
  QWidget *zoneCentral = new QWidget; 
  zoneCentral->setLayout(dragLayout);
     
  this->setCentralWidget(zoneCentral);
   
  //
  // 
  //
  
}

MainWindow::~MainWindow()
{
  delete config;
  delete MainWindow::gen;
}

void MainWindow::CreatePc()
{
	MainWindow::gen->AddEquipement("Pc");
	dw->CreateObject("Pc", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateEmu()
{
  bool ok;
  QString text = QInputDialog::getText(this, "Emu",
                                        tr("Enter the real host interface to use:"), QLineEdit::Normal,
                                        "eth0", &ok);
  if (ok && !text.isEmpty())
  {
    //~ std::cout << "text received :" <<  text.toStdString () << std::endl;
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  MainWindow::gen->AddEquipement("Pc");
  MainWindow::gen->AddLink("Emu", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName(), text.toStdString());
	dw->CreateObject("Emu",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateTap()
{
  bool ok;
  QString text = QInputDialog::getText(this, "Tap",
                                        tr("Enter the new interface to use :"), QLineEdit::Normal,
                                        "tap0", &ok);
  if (ok && !text.isEmpty())
  {
    //~ std::cout << "text received :" <<  text.toStdString () << std::endl;
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }
  
  MainWindow::gen->AddEquipement("Tap");
  MainWindow::gen->AddLink("Tap", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName(), text.toStdString());
	dw->CreateObject("Tap",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateAp()
{
	MainWindow::gen->AddEquipement("Ap");
	dw->CreateObject("Ap", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateStation()
{
	MainWindow::gen->AddEquipement("Station");
	dw->CreateObject("Station", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateHub()
{
	MainWindow::gen->AddLink("Hub");
	dw->CreateObject("Hub", this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateSwitch()
{
	MainWindow::gen->AddEquipement("Bridge");
  MainWindow::gen->AddLink("Bridge", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
	dw->CreateObject("Switch",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateRouter()
{
	MainWindow::gen->AddEquipement("Router");
	dw->CreateObject("Router", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::ConfigurationMenu()
{
    config = new Configuration();
}

void MainWindow::deleteObject()
{
  this->dw->deleteSelected();
}

void MainWindow::About()
{
     QMessageBox::about(this, "About",
                  tr("<p align=\"center\">"
                     "<h2>Simulation Generator</h2>"
                     "<h3>for Network Simulator 3</h3>"
                     "<br />"
                     "Copyright (c) 2009 <br />"
                     "Pierre Weiss<br />"
                     "3weissp@gmail.com"
                     "</p>"
                                ));
}




