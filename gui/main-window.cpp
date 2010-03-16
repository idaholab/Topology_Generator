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

#include "ap.h"
#include "tap.h"
#include "emu.h"

#include "tcp-large-transfer.h"
#include "udp-echo.h"

#include "utils.h"
#include "gui-utils.h"
#include "array-utils.h"

#include "application-dialog.h"

MainWindow::MainWindow(const std::string &simulationName)
{
  this->m_dw = NULL;
  this->m_gen = new Generator(simulationName);

  //
  // Menu
  //
  QMenu *menuFichier = menuBar()->addMenu("&File");
  /*
  QAction *menuOpen = menuFichier->addAction("Open");
  menuOpen->setDisabled(true);
  
  QAction *menuNew = menuFichier->addAction("New");
  menuNew->setDisabled(true);
  
  QAction *menuSave = menuFichier->addAction("Save");
  menuSave->setDisabled(true);
  
  QAction *menuSaveAs = menuFichier->addAction("Save as");
  menuSaveAs->setDisabled(true);
  */
  QAction *menuSavePix = menuFichier->addAction("Save as picture");
  connect(menuSavePix, SIGNAL(triggered()), this, SLOT(SavePicture()));
  
  QAction *menuXml = menuFichier->addAction("Save as XML");
  connect(menuXml, SIGNAL(triggered()), this, SLOT(SaveXml()));
  
  QAction *menuXmlLoad = menuFichier->addAction("Load XML file");
  connect(menuXmlLoad, SIGNAL(triggered()), this, SLOT(LoadXml()));

  QAction *actionQuit = menuFichier->addAction("Quit");
  connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

  QMenu *menuEdit = menuBar()->addMenu("&Edit");
  QAction *actionConfig = menuEdit->addAction("Configuration");
  actionConfig->setDisabled(true);
  //connect(actionConfig, SIGNAL(triggered()), this, SLOT(ConfigurationMenu())); 

  QMenu *menuView = menuBar()->addMenu("&Generate");
  QAction *actionCpp = menuView->addAction("&C++");
  connect(actionCpp, SIGNAL(triggered()), this, SLOT(GenerateCpp())); 
  QAction *actionPython = menuView->addAction("&Python");
  connect(actionPython, SIGNAL(triggered()), this, SLOT(GeneratePython()));

  QMenu *menuHelp = menuBar()->addMenu("&Help");
  QAction *menuOnlineHelp = menuHelp->addAction("Online Help");
  menuOnlineHelp->setDisabled(true);
  //connect(menuOnlineHelp, SIGNAL(triggered()), this, SLOT(Help()));
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
  connect(stasLinkAction, SIGNAL(triggered()), this, SLOT(CreateWifiLink()));
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
  connect(appsLinkAction, SIGNAL(triggered()), this, SLOT(CreateApplication()));
  //separator
  toolBarFichier->addSeparator();
  //Delete button
  QIcon delIcon(":/Ico/Del.png");
  QString delString("Delete");
  this->m_delAction = toolBarFichier->addAction(delIcon, delString);
  this->m_delAction->setDisabled (true);  
  connect(this->m_delAction, SIGNAL(triggered()), this, SLOT(DeleteObject()));

  //
  // Creation of Drag N Drop Area.
  //
  QHBoxLayout *dragLayout = new QHBoxLayout;
  this->m_dw = new DragWidget();

  dragLayout->addWidget(this->m_dw);

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
  delete this->m_gen;
}

void MainWindow::SetGenerator(Generator *gen)
{
  this->m_gen = gen;
}

Generator* MainWindow::GetGenerator()
{
  return this->m_gen;
}

