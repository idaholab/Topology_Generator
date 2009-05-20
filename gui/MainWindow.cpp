#include <iostream>

#include "MainWindow.h"
#include "DragWidget.h"


MainWindow::MainWindow(const std::string &simulationName)
{
  
  this->dw = NULL;
  this->config = NULL;
  this->gen = new Generator(simulationName);
  
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
  menuAffichage->addAction("Cpp");
  menuAffichage->addAction("Python");
     
  QAction *menuAbout = menuBar()->addAction("About");
     
  menuAbout = menuAbout;
     
  //
  // toolbar for add equipements.
  //
  QToolBar *toolBarFichier = addToolBar("Fichier");
  //Delete button
  QIcon delIcon(":/Ico/Del.png");
  QString delString("Delete");  
  QAction *delAction = toolBarFichier->addAction(delIcon, delString);
  connect(delAction, SIGNAL(triggered()), this, SLOT(deleteObject()));
  //PC
  QIcon pcIcon(":/Ico/PC.png");
  QString pcString("Terminal");  
  QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
  connect(pcAction, SIGNAL(triggered()), this, SLOT(CreatePc()));
  //PC-Emu
  QIcon emuIcon(":/Ico/PC-Emu.png");
  QString emuString("PC with emu");  
  QAction *emuAction = toolBarFichier->addAction(emuIcon, emuString);
  connect(emuAction, SIGNAL(triggered()), this, SLOT(CreateEmu()));
  //PC-Tap
  QIcon tapIcon(":/Ico/PC-Tap.png");
  QString tapString("PC with tap");  
  QAction *tapAction = toolBarFichier->addAction(tapIcon, tapString);
  connect(tapAction, SIGNAL(triggered()), this, SLOT(CreateTap()));
  //AP-Wifi
  QIcon apIcon(":/Ico/AP-Wifi.png");
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
  // About Popup
  //
     
 
}

MainWindow::~MainWindow()
{
  //delete dw;
  delete config;
  delete gen;
}

void MainWindow::CreatePc()
{
	this->gen->AddEquipement("Pc");
	dw->CreateObject("Pc", this->gen->listEquipement.at(this->gen->listEquipement.size() - 1)->getNodeName());
}

void MainWindow::CreateEmu()
{
	dw->CreateObject("Emu","");
}

void MainWindow::CreateTap()
{
	dw->CreateObject("Tap","");
}

void MainWindow::CreateAp()
{
	dw->CreateObject("Ap","");
}

void MainWindow::CreateStation()
{
	dw->CreateObject("Station","");
}

void MainWindow::CreateHub()
{
	dw->CreateObject("Hub","");
}

void MainWindow::CreateSwitch()
{
	dw->CreateObject("Switch","");
}

void MainWindow::CreateRouter()
{
	dw->CreateObject("Router","");
}

void MainWindow::ConfigurationMenu()
{
    config = new Configuration();
}

void MainWindow::deleteObject()
{
	//~ dw->deleteLastSelected();
}



