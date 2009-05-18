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
* \file Bridge.cpp
* \brief Bridge link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#include "Bridge.h"
#include "Generator.h"


Bridge::Bridge(const size_t &_indice, const std::string &_nodeBridge) : Link(_indice)
{
  this->linkName = "bridge_"+this->getIndice();
  this->ndcName = "ndc_"+this->getLinkName();
  this->allNodeContainer = "all_"+this->getLinkName();
  this->nodeBridge = _nodeBridge;
}

Bridge::~Bridge()
{
}
std::string Bridge::getNodeBridge()
{
  return this->nodeBridge;
}

std::vector<std::string> Bridge::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  
  return headers;
}

std::vector<std::string> Bridge::GenerateLink()
{
  std::vector<std::string> generatedLink;
  /* creation of the link. */
  generatedLink.push_back("CsmaHelper csma_"+this->getLinkName()+";");
  generatedLink.push_back("csma_"+this->getLinkName()+".SetChannelAttribute (\"DataRate\", StringValue (\""+this->getDataRate()+"\"));");
  generatedLink.push_back("csma_"+this->getLinkName()+".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds ("+this->getLinkDelay()+")));");
  
  return generatedLink;
}

std::vector<std::string> Bridge::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  //ndc.push_back("NetDeviceContainer "+this->getNdcName()+" = csma_"+this->getLinkName()+".Install ("+this->getAllNodeContainer()+");");
  
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  
  ndc.push_back("NetDeviceContainer terminalDevices_"+this->getLinkName()+";");
  ndc.push_back("NetDeviceContainer BridgeDevices_"+this->getLinkName()+";");

  ndc.push_back("for (int i = 0; i < "+Generator::toString(allNodes.size()-1)+"; i++)");
  ndc.push_back("{");
  ndc.push_back(" NetDeviceContainer link = csma_"+this->getLinkName()+".Install(NodeContainer("+this->getAllNodeContainer()+".Get(i), "+this->getNodeBridge()+"));");
  ndc.push_back(" terminalDevices_"+this->getLinkName()+".Add (link.Get(0));");
  ndc.push_back(" BridgeDevices_"+this->getLinkName()+".Add (link.Get(1));");
  ndc.push_back("}");
 
  ndc.push_back("BridgeHelper bridge_"+this->getLinkName()+";");
  ndc.push_back("bridge_"+this->getLinkName()+".Install ("+this->getNodeBridge()+".Get(0), BridgeDevices_"+this->getLinkName()+");");
  
  ndc.push_back("NetDeviceContainer ndc_"+this->getLinkName()+" = terminalDevices_"+this->getLinkName()+";"); 
  
  return ndc;
}


