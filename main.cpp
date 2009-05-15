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
  
  int machines = 15;

  gen->AddEquipement(machines);//0
  gen->AddEquipement("Pc");
  
  
  /* Add it to a Csma network. */
  gen->AddLink("Hub");//0
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName());
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  
  gen->AddApplication("Ping", gen->listEquipement.at(1)->getNodeName(), gen->listEquipement.at(0)->getNodeName(5), 0, 5);
  gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(0), gen->listEquipement.at(1)->getNodeName(), 0, 5); 
  
	/* Generate de application code. */
  gen->GenerateCode();
  
  delete gen;
}

