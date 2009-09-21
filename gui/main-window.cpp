/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
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
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

/**
 * \file main-window.cpp
 * \brief The main windows file.
 * \author Pierre Weiss
 * \date 2009
 */

#include <iostream>
#include <stdexcept>

#include "main-window.h"
#include "drag-widget.h"
#include "drag-object.h"

#include "tap.h"
#include "emu.h"

MainWindow::MainWindow(const std::string &simulationName)
{

  this->m_dw = NULL;
  this->m_gen = new Generator(simulationName);

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

  QAction *actionQuit = menuFichier->addAction("Quit");
  connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdit = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdit->addAction("Configuration");
  actionConfig->setDisabled(true);
  connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 

  QMenu *menuView = menuBar()->addMenu("&Generate");
  QAction *actionCpp = menuView->addAction("C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  QAction *menuPython = menuView->addAction("Python");
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
  // Wired Link
  QIcon linkIcon(":/Ico/WiredLink.png");
  QString linkString("Wired Link");  
  QAction *linkAction = toolBarFichier->addAction(linkIcon, linkString);
  connect(linkAction, SIGNAL(triggered()), this, SLOT(CreateWiredLink()));
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
  MainWindow::m_delAction = toolBarFichier->addAction(delIcon, delString);
  MainWindow::m_delAction->setDisabled (true);  
  connect(MainWindow::m_delAction, SIGNAL(triggered()), this, SLOT(DeleteObject()));

  //
  // Creation of Drag N Drop Area.
  //
  QHBoxLayout *dragLayout = new QHBoxLayout;
  this->m_dw = new DragWidget();

  dragLayout->addWidget(m_dw);

  QWidget *zoneCentral = new QWidget; 
  zoneCentral->setLayout(dragLayout);

  this->setCentralWidget(zoneCentral);

  //
  // 
  //
  this->m_dw->SetMainWindow(this);
}

MainWindow::~MainWindow()
{
  delete m_gen;
}

void MainWindow::CreatePc()
{
  this->m_gen->AddNode("Pc");
  m_dw->CreateObject("Pc", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
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

  this->m_gen->AddNode("Pc",number);
  m_dw->CreateObject("Pc-group", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
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
    for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->m_gen->AddNode("Pc");
  this->m_gen->AddLink("Emu", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  m_dw->CreateObject("Emu",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
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
    for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->m_gen->AddNode("Tap");
  this->m_gen->AddLink("Tap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  m_dw->CreateObject("Tap",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CleanIface()
{
  /* remove from list the unused iface. */
  bool used = false;
  for(size_t i = 0; i < (size_t) this->m_listIface.size(); i++)
  {
    used = false;
    for(size_t j = 0; j < this->m_gen->GetNLinks(); j++)
    {
      if( (this->m_gen->GetLink(j)->GetLinkName()).find("tap_") == 0)
      {
        if( this->m_listIface.at(i) == static_cast<Tap*>(this->m_gen->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
      if( (this->m_gen->GetLink(j)->GetLinkName()).find("emu_") == 0 ) 
      {
        if( this->m_listIface.at(i) == static_cast<Emu*>(this->m_gen->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
    }
    if(!used)
    {
      this->m_listIface.erase(this->m_listIface.begin() + i);
    }
  }
}

void MainWindow::CreateAp()
{  
  this->m_gen->AddNode("Ap");
  this->m_gen->AddLink("Ap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  m_dw->CreateObject("Ap", this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName() );
}

void MainWindow::CreateStation()
{
  this->m_gen->AddNode("Station");
  m_dw->CreateObject("Station", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateHub()
{
  this->m_gen->AddLink("Hub");
  m_dw->CreateObject("Hub", this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateSwitch()
{
  this->m_gen->AddNode("Bridge");
  this->m_gen->AddLink("Bridge", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  m_dw->CreateObject("Switch",this->m_gen->GetLink(this->m_gen->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateRouter()
{
  this->m_gen->AddNode("Router");
  m_dw->CreateObject("Router", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateWiredLink()
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
  if(this->m_dw->m_traceLink)
  {
    this->m_dw->m_traceLink = false;
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->m_traceLink = true;
  this->m_dw->m_linkType = "WiredLink";
}

void MainWindow::ValidLink()
{
  /* function called when the two equipement are selected. */
  /* get the selected equipement. */
  this->m_dw->m_traceLink = false;

  std::vector<std::string> equi = this->m_dw->GetLastSelected();
  size_t indic = 0;

  if(equi.at(0) == "" || equi.at(1) == "" || equi.at(0) == "deleted" || equi.at(1) == "deleted")
  {
    QMessageBox::about(this, "Error", "You don't have selected two equipement.");
    for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
    {
      if( (equi.at(0) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(1) == this->m_dw->m_drawLines.at(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(0) == this->m_dw->m_drawLines.at(i).GetSecond()) )
      {
        this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
      }
    }
    this->m_dw->ResetSelected();
    return;
  }

  if(equi.at(0) == equi.at(1))
  {
    QMessageBox::about(this, "Error", "You can't connect object to itself.");
    for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
    {
      if( (equi.at(0) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(1) == this->m_dw->m_drawLines.at(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(0) == this->m_dw->m_drawLines.at(i).GetSecond()) )
      {
        this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
      }
    }
    this->m_dw->ResetSelected();
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
    for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
    {
      if( (equi.at(0) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(1) == this->m_dw->m_drawLines.at(i).GetSecond()) ||
          (equi.at(1) == this->m_dw->m_drawLines.at(i).GetFirst() && equi.at(0) == this->m_dw->m_drawLines.at(i).GetSecond()) )
      {
        this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
      }
    }
    this->m_dw->ResetSelected();
    return;
  }
  //
  // OTHERS
  //
  else if( (equi.at(0)).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
      (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    { 
      if( this->m_gen->GetLink(i)->GetLinkName() == equi.at(0))
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
    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    { 
      if( this->m_gen->GetLink(i)->GetLinkName() == equi.at(1))
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

    for(size_t i = 0; i < (size_t) this->m_gen->GetNLinks(); i++)
    {
      if(equi.at(0) == this->m_gen->GetLink(i)->GetLinkName())
      {
        number = i;
        break;
      }
      if(equi.at(1) == this->m_gen->GetLink(i)->GetLinkName())
      {
        number2 = i;
        break;
      }
    }
    if(number != (size_t) - 1)
    {
      this->ConnectNode(number, equi.at(1));
    }
    else if(number2 != (size_t) - 1)
    {
      this->ConnectNode(number2, equi.at(0));
    }
    else
    {
      /* you can't connect for example two terminals without an csma network so ... */
      if(equi.at(2) == "WiredLink")
      {
        this->m_gen->AddLink("Hub");
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(1));
      }
      else if(equi.at(2) == "P2pLink")
      {
        this->m_gen->AddLink("PointToPoint");
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->m_gen->GetNLinks() - 1), equi.at(1));
      }
      else
      {
        QMessageBox::about(this, "Error", "An error occured.");
        /* delete the two equi .... */
        for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
        {
          if(equi.at(0) == this->m_dw->m_drawLines.at(i).GetFirst() || equi.at(1) == this->m_dw->m_drawLines.at(i).GetFirst() )
          {
            this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
          }
        }
      }
    } 
  }

  /* Draw the connection. */
  this->m_dw->DrawLine();
  this->m_dw->ResetSelected();
}

void MainWindow::CreateStationLink()
{
  if(this->m_dw->m_traceLink)
  {
    this->m_dw->m_traceLink = false;
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->m_traceLink = true;
  this->m_dw->m_linkType = "WifiLink";
}

void MainWindow::CreateP2pLink()
{
  if(this->m_dw->m_traceLink)
  {
    this->m_dw->m_traceLink = false;
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->m_traceLink = true;
  this->m_dw->m_linkType = "P2pLink";
}

void MainWindow::ConfigurationMenu()
{
}

void MainWindow::DeleteObject()
{
  this->m_dw->DeleteSelected();
}

void MainWindow::About()
{
  QMessageBox::about(this, "About",
      tr("<p align=\"center\">"
        "<h2>The ns-3 topology m_generator"
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
    this->m_gen->GetLink(linkNumber);
  }
  catch(const std::out_of_range &e)
  {
    QMessageBox::about(this, "Error", "This link doesn't exist.");
    for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
    {
      if( (nodeName == this->m_dw->m_drawLines.at(i).GetFirst() && this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->m_drawLines.at(i).GetSecond()) ||
          (this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->m_drawLines.at(i).GetFirst() && nodeName == this->m_dw->m_drawLines.at(i).GetSecond()) )
      {
        this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
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
    for(size_t i = 0; i < (size_t) this->m_gen->GetNNodes(); i++)
    {
      if(nodeName == this->m_gen->GetNode(i)->GetNodeName())
      {
        numberOfConnectedMachines += MainWindow::m_gen->GetNode(i)->GetMachinesNumber();
      }
    }
  }

  /* get the number of machines also connected. */
  std::vector<std::string> nodes = this->m_gen->GetLink(linkNumber)->GetInstalledNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->m_gen->GetNNodes(); j++)
    {
      if(nodes.at(i) == this->m_gen->GetNode(j)->GetNodeName())
      {
        numberOfConnectedMachines += this->m_gen->GetNode(j)->GetMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    for(size_t i = 0; i < (size_t) this->m_dw->m_drawLines.size(); i++)
    {
      if( (nodeName == this->m_dw->m_drawLines.at(i).GetFirst() && this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->m_drawLines.at(i).GetSecond()) ||
          (this->m_gen->GetLink(linkNumber)->GetLinkName() == this->m_dw->m_drawLines.at(i).GetFirst() && nodeName == this->m_dw->m_drawLines.at(i).GetSecond()) )
      {
        this->m_dw->m_drawLines.erase(this->m_dw->m_drawLines.begin() + i);
      }
    }
    return;
  }
  this->m_gen->GetLink(linkNumber)->Install(nodeName);
}

void MainWindow::GenerateCpp()
{
  this->m_gen->GenerateCode();
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
  QLabel *m_appsPing;
  m_appsPing = new QLabel("Ping", dialog);
  layout->addWidget(m_appsPing, 2, 0);

  QCheckBox *box_m_appsPing = new QCheckBox(dialog);
  layout->addWidget(box_m_appsPing, 2, 1);

  /* UDP ECHO */
  QLabel *m_appsUdpEcho;
  m_appsUdpEcho = new QLabel("Udp Echo", dialog);
  layout->addWidget(m_appsUdpEcho, 3, 0);

  QCheckBox *box_m_appsUdpEcho = new QCheckBox(dialog);
  layout->addWidget(box_m_appsUdpEcho, 3, 1);

  /* TCP LARGE TRANSFER */
  QLabel *m_appsTcp;
  m_appsTcp = new QLabel("Tcp Large Transfer", dialog);
  layout->addWidget(m_appsTcp, 4, 0);

  QCheckBox *box_m_appsTcp = new QCheckBox(dialog);
  layout->addWidget(box_m_appsTcp, 4, 1);

  layout->addWidget(buttonBox, 15, 3);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    if(box_m_appsPing->isChecked())
    {
      this->m_dw->m_appsPing = true;
      this->m_dw->ShowGuiPing();
    }
    else if(box_m_appsUdpEcho->isChecked())
    {
      this->m_dw->m_appsUdpEcho = true;
      this->m_dw->ShowGuiUdpEcho();
    }
    else if(box_m_appsTcp->isChecked())
    {
      this->m_dw->m_appsTcp = true;
      this->m_dw->ShowGuiTcp();
    }
  }
}

void MainWindow::ValidApps()
{
  if(this->m_dw->m_appsPing)
  {
    this->m_gen->AddApplication("Ping", this->m_dw->m_appsServer, this->m_dw->m_appsClient, this->m_dw->m_startTime, this->m_dw->m_endTime);
    QMessageBox::about(this, "Ping", "Ping successfull installed.");
  }

  if(this->m_dw->m_appsUdpEcho)
  {
    this->m_gen->AddApplication("UdpEcho", this->m_dw->m_appsServer, this->m_dw->m_appsClient, this->m_dw->m_startTime, this->m_dw->m_endTime, this->m_dw->m_port);
    QMessageBox::about(this, "Udp Echo", "Udp echo successfull installed.");
  }

  if(this->m_dw->m_appsTcp)
  {
    this->m_gen->AddApplication("TcpLargeTransfer", this->m_dw->m_appsServer, this->m_dw->m_appsClient, this->m_dw->m_startTime, this->m_dw->m_endTime, this->m_dw->m_port);
    QMessageBox::about(this, "Tcp Large Transfer", "Tcp large transfer successfull installed.");
  }

  this->m_dw->m_appsPing = false;
  this->m_dw->m_appsUdpEcho = false;
  this->m_dw->m_appsTcp = false;
  this->m_dw->m_appsServer = "";
  this->m_dw->m_appsClient = "";
  this->m_dw->m_startTime = 0;
  this->m_dw->m_endTime = 0;
  this->m_dw->m_port = 0;
}

