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
 * \file main.cpp
 * \brief The ns-3 generator.
 * \author Pierre Weiss
 */

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <stdexcept>

#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>

#include "kern/Generator.h"
#include "gui/MainWindow.h"

static void printState(Generator *gen)
{
  std::cout << "Nodes :" << std::endl;
  for(int i = 0; (size_t) i < gen->listNode.size(); i++)
  {
    std::cout << "- " << gen->listNode.at(i)->getNodeName() << std::endl;
  }

  std::cout << "Link :" << std::endl;
  for(int i = 0; (size_t) i < gen->listLink.size(); i++)
  {
    std::cout << "- " << gen->listLink.at(i)->getLinkName() << std::endl;
    for(int j = 0; (size_t) j < gen->listLink.at(i)->getNodes().size(); j++)
    {
      std::cout << "  -- " << gen->listLink.at(i)->getNodes().at(j) << std::endl;
    }
  }
}

/**
 * \brief Entry point of program.
 * \param argc number of argument
 * \param argv array of argument
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
  argc = argc;
  argv = argv;

  QApplication app(argc, argv);
 
  MainWindow *win = new MainWindow(std::string("Simulation-Name"));
  win->setWindowTitle("Generator");
  win->show();
    
  app.exec();
	
  delete win;

  /*Generator *gen = new Generator("Simulation name ...");
  
  gen->AddNode(std::string("Router"));//0
  gen->AddNode(std::string("Pc"), 10);//1
  gen->AddNode(std::string("Ap"));//2
  gen->AddNode(std::string("Station"));//3
  gen->AddNode(std::string("Bridge"));//4
  gen->AddNode(std::string("Tap"));//5
  gen->AddNode(std::string("Emu"));//6

  gen->AddLink(std::string("Hub"));//0
  gen->listLink.at(0)->Install(gen->listNode.at(0)->getNodeName());
  gen->listLink.at(0)->Install(gen->listNode.at(1)->getNodeName(0));
  gen->listLink.at(0)->setTrace(true);
  gen->listLink.at(0)->setPromisc(true);

  gen->AddLink(std::string("PointToPoint"));//1
  gen->listLink.at(1)->Install(gen->listNode.at(0)->getNodeName());
  gen->listLink.at(1)->Install(gen->listNode.at(1)->getNodeName(1));

  gen->AddLink(std::string("Bridge"), gen->listNode.at(4)->getNodeName());//2
  gen->listLink.at(2)->Install(gen->listNode.at(0)->getNodeName());
  gen->listLink.at(2)->Install(gen->listNode.at(1)->getNodeName(2));

  gen->AddLink(std::string("Ap"), gen->listNode.at(2)->getNodeName());//3
  gen->listLink.at(3)->setMobility(true);
  gen->listLink.at(3)->Install(gen->listNode.at(0)->getNodeName());
  gen->listLink.at(3)->Install(gen->listNode.at(3)->getNodeName());

  //gen->AddLink(std::string("Emu"), gen->listNode.at(6)->getNodeName(), std::string("wlan0"));//4
  //gen->AddLink(std::string("Tap"), gen->listNode.at(5)->getNodeName(), std::string("tap0"));//5

  gen->AddApplication(std::string("Ping"), gen->listNode.at(1)->getNodeName(0), gen->listNode.at(1)->getNodeName(1), 0, 5);
  gen->AddApplication(std::string("Ping"), gen->listNode.at(1)->getNodeName(0), gen->listNode.at(1)->getNodeName(2), 0, 5);
  gen->AddApplication(std::string("Ping"), gen->listNode.at(1)->getNodeName(0), gen->listNode.at(3)->getNodeName(), 0, 5);

  gen->GenerateCode();
 
  printState(gen);

  delete gen;*/
}

