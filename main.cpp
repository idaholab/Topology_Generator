/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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

using namespace std;

#include "Generator.h"
#include <iostream>
#include <stdlib.h>
#include <limits>

//
// This class is written to test all the implementation of the generator code.
//

int main()
{
  Generator *gen = new Generator("test simulation");
  
   /* Add Equipement : */
  gen->AddEquipement("Pc");//0
  gen->AddEquipement("Pc");//1
  
  gen->AddEquipement("Router");//2
  
  gen->AddEquipement("Pc");//3
  gen->AddEquipement("Pc");//4
  
  gen->AddEquipement("Pc");//5
  
  gen->AddEquipement("Pc");
  gen->listEquipement.at(6)->setNsc("liblinux2.6.26.so");
  
  
  
  /* Add it to a Csma network. */
  gen->AddLink("Hub");//0
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName());
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  
  gen->AddLink("Hub");//1
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(3)->getNodeName());
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(4)->getNodeName());
  
  /* link the two subnetworks to the router. */
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(2)->getNodeName());
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(2)->getNodeName());
  
  gen->AddLink("PointToPoint");//2
  gen->listLink.at(2)->AddNodes(gen->listEquipement.at(4)->getNodeName());
  gen->listLink.at(2)->AddNodes(gen->listEquipement.at(5)->getNodeName());
  
  
  gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(), gen->listEquipement.at(5)->getNodeName(), 0, 5); 
  
	/* Generate de application code. */
  gen->GenerateCode();
  
  delete gen;
}

