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
#include <stdexcept>

Generator *gen;

//
// This class is written to test all the implementation of the generator code.
//

void ConnectNode(const size_t &linkNumber, const std::string &nodeName)
{
  size_t numberOfConnectedMachines = 0;
  
  /* get the number of machines to add */
  if(nodeName.find("Get") == 0)
  {
    numberOfConnectedMachines += 1;
  }
  else
  {
    for(size_t i = 0; i < (size_t) gen->listEquipement.size(); i++)
    {
      if(nodeName.compare(gen->listEquipement.at(i)->getNodeName()) == 0)
      {
        numberOfConnectedMachines += gen->listEquipement.at(i)->getMachinesNumber();
      }
    }
  }
  
  /* get the number of machines also connected. */
  std::vector<std::string> nodes = gen->listLink.at(linkNumber)->getNodes();
  for(size_t i = 0; i < (size_t) nodes.size(); i++)
  {
    for(size_t j = 0; j < (size_t) gen->listEquipement.size(); j++)
    {
      if(nodes.at(i).compare(gen->listEquipement.at(j)->getNodeName()) == 0)
      {
        numberOfConnectedMachines += gen->listEquipement.at(j)->getMachinesNumber();
      }
    }
  }
  if( numberOfConnectedMachines > (255 -2) )
  {
    throw std::logic_error("Limit of machines exceeded.\n");
  }
  gen->listLink.at(linkNumber)->AddNodes(nodeName);
}

int main()
{
  gen = new Generator(std::string("Simulation-Name"));
  
  int group = 2;
  // Equipement which are possible to create.
  gen->AddEquipement(group);
  gen->AddEquipement("Pc");
  
  //~  Add it to a Csma network.
  gen->AddLink(std::string("Hub"));
  ConnectNode(0, std::string(gen->listEquipement.at(0)->getNodeName()));
  ConnectNode(0, std::string(gen->listEquipement.at(1)->getNodeName()));
  
  gen->AddApplication(std::string("Ping"), std::string(gen->listEquipement.at(0)->getNodeName(0)), std::string(gen->listEquipement.at(0)->getNodeName(8)), 1, 10);
  
	//Generate de application code. 
  gen->GenerateCode();
  
  
  delete gen;
}

