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
 * \file main.cpp
 * \brief The ns-3 generator.
 * \author Pierre Weiss
 */

using namespace std;

#include <cstdlib>
#include <csignal>

#include <iostream>
#include <limits>
#include <stdexcept>

#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>

#include "kern/generator.h"
#include "gui/main-window.h"

/**
 * \var VERSION
 * \brief Current version.
 */
const char* VERSION = "0.1";

/**
 * \brief Signal handler.
 * \param code signal code received
 * \author Sebastien Vincent
 */
static void signalHandler(int code)
{
  switch(code)
  {
    case SIGTERM:
    case SIGINT:
      /* quit Qt application */
      qApp->quit();
      break;
    default:
      break;
  }
}

/**
 * \brief Print help menu.
 * \param name name of the program
 * \param version version of the program
 */
static void printHelp(const char* name, const char* version)
{
  std::cout << "ns-3-generator " << version << std::endl;
  std::cout << "Usage: " << name << " [-h] [-v]" << std::endl;
}

/**
 * \brief Parse the command line arguments.
 * \param argc number of argument
 * \param argv array of argument
 */
static void parseCmdline(int argc, char** argv)
{
  static const char* optstr = "hv";
  int s = 0;

  while((s = getopt(argc, argv, optstr)) != -1)
  {
    switch(s)
    {
      case 'h': /* help */
        printHelp(argv[0], VERSION);
        exit(EXIT_SUCCESS);
        break;
      case 'v': /* version */
        std::cout << "ns-3-generator " << VERSION << std::endl;
        std::cout << "Copyright (C) 2009 University of Strasbourg." << std::endl;
        std::cout <<"This is free software; see the source for copying conditions.  There is NO" << std::endl;
        std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << std::endl << std::endl;
        exit(EXIT_SUCCESS);
        break;
      default:
        break;
    }
  }
}

#if TEST
static void printState(Generator *gen)
{
  std::cout << "Nodes :" << std::endl;
  for(int i = 0; (size_t) i < gen->GetNNodes(); i++)
  {
    std::cout << "- " << gen->GetNode(i)->GetNodeName() << std::endl;
  }

  std::cout << "Link :" << std::endl;
  for(int i = 0; (size_t) i < gen->GetNLinks(); i++)
  {
    std::cout << "- " << gen->GetLink(i)->GetLinkName() << std::endl;
    for(int j = 0; (size_t) j < gen->GetLink(i)->GetInstalledNodes().size(); j++)
    {
      std::cout << "  -- " << gen->GetLink(i)->GetInstalledNodes().at(j) << std::endl;
    }
  }
}
#endif

/**
 * \brief Entry point of program.
 * \param argc number of argument
 * \param argv array of argument
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
  /* parse command line arguments */
  parseCmdline(argc, argv);

  /* catch signals */
  if(signal(SIGTERM, signalHandler) == SIG_ERR)
  {
    std::cerr << "SIGTERM will not be catched" << std::endl;
  }

  if(signal(SIGINT, signalHandler) == SIG_ERR)
  {
    std::cerr << "SIGINT will not be catched" << std::endl;
  }

  QApplication app(argc, argv);
 
  MainWindow* win = new MainWindow(std::string("Simulation generator for ns-3"));
  win->setWindowTitle("Generator");
  win->show();
    
  app.exec();
	
  delete win;

#if TEST
  Generator *gen = new Generator("Simulation name ...");
  
  gen->AddNode(std::string("Router"));//0
  gen->AddNode(std::string("Pc"), 10);//1
  gen->AddNode(std::string("Ap"));//2
  gen->AddNode(std::string("Station"));//3
  gen->AddNode(std::string("Bridge"));//4
  gen->AddNode(std::string("Tap"));//5
  gen->AddNode(std::string("Emu"));//6

  gen->AddLink(std::string("Hub"));//0
  gen->GetLink(0)->Install(gen->GetNode(0)->GetNodeName());
  gen->GetLink(0)->Install(gen->GetNode(1)->GetNodeName(0));
  gen->GetLink(0)->SetTrace(true);
  gen->GetLink(0)->SetPromisc(true);

  gen->AddLink(std::string("PointToPoint"));//1
  gen->GetLink(1)->Install(gen->GetNode(0)->GetNodeName());
  gen->GetLink(1)->Install(gen->GetNode(1)->GetNodeName(1));

  gen->AddLink(std::string("Bridge"), gen->GetNode(4)->GetNodeName());//2
  gen->GetLink(2)->Install(gen->GetNode(0)->GetNodeName());
  gen->GetLink(2)->Install(gen->GetNode(1)->GetNodeName(2));

  gen->AddLink(std::string("Ap"), gen->GetNode(2)->GetNodeName());//3
  gen->GetLink(3)->SetMobility(true);
  gen->GetLink(3)->Install(gen->GetNode(0)->GetNodeName());
  gen->GetLink(3)->Install(gen->GetNode(3)->GetNodeName());

  //gen->AddLink(std::string("Emu"), gen->GetNode(6)->GetNodeName(), std::string("wlan0"));//4
  //gen->AddLink(std::string("Tap"), gen->GetNode(5)->GetNodeName(), std::string("tap0"));//5

  gen->AddApplication(std::string("Ping"), gen->GetNode(1)->GetNodeName(0), gen->GetNode(1)->GetNodeName(1), 0, 5);
  gen->AddApplication(std::string("Ping"), gen->GetNode(1)->GetNodeName(0), gen->GetNode(1)->GetNodeName(2), 0, 5);
  gen->AddApplication(std::string("Ping"), gen->GetNode(1)->GetNodeName(0), gen->GetNode(3)->GetNodeName(), 0, 5);

  gen->GenerateCode();
 
  printState(gen);

  delete gen;
#endif

}

