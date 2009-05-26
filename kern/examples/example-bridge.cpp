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

//  Topology Generated :
//  
//  PC ---- BRIDGE ---- PC
// 

using namespace std;

#include <iostream>
#include <stdlib.h>
#include "../Generator.h"

int main(int argc, char *argv[])
{
  /* avoid compile warnings */
  argc = argc;
  argv = argv;
  
  Generator *gen = new Generator(std::string("example-bridge"));
  
  /* Add Equipement : */
  gen->AddEquipement("Pc");//0
  gen->AddEquipement("Pc");//1
  
  gen->AddEquipement("Bridge");//2
  
  /* Add the bridge. */
  gen->AddLink("Bridge", gen->listEquipement.at(2)->getNodeName());
  /* Add equipement to bridge */
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName());
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  
  /* Add an application */
  gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(), gen->listEquipement.at(1)->getNodeName(), 0, 5);// 0 start time - 5 end time

  gen->GenerateCode();
  
  delete gen;
}