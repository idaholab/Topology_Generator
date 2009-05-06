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
* \file Equipement.cpp
* \brief Abstract Equipement Base Class.
* \author Pierre Weiss
* \date 2009
*/

#include "Equipement.h"
#include <sstream>

Equipement::Equipement(size_t _indice, std::string _type)
{
  this->indice = _indice;
  this->nodeName = _type + this->toString(_indice);
  this->ip = "0.0.0.0";
  this->mask = "0.0.0.0";
  this->ipInterfaceName = "iface_"+this->nodeName;
  this->x = 0;
  this->y = 0;	
}

//no pointer, nothing to destroy
Equipement::~Equipement()
{
}

std::vector<std::string> Equipement::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/helper-module.h\"");

  return headers; 
}

std::vector<std::string> Equipement::GenerateNode()
{
  std::vector<std::string> nodes;
  nodes.push_back("NodeContainer "+this->getNodeName()+";");
  nodes.push_back(this->getNodeName()+".Create(1);");

  return nodes; 
}

std::vector<std::string> Equipement::GenerateIpStack()
{
  std::vector<std::string> stack;
  stack.push_back("InternetStackHelper net_"+this->getNodeName()+";");
  stack.push_back("net_"+this->getNodeName()+".Install ("+this->getNodeName()+");");

  return stack; 
}
  
std::vector<std::string> Equipement::GenerateIpAssign()
{
  // need to think about the third argument from the SetBase method.
  std::vector<std::string> ipAssign;
  ipAssign.push_back("Ipv4AddressHelper ipv4_"+this->getNodeName()+";");
  ipAssign.push_back("ipv4.SetBase (\""+this->getIp()+"\", \""+this->getMask()+"\", \"0.0.0."+this->getIndice()+"\");");
  
  // Ipv4InterfaceContainer have to be used with an application.
  //ipAssign.push_back("Ipv4InterfaceContainer "+this->getIpInterfaceName()+" = ipv4.Assign(netDeviceCont_"+this->getNodeName()+");");
  ipAssign.push_back("ipv4.Assign(\"hum ???\");");

  return ipAssign; 
}

std::string Equipement::toString(size_t nbr)
{
  std::ostringstream out;
  out << nbr;
  
  return out.str();
}

void Equipement::setNodeName(std::string _nodeName)
{
  this->nodeName = _nodeName;
}

void Equipement::setIpv4Address(std::string _ip, std::string _mask)
{
  this->ip = _ip;
  this->mask = _mask;
}

void Equipement::setIpInterfaceName(std::string _ipInterfaceName)
{
  this->ipInterfaceName = _ipInterfaceName;
}

std::string Equipement::getNodeName()
{
  return this->nodeName;
}

std::string Equipement::getIpInterfaceName()
{
  return this->ipInterfaceName;
}
 
void Equipement::setPosition(size_t _x, size_t _y)
{
  this->x = _x;
  this->y = _y;
}

std::string Equipement::getIp()
{
  return this->ip;
}

std::string Equipement::getMask()
{
  return this->mask;
}

std::string Equipement::getX()
{
  return toString(this->x);
}

std::string Equipement::getY()
{
  return toString(this->y);
}

std::string Equipement::getIndice()
{
  return toString(this->indice);
}





