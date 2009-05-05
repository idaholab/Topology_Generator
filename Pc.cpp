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
/**
* \file Pc.cpp
* \brief Subclasse from Equipement.
* \author Pierre Weiss
* \date 2009
*/

#include "Pc.h"

Pc::Pc() : Equipement()
{
}

Pc::~Pc()
{	
}

std::vector<std::string> Pc::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/helper-module.h\"");
  
  return headers;
}

std::vector<std::string> Pc::GenerateNode()
{
  std::vector<std::string> nodes;
  nodes.push_back("NodeContainer "+this->getNodeName()+";");
  nodes.push_back(this->getNodeName()+".Create(1);");
 
  return nodes;
}

std::vector<std::string> Pc::GenerateIpStack()
{
  std::vector<std::string> stack;
  stack.push_back("InternetStackHelper net_"+this->getNodeName()+";");
  stack.push_back("net_"+this->getNodeName()+".Install ("+this->getNodeName()+");");
  
  return stack; 
}

std::vector<std::string> Pc::GenerateIpAssign()
{ 
  // need to think about the third argument from the SetBase method.
  std::vector<std::string> ipAssign;
  ipAssign.push_back("Ipv4AddressHelper ipv4_"+this->getNodeName()+";");
	ipAssign.push_back("ipv4.SetBase (\""+this->getIp()+"\", \""+this->getMask()+"\", \"0.0.0."+this->getIndice()+"\");");
  ipAssign.push_back("Ipv4InterfaceContainer "+this->getIpInterfaceName()+" = ipv4.Assign(netDeviceCont_"+this->getNodeName()+");");
  
  return ipAssign;
}
 

