#include <iostream>

#include "Graph.h"
#include "dragwidget.h"

Graph::Graph()
{
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
   
   QMenu *menuAbout = menuBar()->addMenu("&About");
   //à voir.
   //menuAbout->addAction("");
   
   //
   // toolbar for add equipements.
   //
   QToolBar *toolBarFichier = addToolBar("Fichier");
   //Delete button
   QIcon delIcon("Ico/Del.png");
   QString delString("Delete");  
   QAction *delAction = toolBarFichier->addAction(delIcon, delString);
   connect(delAction, SIGNAL(triggered()), this, SLOT(deleteObject()));
   //PC
   QIcon pcIcon("Ico/PC.png");
   QString pcString("Terminal");  
   QAction *pcAction = toolBarFichier->addAction(pcIcon, pcString);
   connect(pcAction, SIGNAL(triggered()), this, SLOT(addPC()));
   //PC-Emu
   QIcon emuIcon("Ico/PC-Emu.png");
   QString emuString("PC with emu");  
   QAction *emuAction = toolBarFichier->addAction(emuIcon, emuString);
   connect(emuAction, SIGNAL(triggered()), this, SLOT(addPC_Emu()));
   //PC-Tap
   QIcon tapIcon("Ico/PC-Tap.png");
   QString tapString("PC with tap");  
   QAction *tapAction = toolBarFichier->addAction(tapIcon, tapString);
   connect(tapAction, SIGNAL(triggered()), this, SLOT(addPC_Tap()));
   //AP-Wifi
   QIcon apIcon("Ico/AP-Wifi.png");
   QString apString("AP Wifi");  
   QAction *apAction = toolBarFichier->addAction(apIcon, apString);
   connect(apAction, SIGNAL(triggered()), this, SLOT(addAP()));
   //StationWifi
   QIcon stasIcon("Ico/StationWifi.png");
   QString stasString("Station Wifi");  
   QAction *stasAction = toolBarFichier->addAction(stasIcon, stasString);
   connect(stasAction, SIGNAL(triggered()), this, SLOT(addStation()));
   //Hub
   QIcon hubIcon("Ico/Hub.png");
   QString hubString("Hub");  
   QAction *hubAction = toolBarFichier->addAction(hubIcon, hubString);
   connect(hubAction, SIGNAL(triggered()), this, SLOT(addHub()));
   //Switch
   QIcon switchIcon("Ico/Switch.png");
   QString switchString("Switch");  
   QAction *switchAction = toolBarFichier->addAction(switchIcon, switchString);
   connect(switchAction, SIGNAL(triggered()), this, SLOT(addSwitch()));
   //Router
   QIcon routerIcon("Ico/Router.png");
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

void Graph::addPC()
{
	dw->CreateObject("PC");
}

void Graph::addPC_Emu()
{
	dw->CreateObject("PC-Emu");
}

void Graph::addPC_Tap()
{
	dw->CreateObject("PC-Tap");
}

void Graph::addAP()
{
	dw->CreateObject("AP");
}

void Graph::addStation()
{
	dw->CreateObject("StationWifi");
}

void Graph::deleteObject()
{
	dw->deleteLastSelected();
}

void Graph::addHub()
{
	dw->CreateObject("Hub");
}

void Graph::addSwitch()
{
	dw->CreateObject("Switch");
}

void Graph::addRouter()
{
	dw->CreateObject("Router");
}

void Graph::ConfigurationMenu()
{
    Configuration *config = new Configuration();
}



