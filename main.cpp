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

#include "core/Generator.h"
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
  
  /* Add Equipement : */
  gen->AddEquipement(9);//note that the central node of the star is number 0.
  
  /* Add the bridge. */
  gen->AddLink("Hub");
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName(1));
  
  gen->AddLink("Hub");
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(0)->getNodeName(2));
  
  gen->AddLink("Hub");
  gen->listLink.at(2)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(2)->AddNodes(gen->listEquipement.at(0)->getNodeName(3));
  
  gen->AddLink("Hub");
  gen->listLink.at(3)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(3)->AddNodes(gen->listEquipement.at(0)->getNodeName(4));
  
  gen->AddLink("Hub");
  gen->listLink.at(4)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(4)->AddNodes(gen->listEquipement.at(0)->getNodeName(5));
  
  gen->AddLink("Hub");
  gen->listLink.at(5)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(5)->AddNodes(gen->listEquipement.at(0)->getNodeName(6));
  
  gen->AddLink("Hub");
  gen->listLink.at(6)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(6)->AddNodes(gen->listEquipement.at(0)->getNodeName(7));
  
  gen->AddLink("Hub");
  gen->listLink.at(7)->AddNodes(gen->listEquipement.at(0)->getNodeName(0));
  gen->listLink.at(7)->AddNodes(gen->listEquipement.at(0)->getNodeName(8));
  
  
  /* Add an application */
  gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(1), gen->listEquipement.at(0)->getNodeName(5), 0, 5);// 0 start time - 5 end time

	//Generate de application code. 
  gen->GenerateCode();
  
  
  delete gen;
}

