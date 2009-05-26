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
#include <stdexcept>

#include "MainWindow.h"
#include "DragWidget.h"
#include "DragObject.h"
#include "Tap.h"
#include "Emu.h"

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
  QAction *actionCpp = menuAffichage->addAction("C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  menuAffichage->addAction("Python");
     
  QAction *menuAbout = menuBar()->addAction("About");
  connect(menuAbout, SIGNAL(triggered()), this, SLOT(About())); 
  
  QAction *menuHelp = menuBar()->addAction("Help");
  connect(menuAbout, SIGNAL(triggered()), this, SLOT(Help()));
     
  menuAbout = menuAbout;
  menuHelp = menuHelp;
     
  //
  // toolbar for add equipements.
  //
  QToolBar *toolBarFichier = addToolBar("");
  //PC
  QIcon pcIcon(":/Ico/Pc.png");
  QString pcString("Terminal");  
  QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
  connect(pcAction, SIGNAL(triggered()), this, SLOT(CreatePc()));
  //Pc-group
  QIcon pcgIcon(":/Ico/Pc-group.png");
  QString pcgString("Terminal Group");  
  QAction *pcgAction = toolBarFichier->addAction(pcgIcon, pcgString);
  connect(pcgAction, SIGNAL(triggered()), this, SLOT(CreatePcGroup()));
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
  //separator
  toolBarFichier->addSeparator();
  // Hard Link
  QIcon linkIcon(":/Ico/HardLink.png");
  QString linkString("Hard Link");  
  QAction *linkAction = toolBarFichier->addAction(linkIcon, linkString);
  connect(linkAction, SIGNAL(triggered()), this, SLOT(CreateHardLink()));
  // Station link
  QIcon stasLinkIcon(":/Ico/Link.png");
  QString stasLinkString("Station Link");  
  QAction *stasLinkAction = toolBarFichier->addAction(stasLinkIcon, stasLinkString);
  connect(stasLinkAction, SIGNAL(triggered()), this, SLOT(CreateStationLink()));
  //P2P link
  QIcon p2pLinkIcon(":/Ico/P2pLink.png");
  QString p2pLinkString("P2P Link");  
  QAction *p2pLinkAction = toolBarFichier->addAction(p2pLinkIcon, p2pLinkString);
  connect(p2pLinkAction, SIGNAL(triggered()), this, SLOT(CreateP2pLink()));
  //separator
  toolBarFichier->addSeparator();
  //Delete button
  QIcon delIcon(":/Ico/Del.png");
  QString delString("Delete");
  MainWindow::delAction = toolBarFichier->addAction(delIcon, delString);
  MainWindow::delAction->setDisabled (true);  
  connect(MainWindow::delAction, SIGNAL(triggered()), this, SLOT(deleteObject()));
     
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
	dw->CreateObject("Pc", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreatePcGroup()
{
  bool ok;
  size_t number = 0;
  QString text = QInputDialog::getText(this, "Terminal Group",
                                        tr("Enter the number of machines to create :"), QLineEdit::Normal,
                                        "", &ok);
  if (ok && !text.isEmpty())
  {
    /* number ok ! */
    number = text.toInt();
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }
  
  MainWindow::gen->AddEquipement(number);
	dw->CreateObject("Pc-group", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateEmu()
{
  this->CleanIface();
  
  bool ok;
  QString text = QInputDialog::getText(this, "Emu",
                                        tr("Enter the real host interface to use:"), QLineEdit::Normal,
                                        "eth0", &ok);
  if (ok && !text.isEmpty())
  {
    /* test if the iface is already used. */
    for(size_t i = 0; i < (size_t) this->listIface.size(); i++)
    {
      if( (text.toStdString()).compare(this->listIface.at(i)) == 0)
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  MainWindow::gen->AddEquipement("Pc");
  MainWindow::gen->AddLink("Emu", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName(), text.toStdString());
	dw->CreateObject("Emu",MainWindow::gen->listLink.at(MainWindow::gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateTap()
{
  this->CleanIface();
  
  bool ok;
  QString text = QInputDialog::getText(this, "Tap",
                                        tr("Enter the new interface to use :"), QLineEdit::Normal,
                                        "tap0", &ok);
  if (ok && !text.isEmpty())
  {
    for(size_t i = 0; i < (size_t) this->listIface.size(); i++)
    {
      if( (text.toStdString()).compare(this->listIface.at(i)) == 0)
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }
  
  MainWindow::gen->AddEquipement("Tap");
  MainWindow::gen->AddLink("Tap", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName(), text.toStdString());
	dw->CreateObject("Tap",MainWindow::gen->listLink.at(MainWindow::gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CleanIface()
{
  /* remove from list the unused iface. */
  bool used = false;
  for(size_t i = 0; i < (size_t) this->listIface.size(); i++)
  {
    used = false;
    for(size_t j = 0; j < MainWindow::gen->listLink.size(); j++)
    {
      if( (MainWindow::gen->listLink.at(j)->getLinkName()).find("tap_") == 0)
      {
        if( (this->listIface.at(i)).compare(static_cast<Tap*>(MainWindow::gen->listLink.at(j))->getIfaceName()) == 0)
        {
          used = true;
          break;
        }
      }
      if( (MainWindow::gen->listLink.at(j)->getLinkName()).find("emu_") == 0 ) 
      {
        if( (this->listIface.at(i)).compare(static_cast<Emu*>(MainWindow::gen->listLink.at(j))->getIfaceName()) == 0)
        {
          used = true;
          break;
        }
      }
    }
    if(!used)
    {
      this->listIface.erase(this->listIface.begin() + i);
    }
  }
}

void MainWindow::CreateAp()
{
	MainWindow::gen->AddEquipement("Ap");
	MainWindow::gen->AddLink("Wifi", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName(), false);
	dw->CreateObject("Ap", MainWindow::gen->listLink.at(MainWindow::gen->listLink.size() - 1)->getLinkName() );
}

void MainWindow::CreateStation()
{
	MainWindow::gen->AddEquipement("Station");
	dw->CreateObject("Station", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateHub()
{
	MainWindow::gen->AddLink("Hub");
	dw->CreateObject("Hub", MainWindow::gen->listLink.at(MainWindow::gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateSwitch()
{
	MainWindow::gen->AddEquipement("Bridge");
  MainWindow::gen->AddLink("Bridge", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName());
	dw->CreateObject("Switch",MainWindow::gen->listLink.at(MainWindow::gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateRouter()
{
	MainWindow::gen->AddEquipement("Router");
	dw->CreateObject("Router", MainWindow::gen->listEquipement.at(MainWindow::gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateHardLink()
{
  /*
   * The differents link :
   *  - Pc to Pc (create a hide hub)
   *  - Pc to Hub
   *  - Pc to Bridge
   *  - Pc to Router (create a hide hub)
   *  - Pc to Ap
   *  - Ap to Router
   *  - Hub to Router
   *  - Switch to Router
   *  - Pc to emu
   *  - Pc to Tap
   */
  
  
  /* get the selected equipement. */
  std::vector<std::string> equi = this->dw->getLastSelected();
  size_t indic = 0;
  
  if(equi.at(0) == "" || equi.at(1) == "" || equi.at(0) == "deleted" || equi.at(1) == "deleted")
  {
    QMessageBox::about(this, "Error", "You don't have selected two equipement.");
    return;
  }
  
  if(equi.at(0) == equi.at(1))
  {
    QMessageBox::about(this, "Error", "You can't connect object to itself.");
    return;
  }
  
  std::cout << equi.at(0) << " - " << equi.at(1) << std::endl;
  
  if( (equi.at(0)).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
      (equi.at(0)).find("ap_") == 0  || (equi.at(0)).find("emu_") == 0 || 
      (equi.at(0).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) MainWindow::gen->listLink.size(); i++)
    { 
std::cout << "link name :" << (MainWindow::gen->listLink.at(i)->getLinkName()) << std::endl;
      if( (MainWindow::gen->listLink.at(i)->getLinkName()).compare(equi.at(0)) == 0)
      {
        indic = i;
      }
    }
    this->ConnectNode(indic, equi.at(1));
  }
  else if ((equi.at(1)).find("hub_") == 0 || (equi.at(1)).find("bridge_") == 0 || 
          (equi.at(1)).find("ap_") == 0  || (equi.at(1)).find("emu_") == 0 || 
          (equi.at(1).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) MainWindow::gen->listLink.size(); i++)
    { 
std::cout << "link name :" << (MainWindow::gen->listLink.at(i)->getLinkName()) << std::endl;
      if( (MainWindow::gen->listLink.at(i)->getLinkName()).compare(equi.at(1)) == 0)
      {
        indic = i;
      }
    }
    this->ConnectNode(indic, equi.at(0));
  }
  else
  {
    size_t number = -1;
    size_t number2 = -1;
    for(size_t i = 0; i < (size_t) MainWindow::gen->listLink.size(); i++)
    {
      if(equi.at(0).compare(MainWindow::gen->listLink.at(i)->getLinkName()) == 0)
      {
        number = i;
        break;
      }
      if(equi.at(1).compare(MainWindow::gen->listLink.at(i)->getLinkName()) == 0)
      {
        number2 = i;
        break;
      }
    }
    if(number != (size_t) -1 )
    {
      this->ConnectNode(number, equi.at(1));
    }
    else if(number2 != (size_t) -1)
    {
      this->ConnectNode(number2, equi.at(0));
    }
    else
    {
      /* you can't connect for example two terminals without an csma network so ... */
      MainWindow::gen->AddLink("Hub");
      this->ConnectNode((MainWindow::gen->listLink.size() - 1), equi.at(0));
      this->ConnectNode((MainWindow::gen->listLink.size() - 1), equi.at(1));
    }
  }
  
  /* Draw the connection. */
  this->dw->DrawLine(std::string("HardLink"));
  
  this->dw->ResetSelected();
}

void MainWindow::CreateStationLink()
{
}

void MainWindow::CreateP2pLink()
{
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
                     "<h2>Simulation Generator<br />"
                     "for ns-3</h2>"
                     "</p><br />"
                     "Copyright (c) 2009 University of Strasbourg<br />"
                     "This program is free software; you can redistribute it and/or<br />"
                     "modify it under the terms of the GNU General Public License<br />"
                     "as published by the Free Software Foundation; either version 2<br />"
                     "of the License, or (at your option) any later version.<br />"
                     "<br />"
                     "<strong>Authors:</strong><br />"
                     "Pierre Weiss &lt;3weissp@gmail.com&gt;<br />"
                     "Sebastien Vincent &lt;vincent@clarinet.u-strasbg.fr&gt;"
                                ));
}

void MainWindow::Help()
{

}

void MainWindow::ConnectNode(const size_t &linkNumber, const std::string &nodeName)
{
  /* test if the link exist. */
  try
  {
    MainWindow::gen->listLink.at(linkNumber);
  }
    catch(const std::out_of_range &e)
    {
      QMessageBox::about(this, "Error", "This link doesn't exist.");
      return;
    }
  
  size_t numberOfConnectedMachines = 0;
  /* get the number of machines to add */
  if(nodeName.find("Get") == 0)
  {
    numberOfConnectedMachines += 1;
  }
  else
  {
    for(size_t i = 0; i < (size_t) MainWindow::gen->listEquipement.size(); i++)
    {
      if(nodeName.compare(MainWindow::gen->listEquipement.at(i)->getNodeName()) == 0)
      {
        numberOfConnectedMachines += MainWindow::gen->listEquipement.at(i)->getMachinesNumber();
      }
    }
  }
  
  /* get the number of machines also connected. */
  std::vector<std::string> nodes = MainWindow::gen->listLink.at(linkNumber)->getNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) MainWindow::gen->listEquipement.size(); j++)
    {
      if(nodes.at(i).compare(MainWindow::gen->listEquipement.at(j)->getNodeName()) == 0)
      {
        numberOfConnectedMachines += MainWindow::gen->listEquipement.at(j)->getMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    return;
  }
  MainWindow::gen->listLink.at(linkNumber)->AddNodes(nodeName);
}

void MainWindow::GenerateCpp()
{
  MainWindow::gen->GenerateCode();
}


