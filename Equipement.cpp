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


#include "Equipement.h"
#include "Generator.h"

#include <sstream>

Equipement::Equipement(){
  this->indice = toString(Generator::getIndiceEquipement());
  this->nodeName = "node_"+toString(Generator::getIndiceEquipement());
  this->ip = "0.0.0.0";
  this->mask = "255.255.255.0";
  this->ipInterfaceName = "iface_"+this->nodeName;
  this->x = 0;
  this->y = 0;	
}

//no pointer nothing to destroy
Equipement::~Equipement(){
}

string Equipement::toString(int nbr){
  std::ostringstream out;
  out << nbr;
return out.str();
}

void Equipement::setNodeName(string _nodeName){
  this->nodeName = _nodeName;
}

void Equipement::setIpv4Address(string _ip, string _mask){
  this->ip = _ip;
  this->mask = _mask;
}

void Equipement::setIpInterfaceName(string _ipInterfaceName){
  this->ipInterfaceName = _ipInterfaceName;
}

string Equipement::getNodeName(){
  return this->nodeName;
}

string Equipement::getIpInterfaceName(){
  return this->ipInterfaceName;
}
 
string Equipement::getHeader(){
  return this->header;
}

void Equipement::setPosition(int _x, int _y){
  this->x = _x;
  this->y = _y;
}

string Equipement::getIp(){
  return this->ip;
}

string Equipement::getMask(){
  return this->mask;
}

string Equipement::getX(){
  return toString(this->x);
}

string Equipement::getY(){
  return toString(this->y);
}

string Equipement::getIndice(){
  return this->indice;
}
