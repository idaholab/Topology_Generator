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
  this->SetDragWidget(NULL);
  this->SetGenerator(new Generator(simulationName));

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
  QAction *menuSaveAs = menuFichier->addAction("Save as");
  menuSaveAs->setDisabled(true);
  QAction *menuSavePix = menuFichier->addAction("Save as picture");
  connect(menuSavePix, SIGNAL(triggered()), this, SLOT(SavePicture()));
  /* menuSavePix->setDisabled(true); */

  QAction *actionQuit = menuFichier->addAction("Quit");
  connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdit = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdit->addAction("Configuration");
  actionConfig->setDisabled(true);
  connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 

  QMenu *menuView = menuBar()->addMenu("&Generate");
  QAction *actionCpp = menuView->addAction("&C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  QAction *actionPython = menuView->addAction("&Python");
  connect(actionPython, SIGNAL(triggered()), this, SLOT(GeneratePython()));

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
  this->SetDelQAction(toolBarFichier->addAction(delIcon, delString));
  this->GetDelQAction()->setDisabled (true);  
  connect(this->GetDelQAction(), SIGNAL(triggered()), this, SLOT(DeleteObject()));

  //
  // Creation of Drag N Drop Area.
  //
  QHBoxLayout *dragLayout = new QHBoxLayout;
  this->SetDragWidget(new DragWidget());

  dragLayout->addWidget(GetDragWidget());

  QWidget *zoneCentral = new QWidget; 
  zoneCentral->setLayout(dragLayout);

  this->setCentralWidget(zoneCentral);

  //
  // 
  //
  this->GetDragWidget()->SetMainWindow(this);
}

MainWindow::~MainWindow()
{
  delete this->GetGenerator();
}

