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

/*  Topology Generated :
//
//     n6   n5   n4
//        \ |  /
//    n7 -- n0 -- n3
//        / | \ 
//     n8   n1   n2
//
*/

using namespace std;

#include <cstdlib>
#include <iostream>

#include "../generator.h"

int main(int argc, char *argv[])
{
  /* avoid compile warnings */
  argc = argc;
  argv = argv;
  
  Generator *gen = new Generator(std::string("example-star"));
  
  /* Add Node : */
  gen->AddNode("Pc", 9);
  
  /* Add the bridge. */
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(0)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(0)->Install(gen->GetNode(0)->GetNodeName(1));
  /* Enable trace... */
  gen->GetNetworkHardware(0)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(1)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(1)->Install(gen->GetNode(0)->GetNodeName(2));
  /* Enable trace... */
  gen->GetNetworkHardware(1)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(2)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(2)->Install(gen->GetNode(0)->GetNodeName(3));
  /* Enable trace... */
  //gen->GetNetworkHardware(2)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(3)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(3)->Install(gen->GetNode(0)->GetNodeName(4));
  /* Enable trace... */
  //gen->GetNetworkHardware(3)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(4)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(4)->Install(gen->GetNode(0)->GetNodeName(5));
  /* Enable trace... */
  gen->GetNetworkHardware(4)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(5)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(5)->Install(gen->GetNode(0)->GetNodeName(6));
  /* Enable trace... */
  //gen->GetNetworkHardware(5)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(6)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(6)->Install(gen->GetNode(0)->GetNodeName(7));
  /* Enable trace... */
  //gen->GetNetworkHardware(6)->SetTrace(true);
  
  gen->AddNetworkHardware("Hub");
  gen->GetNetworkHardware(7)->Install(gen->GetNode(0)->GetNodeName(0));
  gen->GetNetworkHardware(7)->Install(gen->GetNode(0)->GetNodeName(8));
  /* Enable trace... */
  //gen->GetNetworkHardware(7)->SetTrace(true);
  
  /* Add an application */
  gen->AddApplication("Ping", gen->GetNode(0)->GetNodeName(1), gen->GetNode(0)->GetNodeName(5), 0, 5);// 0 start time - 5 end time


  gen->GenerateCodeCpp();
  
  delete gen;
}
