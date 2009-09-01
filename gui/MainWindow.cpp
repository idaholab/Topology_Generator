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

MainWindow::MainWindow(const std::string &simulationName)
{

  this->dw = NULL;
  this->gen = new Generator(simulationName);

  //
  // Menu
  //
  QMenu *menuFichier = menuBar()->addMenu("&File");
  QAction *menuOpen = menuFichier->addAction("Open");
  menuOpen->setDisabled(true);
  QAction *menuNew = menuFichier->addAction("New");
  menuNew->setDisabled(true);
  QAction *menuSave = menuFichier->addAction("Save");
  menuSave->setDisabled(true);
  QAction *menuSaveAs = menuFichier->addAction("Save As");
  menuSaveAs->setDisabled(true);
  QAction *menuSavePix = menuFichier->addAction("Save Picture");
  menuSavePix->setDisabled(true);

  QAction *actionQuitter = menuFichier->addAction("Quit");
  connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdition = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdition->addAction("Configuration");
  actionConfig->setDisabled(true);
  connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 

  QMenu *menuAffichage = menuBar()->addMenu("&Generate");
  QAction *actionCpp = menuAffichage->addAction("C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  QAction *menuPython = menuAffichage->addAction("Python");
  menuPython->setDisabled(true);

  QMenu *menuHelp = menuBar()->addMenu("&Help");
  QAction *menuOnlineHelp = menuHelp->addAction("Online Help");
  menuOnlineHelp->setDisabled(true);
  connect(menuOnlineHelp, SIGNAL(triggered()), this, SLOT(Help()));
  QAction *menuAbout = menuHelp->addAction("About");
  connect(menuAbout, SIGNAL(triggered()), this, SLOT(About())); 

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
  QIcon appsLinkIcon("");
  QString appsLinkString("Application");  
  QAction *appsLinkAction = toolBarFichier->addAction(appsLinkIcon, appsLinkString);
  connect(appsLinkAction, SIGNAL(triggered()), this, SLOT(CreateApps()));
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
  this->dw->setMainWindow(this);
}

MainWindow::~MainWindow()
{
  delete gen;
}

void MainWindow::CreatePc()
{
  this->gen->AddNode("Pc");
  dw->CreateObject("Pc", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
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
    number = text.toUInt();
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  if(number <= (size_t) 0 )
  {
    QMessageBox::about(this, "Error", "The pc number can't be negative ...");
    return;
  }

  this->gen->AddNode("Pc",number);
  dw->CreateObject("Pc-group", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
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
      if( text.toStdString() == this->listIface.at(i))
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

  this->gen->AddNode("Pc");
  this->gen->AddLink("Emu", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName(), text.toStdString());
  dw->CreateObject("Emu",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
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
      if( text.toStdString() == this->listIface.at(i))
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

  this->gen->AddNode("Tap");
  this->gen->AddLink("Tap", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName(), text.toStdString());
  dw->CreateObject("Tap",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CleanIface()
{
  /* remove from list the unused iface. */
  bool used = false;
  for(size_t i = 0; i < (size_t) this->listIface.size(); i++)
  {
    used = false;
    for(size_t j = 0; j < this->gen->listLink.size(); j++)
    {
      if( (this->gen->listLink.at(j)->getLinkName()).find("tap_") == 0)
      {
        if( this->listIface.at(i) == static_cast<Tap*>(this->gen->listLink.at(j))->getIfaceName())
        {
          used = true;
          break;
        }
      }
      if( (this->gen->listLink.at(j)->getLinkName()).find("emu_") == 0 ) 
      {
        if( this->listIface.at(i) == static_cast<Emu*>(this->gen->listLink.at(j))->getIfaceName())
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
  this->gen->AddNode("Ap");
  this->gen->AddLink("Ap", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
  dw->CreateObject("Ap", this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName() );
}

void MainWindow::CreateStation()
{
  this->gen->AddNode("Station");
  dw->CreateObject("Station", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
}

void MainWindow::CreateHub()
{
  this->gen->AddLink("Hub");
  dw->CreateObject("Hub", this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateSwitch()
{
  this->gen->AddNode("Bridge");
  this->gen->AddLink("Bridge", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
  dw->CreateObject("Switch",this->gen->listLink.at(this->gen->listLink.size() - 1)->getLinkName());
}

void MainWindow::CreateRouter()
{
  this->gen->AddNode("Router");
  dw->CreateObject("Router", this->gen->listNode.at(this->gen->listNode.size() - 1)->getNodeName());
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
  if(this->dw->traceLink)
  {
    this->dw->traceLink = false;
    this->dw->ResetSelected();
    return;
  }
  this->dw->traceLink = true;
  this->dw->linkType = "HardLink";
}

void MainWindow::ValidLink()
{
  /* function called when the two equipement are selected. */
  /* get the selected equipement. */
  this->dw->traceLink = false;

  std::vector<std::string> equi = this->dw->getLastSelected();
  size_t indic = 0;

  if(equi.at(0) == "" || equi.at(1) == "" || equi.at(0) == "deleted" || equi.at(1) == "deleted")
  {
    QMessageBox::about(this, "Error", "You don't have selected two equipement.");
    for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
    {
      if( (equi.at(0) == this->dw->drawLines.at(i).begin && equi.at(1) == this->dw->drawLines.at(i).end) ||
          (equi.at(1) == this->dw->drawLines.at(i).begin && equi.at(0) == this->dw->drawLines.at(i).end) )
      {
        this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
      }
    }
    this->dw->ResetSelected();
    return;
  }

  if(equi.at(0) == equi.at(1))
  {
    QMessageBox::about(this, "Error", "You can't connect object to itself.");
    for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
    {
      if( (equi.at(0) == this->dw->drawLines.at(i).begin && equi.at(1) == this->dw->drawLines.at(i).end) ||
          (equi.at(1) == this->dw->drawLines.at(i).begin && equi.at(0) == this->dw->drawLines.at(i).end) )
      {
        this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
      }
    }
    this->dw->ResetSelected();
    return;
  }

  //
  // LINK to LINK
  //

  if( (equi.at(0).find("wifi_") == 0 || equi.at(0).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
        (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 )) && 
      (equi.at(1).find("wifi_") == 0 || equi.at(1).find("hub_") == 0 || (equi.at(1)).find("bridge_") == 0 || 
       (equi.at(1)).find("emu_") == 0 || (equi.at(1).find("tap_") == 0)) )
  {
    QMessageBox::about(this, "Error", "This link can't be etablished. Please use a Pc or a Router.");
    for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
    {
      if( (equi.at(0) == this->dw->drawLines.at(i).begin && equi.at(1) == this->dw->drawLines.at(i).end) ||
          (equi.at(1) == this->dw->drawLines.at(i).begin && equi.at(0) == this->dw->drawLines.at(i).end) )
      {
        this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
      }
    }
    this->dw->ResetSelected();
    return;
  }
  //
  // OTHERS
  //
  else if( (equi.at(0)).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
      (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->gen->listLink.size(); i++)
    { 
      if( this->gen->listLink.at(i)->getLinkName() == equi.at(0))
      {
        indic = i;
      }
    }
    this->ConnectNode(indic, equi.at(1));
  }
  else if ((equi.at(1)).find("hub_") == 0 || (equi.at(1)).find("bridge_") == 0 || 
      (equi.at(1)).find("emu_") == 0 || (equi.at(1).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->gen->listLink.size(); i++)
    { 
      if( this->gen->listLink.at(i)->getLinkName() == equi.at(1))
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
    for(size_t i = 0; i < (size_t) this->gen->listLink.size(); i++)
    {
      if(equi.at(0) == this->gen->listLink.at(i)->getLinkName())
      {
        number = i;
        break;
      }
      if(equi.at(1) == this->gen->listLink.at(i)->getLinkName())
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
      if(equi.at(2) == "HardLink")
      {
        this->gen->AddLink("Hub");
        this->ConnectNode((this->gen->listLink.size() - 1), equi.at(0));
        this->ConnectNode((this->gen->listLink.size() - 1), equi.at(1));
      }
      else if(equi.at(2) == "P2pLink")
      {
        this->gen->AddLink("PointToPoint");
        this->ConnectNode((this->gen->listLink.size() - 1), equi.at(0));
        this->ConnectNode((this->gen->listLink.size() - 1), equi.at(1));
      }
      else
      {
        QMessageBox::about(this, "Error", "An error occured.");
        /* delete the two equi .... */
        for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
        {
          if(equi.at(0) == this->dw->drawLines.at(i).begin || equi.at(1) == this->dw->drawLines.at(i).begin )
          {
            this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
          }
        }
      }
    } 
  }

  /* Draw the connection. */
  this->dw->DrawLine();
  this->dw->ResetSelected();
}

void MainWindow::CreateStationLink()
{
  if(this->dw->traceLink)
  {
    this->dw->traceLink = false;
    this->dw->ResetSelected();
    return;
  }
  this->dw->traceLink = true;
  this->dw->linkType = "WifiLink";
}

void MainWindow::CreateP2pLink()
{
  if(this->dw->traceLink)
  {
    this->dw->traceLink = false;
    this->dw->ResetSelected();
    return;
  }
  this->dw->traceLink = true;
  this->dw->linkType = "P2pLink";
}

void MainWindow::ConfigurationMenu()
{
}

void MainWindow::deleteObject()
{
  this->dw->deleteSelected();
}

void MainWindow::About()
{
  QMessageBox::about(this, "About",
      tr("<p align=\"center\">"
        "<h2>The ns-3 topology generator"
        "</h2>"
        "</p><br />"
        "Copyright (c) 2009 University of Strasbourg<br /><br />"
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
    this->gen->listLink.at(linkNumber);
  }
  catch(const std::out_of_range &e)
  {
    QMessageBox::about(this, "Error", "This link doesn't exist.");
    for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
    {
      if( (nodeName == this->dw->drawLines.at(i).begin && this->gen->listLink.at(linkNumber)->getLinkName() == this->dw->drawLines.at(i).end) ||
          (this->gen->listLink.at(linkNumber)->getLinkName() == this->dw->drawLines.at(i).begin && nodeName == this->dw->drawLines.at(i).end) )
      {
        this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
      }
    }
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
    for(size_t i = 0; i < (size_t) this->gen->listNode.size(); i++)
    {
      if(nodeName == this->gen->listNode.at(i)->getNodeName())
      {
        numberOfConnectedMachines += MainWindow::gen->listNode.at(i)->getMachinesNumber();
      }
    }
  }

  /* get the number of machines also connected. */
  std::vector<std::string> nodes = this->gen->listLink.at(linkNumber)->getNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->gen->listNode.size(); j++)
    {
      if(nodes.at(i) == this->gen->listNode.at(j)->getNodeName())
      {
        numberOfConnectedMachines += this->gen->listNode.at(j)->getMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    for(size_t i = 0; i < (size_t) this->dw->drawLines.size(); i++)
    {
      if( (nodeName == this->dw->drawLines.at(i).begin && this->gen->listLink.at(linkNumber)->getLinkName() == this->dw->drawLines.at(i).end) ||
          (this->gen->listLink.at(linkNumber)->getLinkName() == this->dw->drawLines.at(i).begin && nodeName == this->dw->drawLines.at(i).end) )
      {
        this->dw->drawLines.erase(this->dw->drawLines.begin() + i);
      }
    }
    return;
  }
  this->gen->listLink.at(linkNumber)->Install(nodeName);
}

void MainWindow::GenerateCpp()
{
  this->gen->GenerateCode();
}

void MainWindow::CreateApps()
{
  QDialog *dialog = new QDialog(this);
  dialog->setWindowTitle("Application");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  QLabel *title = new QLabel("<h2>Select the application you want to install :</h2>", dialog);
  layout->addWidget(title, 0, 3);

  /* PING */
  QLabel *appsPing;
  appsPing = new QLabel("Ping", dialog);
  layout->addWidget(appsPing, 2, 0);

  QCheckBox *box_appsPing = new QCheckBox(dialog);
  layout->addWidget(box_appsPing, 2, 1);

  /* UDP ECHO */
  QLabel *appsUdpEcho;
  appsUdpEcho = new QLabel("Udp Echo", dialog);
  layout->addWidget(appsUdpEcho, 3, 0);

  QCheckBox *box_appsUdpEcho = new QCheckBox(dialog);
  layout->addWidget(box_appsUdpEcho, 3, 1);

  /* TCP LARGE TRANSFER */
  QLabel *appsTcp;
  appsTcp = new QLabel("Tcp Large Transfer", dialog);
  layout->addWidget(appsTcp, 4, 0);

  QCheckBox *box_appsTcp = new QCheckBox(dialog);
  layout->addWidget(box_appsTcp, 4, 1);

  layout->addWidget(buttonBox, 15, 3);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    if(box_appsPing->isChecked())
    {
      this->dw->appsPing = true;
      this->dw->ShowGuiPing();
    }
    else if(box_appsUdpEcho->isChecked())
    {
      this->dw->appsUdpEcho = true;
      this->dw->ShowGuiUdpEcho();
    }
    else if(box_appsTcp->isChecked())
    {
      this->dw->appsTcp = true;
      this->dw->ShowGuiTcp();
    }
  }
}

void MainWindow::ValidApps()
{
  if(this->dw->appsPing)
  {
    this->gen->AddApplication("Ping", this->dw->appsServer, this->dw->appsClient, this->dw->startTime, this->dw->endTime);
    QMessageBox::about(this, "Ping", "Ping successfull installed.");
  }

  if(this->dw->appsUdpEcho)
  {
    this->gen->AddApplication("UdpEcho", this->dw->appsServer, this->dw->appsClient, this->dw->startTime, this->dw->endTime, this->dw->port);
    QMessageBox::about(this, "Udp Echo", "Udp echo successfull installed.");
  }

  if(this->dw->appsTcp)
  {
    this->gen->AddApplication("TcpLargeTransfer", this->dw->appsServer, this->dw->appsClient, this->dw->startTime, this->dw->endTime, this->dw->port);
    QMessageBox::about(this, "Tcp Large Transfer", "Tcp large transfer successfull installed.");
  }

  this->dw->appsPing = false;
  this->dw->appsUdpEcho = false;
  this->dw->appsTcp = false;
  this->dw->appsServer = "";
  this->dw->appsClient = "";
  this->dw->startTime = 0;
  this->dw->endTime = 0;
  this->dw->port = 0;
}