void MainWindow::CreatePc()
{
  this->GetGenerator()->AddNode("Pc");
  GetDragWidget()->CreateObject("Pc", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
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

  this->GetGenerator()->AddNode("Pc",number);
  GetDragWidget()->CreateObject("Pc-group", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
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
    for(size_t i = 0; i < (size_t) this->GetIfaceList().size(); i++)
    {
      if( text.toStdString() == this->GetNIfaceList(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->AddIfaceList(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->GetGenerator()->AddNode("Pc");
  this->GetGenerator()->AddLink("Emu", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  GetDragWidget()->CreateObject("Emu",this->GetGenerator()->GetLink(this->GetGenerator()->GetNLinks() - 1)->GetLinkName());
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
    for(size_t i = 0; i < (size_t) this->GetIfaceList().size(); i++)
    {
      if( text.toStdString() == this->GetNIfaceList(i))
      {
        /* interface already used ... */
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->AddIfaceList(text.toStdString());
  }
  else
  {
    /* cancel button or no text ... */
    return;
  }

  this->GetGenerator()->AddNode("Tap");
  this->GetGenerator()->AddLink("Tap", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  GetDragWidget()->CreateObject("Tap",this->GetGenerator()->GetLink(this->GetGenerator()->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CleanIface()
{
  /* remove from list the unused iface. */
  bool used = false;
  for(size_t i = 0; i < (size_t) this->GetIfaceList().size(); i++)
  {
    used = false;
    for(size_t j = 0; j < this->GetGenerator()->GetNLinks(); j++)
    {
      if( (this->GetGenerator()->GetLink(j)->GetLinkName()).find("tap_") == 0)
      {
        if( this->GetNIfaceList(i) == static_cast<Tap*>(this->GetGenerator()->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
      if( (this->GetGenerator()->GetLink(j)->GetLinkName()).find("emu_") == 0 ) 
      {
        if( this->GetNIfaceList(i) == static_cast<Emu*>(this->GetGenerator()->GetLink(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
    }
    if(!used)
    {
      this->EraseIfaceList(i);
    }
  }
}

void MainWindow::CreateAp()
{  
  this->GetGenerator()->AddNode("Ap");
  this->GetGenerator()->AddLink("Ap", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
  GetDragWidget()->CreateObject("Ap", this->GetGenerator()->GetLink(this->GetGenerator()->GetNLinks() - 1)->GetLinkName() );
}

void MainWindow::CreateStation()
{
  this->GetGenerator()->AddNode("Station");
  GetDragWidget()->CreateObject("Station", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateHub()
{
  this->GetGenerator()->AddLink("Hub");
  GetDragWidget()->CreateObject("Hub", this->GetGenerator()->GetLink(this->GetGenerator()->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateSwitch()
{
  this->GetGenerator()->AddNode("Bridge");
  this->GetGenerator()->AddLink("Bridge", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
  GetDragWidget()->CreateObject("Switch",this->GetGenerator()->GetLink(this->GetGenerator()->GetNLinks() - 1)->GetLinkName());
}

void MainWindow::CreateRouter()
{
  this->GetGenerator()->AddNode("Router");
  GetDragWidget()->CreateObject("Router", this->GetGenerator()->GetNode(this->GetGenerator()->GetNNodes() - 1)->GetNodeName());
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
  if(this->GetDragWidget()->GetTraceLink())
  {
    this->GetDragWidget()->SetTraceLink(false);
    this->GetDragWidget()->ResetSelected();
    return;
  }
  this->GetDragWidget()->SetTraceLink(true);
  this->GetDragWidget()->SetLinkType("WiredLink");
}

void MainWindow::ValidLink()
{
  /* function called when the two equipement are selected. */
  /* get the selected equipement. */
  this->GetDragWidget()->SetTraceLink(false);

  std::vector<std::string> equi = this->GetDragWidget()->GetLastSelected();
  size_t indic = 0;

  if(equi.at(0) == "" || equi.at(1) == "" || equi.at(0) == "deleted" || equi.at(1) == "deleted")
  {
    QMessageBox::about(this, "Error", "You don't have selected two equipement.");
    for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) )
      {
        this->GetDragWidget()->EraseDrawLines(i);
      }
    }
    this->GetDragWidget()->ResetSelected();
    return;
  }

  if(equi.at(0) == equi.at(1))
  {
    QMessageBox::about(this, "Error", "You can't connect object to itself.");
    for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) )
      {
        this->GetDragWidget()->EraseDrawLines(i);
      }
    }
    this->GetDragWidget()->ResetSelected();
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
    for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
    {
      if( (equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) ||
          (equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) )
      {
        this->GetDragWidget()->EraseDrawLines(i);
      }
    }
    this->GetDragWidget()->ResetSelected();
    return;
  }
  //
  // OTHERS
  //
  else if( (equi.at(0)).find("hub_") == 0 || (equi.at(0)).find("bridge_") == 0 || 
      (equi.at(0)).find("emu_") == 0 || (equi.at(0).find("tap_") == 0 ))
  {
    indic = 0;
    for(size_t i = 0; i < (size_t) this->GetGenerator()->GetNLinks(); i++)
    { 
      if( this->GetGenerator()->GetLink(i)->GetLinkName() == equi.at(0))
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
    for(size_t i = 0; i < (size_t) this->GetGenerator()->GetNLinks(); i++)
    { 
      if( this->GetGenerator()->GetLink(i)->GetLinkName() == equi.at(1))
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

    for(size_t i = 0; i < (size_t) this->GetGenerator()->GetNLinks(); i++)
    {
      if(equi.at(0) == this->GetGenerator()->GetLink(i)->GetLinkName())
      {
        number = i;
        break;
      }
      if(equi.at(1) == this->GetGenerator()->GetLink(i)->GetLinkName())
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
        this->GetGenerator()->AddLink("Hub");
        this->ConnectNode((this->GetGenerator()->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->GetGenerator()->GetNLinks() - 1), equi.at(1));
      }
      else if(equi.at(2) == "P2pLink")
      {
        this->GetGenerator()->AddLink("PointToPoint");
        this->ConnectNode((this->GetGenerator()->GetNLinks() - 1), equi.at(0));
        this->ConnectNode((this->GetGenerator()->GetNLinks() - 1), equi.at(1));
      }
      else
      {
        QMessageBox::about(this, "Error", "An error occured.");
        /* delete the two equi .... */
        for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
        {
          if(equi.at(0) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() || equi.at(1) == this->GetDragWidget()->GetNDrawLines(i).GetFirst() )
          {
            this->GetDragWidget()->EraseDrawLines(i);
          }
        }
      }
    } 
  }

  /* Draw the connection. */
  this->GetDragWidget()->DrawLine();
  this->GetDragWidget()->ResetSelected();
}

void MainWindow::CreateStationLink()
{
  if(this->GetDragWidget()->GetTraceLink())
  {
    this->GetDragWidget()->SetTraceLink(false);
    this->GetDragWidget()->ResetSelected();
    return;
  }
  this->GetDragWidget()->SetTraceLink(true);
  this->GetDragWidget()->SetLinkType("WifiLink");
}

void MainWindow::CreateP2pLink()
{
  if(this->GetDragWidget()->GetTraceLink())
  {
    this->GetDragWidget()->SetTraceLink(false);
    this->GetDragWidget()->ResetSelected();
    return;
  }
  this->GetDragWidget()->SetTraceLink(true);
  this->GetDragWidget()->SetLinkType("P2pLink");
}

void MainWindow::ConfigurationMenu()
{
}

void MainWindow::DeleteObject()
{
  this->GetDragWidget()->DeleteSelected();
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
    this->GetGenerator()->GetLink(linkNumber);
  }
  catch(const std::out_of_range &e)
  {
    QMessageBox::about(this, "Error", "This link doesn't exist.");
    for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
    {
      if( (nodeName == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && this->GetGenerator()->GetLink(linkNumber)->GetLinkName() == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) ||
          (this->GetGenerator()->GetLink(linkNumber)->GetLinkName() == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && nodeName == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) )
      {
        this->GetDragWidget()->EraseDrawLines(i);
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
    for(size_t i = 0; i < (size_t) this->GetGenerator()->GetNNodes(); i++)
    {
      if(nodeName == this->GetGenerator()->GetNode(i)->GetNodeName())
      {
        numberOfConnectedMachines += MainWindow::GetGenerator()->GetNode(i)->GetMachinesNumber();
      }
    }
  }

  /* get the number of machines also connected. */
  std::vector<std::string> nodes = this->GetGenerator()->GetLink(linkNumber)->GetInstalledNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->GetGenerator()->GetNNodes(); j++)
    {
      if(nodes.at(i) == this->GetGenerator()->GetNode(j)->GetNodeName())
      {
        numberOfConnectedMachines += this->GetGenerator()->GetNode(j)->GetMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    for(size_t i = 0; i < (size_t) this->GetDragWidget()->GetDrawLines().size(); i++)
    {
      if( (nodeName == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && this->GetGenerator()->GetLink(linkNumber)->GetLinkName() == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) ||
          (this->GetGenerator()->GetLink(linkNumber)->GetLinkName() == this->GetDragWidget()->GetNDrawLines(i).GetFirst() && nodeName == this->GetDragWidget()->GetNDrawLines(i).GetSecond()) )
      {
        this->GetDragWidget()->EraseDrawLines(i);
      }
    }
    return;
  }
  this->GetGenerator()->GetLink(linkNumber)->Install(nodeName);
}

void MainWindow::GenerateCpp()
{
  this->GetGenerator()->GenerateCodeCpp();
}

void MainWindow::GeneratePython()
{
  this->GetGenerator()->GenerateCodePython();
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
      this->GetDragWidget()->SetAppsPing(true);
      this->GetDragWidget()->ShowGuiPing();
    }
    else if(box_m_appsUdpEcho->isChecked())
    {
      this->GetDragWidget()->SetAppsUdpEcho(true);
      this->GetDragWidget()->ShowGuiUdpEcho();
    }
    else if(box_m_appsTcp->isChecked())
    {
      this->GetDragWidget()->SetAppsTcp(true);
      this->GetDragWidget()->ShowGuiTcp();
    }
  }
}

void MainWindow::ValidApps()
{
  if(this->GetDragWidget()->GetAppsPing())
  {
    this->GetGenerator()->AddApplication("Ping", this->GetDragWidget()->GetAppsServer(), this->GetDragWidget()->GetAppsClient(), this->GetDragWidget()->GetStartTime(), this->GetDragWidget()->GetEndTime());
    QMessageBox::about(this, "Ping", "Ping successfull installed.");
  }

  if(this->GetDragWidget()->GetAppsUdpEcho())
  {
    this->GetGenerator()->AddApplication("UdpEcho", this->GetDragWidget()->GetAppsServer(), this->GetDragWidget()->GetAppsClient(), this->GetDragWidget()->GetStartTime(), this->GetDragWidget()->GetEndTime(), this->GetDragWidget()->GetPort());
    QMessageBox::about(this, "Udp Echo", "Udp echo successfull installed.");
  }

  if(this->GetDragWidget()->GetAppsTcp())
  {
    this->GetGenerator()->AddApplication("TcpLargeTransfer", this->GetDragWidget()->GetAppsServer(), this->GetDragWidget()->GetAppsClient(), this->GetDragWidget()->GetStartTime(), this->GetDragWidget()->GetEndTime(), this->GetDragWidget()->GetPort());
    QMessageBox::about(this, "Tcp Large Transfer", "Tcp large transfer successfull installed.");
  }

  this->GetDragWidget()->SetAppsPing(false);
  this->GetDragWidget()->SetAppsUdpEcho(false);
  this->GetDragWidget()->SetAppsTcp(false);
  this->GetDragWidget()->SetAppsServer("");
  this->GetDragWidget()->SetAppsClient("");
  this->GetDragWidget()->SetStartTime(0);
  this->GetDragWidget()->SetEndTime(0);
  this->GetDragWidget()->SetPort(0);
}

void MainWindow::SavePicture()
{
  QFileDialog dlg(this, tr("Save image"));

  dlg.setFileMode(QFileDialog::AnyFile);
 
  if(dlg.exec())
  {
    QImage img = QPixmap::grabWidget(this->GetDragWidget()).toImage();
    QString fileName = dlg.selectedFiles().at(0);

    /* check if file exists and notificate the user */
    if(QFile(fileName).exists())
    {
      if(QMessageBox(QMessageBox::Question, "File exists", "File already exists. Overwrite ?", 
            QMessageBox::Ok | QMessageBox::No).exec() != QMessageBox::Ok)
      {
        return;
      }
    }

    if(img.save(fileName))
    {
      QMessageBox(QMessageBox::Information, "Save picture", "Picture saved at " + fileName).exec();
    }
    else
    {
      QMessageBox(QMessageBox::Warning, "Save picture", "Picture saving failed!").exec();
    }
  }
}

void MainWindow::SetGenerator(Generator *gen)
{
  this->m_gen = gen;
}

Generator* MainWindow::GetGenerator()
{
  return this->m_gen;
}

void MainWindow::SetDelQAction(QAction *delAction)
{
  this->m_delAction = delAction;
}

QAction* MainWindow::GetDelQAction()
{
  return this->m_delAction;
}

void MainWindow::SetDragWidget(DragWidget *dw)
{
  this->m_dw = dw;
}

DragWidget* MainWindow::GetDragWidget()
{
  return this->m_dw;
}

void MainWindow::AddIfaceList(const std::string &str)
{
  this->m_listIface.push_back(str);
}

std::vector<std::string> MainWindow::GetIfaceList()
{
  return this->m_listIface;
}

std::string MainWindow::GetNIfaceList(const size_t &index)
{
  return this->m_listIface.at(index);
}

void MainWindow::EraseIfaceList(const size_t &index)
{
  this->m_listIface.erase(this->m_listIface.begin() + index);
}

