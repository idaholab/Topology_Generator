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
//     n6   n5   n4
//        \ |  /
//    n7 -- n0 -- n3
//        / |  \
//     n8   n1   n2
//

using namespace std;

#include <iostream>
#include <stdlib.h>
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
  gen->AddLink("Hub");
  gen->listLink.at(0)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(0)->Install(gen->listNode.at(0)->getNodeName(1));
  /* Enable trace... */
  gen->listLink.at(0)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(1)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(1)->Install(gen->listNode.at(0)->getNodeName(2));
  /* Enable trace... */
  gen->listLink.at(1)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(2)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(2)->Install(gen->listNode.at(0)->getNodeName(3));
  /* Enable trace... */
  //gen->listLink.at(2)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(3)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(3)->Install(gen->listNode.at(0)->getNodeName(4));
  /* Enable trace... */
  //gen->listLink.at(3)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(4)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(4)->Install(gen->listNode.at(0)->getNodeName(5));
  /* Enable trace... */
  gen->listLink.at(4)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(5)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(5)->Install(gen->listNode.at(0)->getNodeName(6));
  /* Enable trace... */
  //gen->listLink.at(5)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(6)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(6)->Install(gen->listNode.at(0)->getNodeName(7));
  /* Enable trace... */
  //gen->listLink.at(6)->setTrace(true);
  
  gen->AddLink("Hub");
  gen->listLink.at(7)->Install(gen->listNode.at(0)->getNodeName(0));
  gen->listLink.at(7)->Install(gen->listNode.at(0)->getNodeName(8));
  /* Enable trace... */
  //gen->listLink.at(7)->setTrace(true);
  
  /* Add an application */
  gen->AddApplication("Ping", gen->listNode.at(0)->getNodeName(1), gen->listNode.at(0)->getNodeName(5), 0, 5);// 0 start time - 5 end time


  gen->GenerateCode();
  
  delete gen;
}
