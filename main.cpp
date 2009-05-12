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
  Generator *gen = new Generator();
  
  /* Add Equipement : */
  gen->AddEquipement("Pc");//0
  gen->AddEquipement("Router");//1
  gen->AddEquipement("Ap");//2
  gen->AddEquipement("Station");//3
  
  gen->AddLink("Hub", "");//0
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName());
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  
  gen->AddLink("Wifi", gen->listEquipement.at(2)->getNodeName());//1
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(3)->getNodeName());
  
  
  /* Add an application */
  gen->AddApplication("TcpLargeTransfer", gen->listEquipement.at(0)->getNodeName(), gen->listEquipement.at(3)->getNodeName(), 0, 5, 6666);// 0 start time - 5 end time
  
	/* Generate de application code. */
  gen->GenerateCode();
  
  delete gen;
}

