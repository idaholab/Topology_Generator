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

#include "Pc.h"

Pc::Pc() : Equipement(){
  this->header = "#include \"ns3/node-module.h\"\n";
}

Pc::~Pc(){	
}

string Pc::GenerateHeader(){
  return this->header;
}

string Pc::GenerateNode(){
  return "NodeContainer "+this->getNodeName()+"\n"
         +this->getNodeName()+".Create(1);\n";
}

string Pc::GenerateIpStack(){
  return "InternetStackHelper net_"+this->getNodeName()+"; \n"
  	     +"net_"+this->getNodeName()+".Install ("+this->getNodeName()+");\n";
}

string Pc::GenerateIpAssign(){ 
  // need to think about the third argument from the SetBase method.	
	
  return "Ipv4AddressHelper ipv4_"+this->getNodeName()+";\n"
  		 +"ipv4.SetBase (\""+this->getIp()+"\", \""+this->getMask()+"\", \"0.0.0."+this->getIndice()+"\");"
  		 +"Ipv4InterfaceContainer "+this->getIpInterfaceName()+" = ipv4.Assign(netDeviceCont_"+this->getNodeName()+");\n";
}
 
void Pc::setHeader(string _header){
  this->header = _header;
}

