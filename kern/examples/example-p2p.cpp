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

//  Topology Generated :
//
//  PC                                       PC
//      --HUB--ROUTER---p2p---ROUTER--HUB-- 
//  PC                                       PC
//

using namespace std;

#include <cstdlib>
#include <iostream>

#include "../generator.h"

int main(int argc, char *argv[])
{
  /* avoid compile warnings */
  argc = argc;
  argv = argv;
  
  Generator *gen = new Generator(std::string("example-p2p"));
  
  /* Add Node : */
  gen->AddNode("Pc");//0
  gen->AddNode("Pc");//1
  
  gen->AddNode("Router");//2
  gen->AddNode("Router");//3
  
  gen->AddNode("Pc");//4
  gen->AddNode("Pc");//5
  
  /* Add the bridge. */
  gen->AddLink("Hub");
  gen->GetLink(0)->Install(gen->GetNode(0)->getNodeName());
  gen->GetLink(0)->Install(gen->GetNode(1)->getNodeName());
  gen->GetLink(0)->Install(gen->GetNode(2)->getNodeName());
  /* Enable trace... */
  gen->GetLink(0)->setTrace(true);
  
  gen->AddLink("PointToPoint");
  gen->GetLink(1)->Install(gen->GetNode(2)->getNodeName());
  gen->GetLink(1)->Install(gen->GetNode(3)->getNodeName());
  /* Enable trace... */
  gen->GetLink(1)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->GetLink(2)->Install(gen->GetNode(3)->getNodeName());
  gen->GetLink(2)->Install(gen->GetNode(4)->getNodeName());
  gen->GetLink(2)->Install(gen->GetNode(5)->getNodeName());
  /* Enable trace... */
  gen->GetLink(2)->setTrace(true);
  
  /* Add an application */
  gen->AddApplication("Ping", gen->GetNode(0)->getNodeName(), gen->GetNode(5)->getNodeName(), 0, 5);// 0 start time - 5 end time

  gen->GenerateCodeCpp();
  
  delete gen;
}