void MainWindow::CleanIface()
{
  bool used = false;
  for(size_t i = 0; i < this->m_listIface.size(); i++)
  {
    used = false;
    for(size_t j = 0; j < this->m_gen->GetNNetworkHardwares(); j++)
    {
      if( (this->m_gen->GetNetworkHardware(j)->GetNetworkHardwareName()).find("tap_") == 0)
      {
        if( this->m_listIface.at(i) == static_cast<Tap*>(this->m_gen->GetNetworkHardware(j))->GetIfaceName())
        {
          used = true;
          break;
        }
      }
      if( (this->m_gen->GetNetworkHardware(j)->GetNetworkHardwareName()).find("emu_") == 0 ) 
      {
        if( this->m_listIface.at(i) == static_cast<Emu*>(this->m_gen->GetNetworkHardware(j))->GetIfaceName())
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

void MainWindow::CreatePc()
{
  this->m_gen->AddNode("Pc");
  this->m_dw->CreateObject("Pc", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreatePcGroup()
{
  bool ok;
  size_t number = 0;
  QString text = QInputDialog::getText(this, "Terminal Group", tr("Enter the number of machines to create :"), QLineEdit::Normal,"", &ok);
  if (ok && !text.isEmpty())
  {
    number = text.toUInt();
  }
  else
  {
    return;
  }

  if(number <= 0 )
  {
    QMessageBox::about(this, "Error", "The pc number can't be negative ...");
    return;
  }

  this->m_gen->AddNode("Pc-group",number);
  this->m_dw->CreateObject("Pc-group", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateEmu()
{
  this->CleanIface();

  bool ok;
  QString text = QInputDialog::getText(this, "Emu", tr("Enter the real host interface to use:"), QLineEdit::Normal, "eth0", &ok);
  if (ok && !text.isEmpty())
  {
    for(size_t i = 0; i < this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    return;
  }

  this->m_gen->AddNode("Emu");
  this->m_gen->AddNetworkHardware("Emu", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  this->m_dw->CreateObject("Emu",this->m_gen->GetNetworkHardware(this->m_gen->GetNNetworkHardwares() - 1)->GetNetworkHardwareName());
}

void MainWindow::CreateTap()
{
  this->CleanIface();

  bool ok;
  QString text = QInputDialog::getText(this, "Tap", tr("Enter the new interface to use :"), QLineEdit::Normal, "tap0", &ok);
  if (ok && !text.isEmpty())
  {
    for(size_t i = 0; i < this->m_listIface.size(); i++)
    {
      if( text.toStdString() == this->m_listIface.at(i))
      {
        QMessageBox::about(this, "Error", "The specified interface is already used ...");
        return;
      }
    }
    this->m_listIface.push_back(text.toStdString());
  }
  else
  {
    return;
  }

  this->m_gen->AddNode("Tap");
  this->m_gen->AddNetworkHardware("Tap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName(), text.toStdString());
  this->m_dw->CreateObject("Tap",this->m_gen->GetNetworkHardware(this->m_gen->GetNNetworkHardwares() - 1)->GetNetworkHardwareName());
}

void MainWindow::CreateAp()
{  
  this->m_gen->AddNode("Ap");
  this->m_gen->AddNetworkHardware("Ap", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  this->m_dw->CreateObject("Ap", this->m_gen->GetNetworkHardware(this->m_gen->GetNNetworkHardwares() - 1)->GetNetworkHardwareName() );
}

void MainWindow::CreateStation()
{
  this->m_gen->AddNode("Station");
  this->m_dw->CreateObject("Station", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateHub()
{
  this->m_gen->AddNetworkHardware("Hub");
  this->m_dw->CreateObject("Hub", this->m_gen->GetNetworkHardware(this->m_gen->GetNNetworkHardwares() - 1)->GetNetworkHardwareName());
}

void MainWindow::CreateSwitch()
{
  this->m_gen->AddNode("Bridge");
  this->m_gen->AddNetworkHardware("Bridge", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
  this->m_dw->CreateObject("Bridge",this->m_gen->GetNetworkHardware(this->m_gen->GetNNetworkHardwares() - 1)->GetNetworkHardwareName());
}

void MainWindow::CreateRouter()
{
  this->m_gen->AddNode("Router");
  this->m_dw->CreateObject("Router", this->m_gen->GetNode(this->m_gen->GetNNodes() - 1)->GetNodeName());
}

void MainWindow::CreateWiredLink()
{
  if(this->m_dw->GetTraceNetworkHardware())
  {
    this->m_dw->SetTraceNetworkHardware(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceNetworkHardware(true);
  this->m_dw->SetNetworkHardwareType("WiredLink");
}

void MainWindow::CreateWifiLink()
{
  if(this->m_dw->GetTraceNetworkHardware())
  {
    this->m_dw->SetTraceNetworkHardware(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceNetworkHardware(true);
  this->m_dw->SetNetworkHardwareType("WifiLink");
}

void MainWindow::CreateP2pLink()
{
  if(this->m_dw->GetTraceNetworkHardware())
  {
    this->m_dw->SetTraceNetworkHardware(false);
    this->m_dw->ResetSelected();
    return;
  }
  this->m_dw->SetTraceNetworkHardware(true);
  this->m_dw->SetNetworkHardwareType("P2pLink");
}

void MainWindow::CreateApplication()
{
  if(!this->m_dw->m_appsPing && !this->m_dw->m_appsUdpEcho && !this->m_dw->m_appsTcp)
  {
    this->m_appsDialog = new ApplicationDialog(this->m_dw);
    this->m_appsDialog->exec();
  }
}

void MainWindow::ConnectNode(const std::string &linkName, const std::string &nodeName)
{
  size_t linkNumber = -1;

  // search link
  for(size_t i = 0; i < this->m_gen->GetNNetworkHardwares(); i++)
  {
    if(linkName == this->m_gen->GetNetworkHardware(i)->GetNetworkHardwareName())
    {
      linkNumber = i;
      break;
    }
  }

  // get the params network connected equipements.
  size_t numberOfConnectedMachines = 0;
  if(nodeName.find("Get") == 0)
  {
    numberOfConnectedMachines += 1;
  }
  else
  {
    for(size_t i = 0; i < this->m_gen->GetNNodes(); i++)
    {
      if(nodeName == this->m_gen->GetNode(i)->GetNodeName())
      {
        numberOfConnectedMachines += this->m_gen->GetNode(i)->GetMachinesNumber();
      }
    }
  }

  // get the current (destination) network connected equipements.
  std::vector<std::string> nodes = this->m_gen->GetNetworkHardware(linkNumber)->GetInstalledNodes();
  for(size_t i = 0; i < nodes.size(); i++)
  {
    for(size_t j = 0; j < this->m_gen->GetNNodes(); j++)
    {
      if(nodes.at(i) == this->m_gen->GetNode(j)->GetNodeName())
      {
        numberOfConnectedMachines += this->m_gen->GetNode(j)->GetMachinesNumber();
      }
    }
  }

  // prevent overflow
  if( numberOfConnectedMachines > (255 -2) )
  {
    QMessageBox::about(this, "Error", "Limit of machines exceeded.");
    for(size_t i = 0; i < this->m_dw->GetDrawLines().size(); i++)
    {
      if( (nodeName == this->m_dw->GetDrawLine(i).GetFirst() && 
          this->m_gen->GetNetworkHardware(linkNumber)->GetNetworkHardwareName() == this->m_dw->GetDrawLine(i).GetSecond()) ||
          (this->m_gen->GetNetworkHardware(linkNumber)->GetNetworkHardwareName() == this->m_dw->GetDrawLine(i).GetFirst() && 
           nodeName == this->m_dw->GetDrawLine(i).GetSecond()) )
      {
        this->m_dw->EraseDrawLine(i);
        return;
      }
    }
    return;
  }

  // install the params node to the dest network
  this->m_gen->GetNetworkHardware(linkNumber)->Install(nodeName);
}

void MainWindow::GenerateCpp()
{
  this->m_gen->GenerateCodeCpp();
}

void MainWindow::GeneratePython()
{
  this->m_gen->GenerateCodePython();
}

void MainWindow::DeleteObject()
{
  this->m_dw->DeleteSelected();
}

void MainWindow::About()
{
  QMessageBox::about(this, "About",
      tr("<p align=\"center\">"
        "<h2>The ns-3 topology generator"
        "</h2>"
        "</p><br />"
        "Copyright (c) 2009-2010 University of Strasbourg<br /><br />"
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

void MainWindow::SavePicture()
{
  QFileDialog dlg(this, tr("Save image"));

  dlg.setFileMode(QFileDialog::AnyFile);
 
  if(dlg.exec())
  {
    QImage img = QPixmap::grabWidget(this->m_dw).toImage();
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

void MainWindow::SaveXml()
{
  QString fileName = "";
  QFileDialog dlg(this, tr("Save XML"));

  dlg.setFileMode(QFileDialog::AnyFile);
 
  if(dlg.exec())
  {
    fileName = dlg.selectedFiles().at(0);

    /* check if file exists and notificate the user */
    if(QFile(fileName).exists())
    {
      if(QMessageBox(QMessageBox::Question, "File exists", "File already exists. Overwrite ?", 
            QMessageBox::Ok | QMessageBox::No).exec() != QMessageBox::Ok)
      {
        return;
      }
    }
  }

  //QString fileName = "test.xml";
  QFile file(fileName);
  file.open(QFile::WriteOnly | QFile::Text);
  QXmlStreamWriter *writer = new QXmlStreamWriter(&file);
  
  guiUtils::saveXml(writer, this->m_gen, this->m_dw);
  
  file.close();

  QMessageBox(QMessageBox::Information, "Save Simulation", "Simulation saved at " + fileName).exec();
}

void MainWindow::LoadXml()
{
  QString fileName = "";
  QFileDialog dlg(this, tr("Load XML"));

  dlg.setFileMode(QFileDialog::AnyFile);
 
  if(dlg.exec())
  {
    fileName = dlg.selectedFiles().at(0);

    if(!QFile(fileName).exists())
    {
      QMessageBox(QMessageBox::Information, "File don't exists", "File don't exists.").exec();
      return;
    }
  }

  QFile file(fileName);
  file.open(QFile::ReadOnly | QFile::Text);
  QXmlStreamReader *reader = new QXmlStreamReader(&file);
  
  guiUtils::loadXml(reader, this->m_gen, this->m_dw);
  
  file.close();

  QMessageBox(QMessageBox::Information, "Load Simulation", "Simulation loaded.").exec();
}

