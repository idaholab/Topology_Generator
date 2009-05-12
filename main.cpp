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


/* this procedure list all Equipement created by the generator and print it. */
void ListAllEquipement(Generator *gen)
{
  for(size_t i = 0; i < (size_t) gen->listEquipement.size(); i++)
  {
    std::cout << "Numéro :" << i << std::endl;
	  std::cout << "nodeName :"<< gen->listEquipement.at(i)->getNodeName() << std::endl;
	  std::cout << "ip :"<< gen->listEquipement.at(i)->getIp() << std::endl;
	  std::cout << "mask :" << gen->listEquipement.at(i)->getMask() << std::endl;
	  std::cout << "ipInterfaceName :" << gen->listEquipement.at(i)->getIpInterfaceName() << std::endl;
	  std::cout << "x :" << gen->listEquipement.at(i)->getX() << std::endl;
	  std::cout << "y :" << gen->listEquipement.at(i)->getY() << std::endl;
	  std::cout << "#################" << std::endl;	
  }	
		
}

void ListAllApplication()
{
}

void ListAllLink()
{
}

void Usage()
{
  std::cout << "0 - exit." << std::endl;
  std::cout << "1 - List all equipements." << std::endl;
  std::cout << "2 - add a PC" << std::endl;
  std::cout << "choose :";
}

int main()
{
  Generator *gen = new Generator();
  
  /* Add Equipement : */
  gen->AddEquipement("Pc");//0
  gen->AddEquipement("Pc");//1
  
  gen->AddEquipement("Bridge");//2
  
  gen->AddEquipement("Router");//3
  
  gen->AddEquipement("Bridge");//4

  gen->AddEquipement("Pc");//5
  gen->AddEquipement("Pc");//6
  
    
  /* Add the bridge. */
  gen->AddLink("Bridge", gen->listEquipement.at(2)->getNodeName());//link 0
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(0)->getNodeName());
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(1)->getNodeName());
  
  gen->AddLink("Bridge", gen->listEquipement.at(4)->getNodeName());//link 1
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(5)->getNodeName());
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(6)->getNodeName());
  
  /* link switch to router. */
  gen->listLink.at(0)->AddNodes(gen->listEquipement.at(3)->getNodeName());
  gen->listLink.at(1)->AddNodes(gen->listEquipement.at(3)->getNodeName());
  
  
  /* Add an application */
  //~ gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(), gen->listEquipement.at(1)->getNodeName(), 0, 5);// 0 start time - 5 end time
  //~ gen->AddApplication("Ping", gen->listEquipement.at(5)->getNodeName(), gen->listEquipement.at(6)->getNodeName(), 0, 5);// 0 start time - 5 end time
  gen->AddApplication("Ping", gen->listEquipement.at(0)->getNodeName(), gen->listEquipement.at(5)->getNodeName(), 0, 5);// 0 start time - 5 end time
  
	/* Generate de application code. */
  gen->GenerateCode();
  
  delete gen;
}

