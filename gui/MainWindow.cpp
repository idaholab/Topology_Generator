#include <iostream>

#include "MainWindow.h"
#include "DragWidget.h"

MainWindow::MainWindow()
{
  
  this->dw = NULL;
  this->config = NULL;
  
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
  QIcon delIcon("./gui/Ico/Del.png");
  QString delString("Delete");  
  QAction *delAction = toolBarFichier->addAction(delIcon, delString);
  connect(delAction, SIGNAL(triggered()), this, SLOT(deleteObject()));
  //PC
  QIcon pcIcon("./gui/Ico/PC.png");
  QString pcString("Terminal");  
  QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
  connect(pcAction, SIGNAL(triggered()), this, SLOT(addPC()));
  //PC-Emu
  QIcon emuIcon("./gui/Ico/PC-Emu.png");
  QString emuString("PC with emu");  
  QAction *emuAction = toolBarFichier->addAction(emuIcon, emuString);
  connect(emuAction, SIGNAL(triggered()), this, SLOT(addPC_Emu()));
  //PC-Tap
  QIcon tapIcon("./gui/Ico/PC-Tap.png");
  QString tapString("PC with tap");  
  QAction *tapAction = toolBarFichier->addAction(tapIcon, tapString);
  connect(tapAction, SIGNAL(triggered()), this, SLOT(addPC_Tap()));
  //AP-Wifi
  QIcon apIcon("./gui/Ico/AP-Wifi.png");
  QString apString("AP Wifi");  
  QAction *apAction = toolBarFichier->addAction(apIcon, apString);
  connect(apAction, SIGNAL(triggered()), this, SLOT(addAP()));
  //StationWifi
  QIcon stasIcon("./gui/Ico/StationWifi.png");
  QString stasString("Station Wifi");  
  QAction *stasAction = toolBarFichier->addAction(stasIcon, stasString);
  connect(stasAction, SIGNAL(triggered()), this, SLOT(addStation()));
  //Hub
  QIcon hubIcon("./gui/Ico/Hub.png");
  QString hubString("Hub");  
  QAction *hubAction = toolBarFichier->addAction(hubIcon, hubString);
  connect(hubAction, SIGNAL(triggered()), this, SLOT(addHub()));
  //Switch
  QIcon switchIcon("./gui/Ico/Switch.png");
  QString switchString("Switch");  
  QAction *switchAction = toolBarFichier->addAction(switchIcon, switchString);
  connect(switchAction, SIGNAL(triggered()), this, SLOT(addSwitch()));
  //Router
  QIcon routerIcon("./gui/Ico/Router.png");
  QString routerString("Router");  
  QAction *routerAction = toolBarFichier->addAction(routerIcon, routerString);
  connect(routerAction, SIGNAL(triggered()), this, SLOT(addRouter()));
     
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
  delete dw;
  delete config;
}

void MainWindow::addPC()
{
	dw->CreateObject("Pc");
}

void MainWindow::addPC_Emu()
{
	dw->CreateObject("Emu");
}

void MainWindow::addPC_Tap()
{
	dw->CreateObject("Tap");
}

void MainWindow::addAP()
{
	dw->CreateObject("Ap");
}

void MainWindow::addStation()
{
	dw->CreateObject("Station");
}

void MainWindow::deleteObject()
{
	dw->deleteLastSelected();
}

void MainWindow::addHub()
{
	dw->CreateObject("Hub");
}

void MainWindow::addSwitch()
{
	dw->CreateObject("Switch");
}

void MainWindow::addRouter()
{
	dw->CreateObject("Router");
}

void MainWindow::ConfigurationMenu()
{
    config = new Configuration();
}



