/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
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
* \file Tap.cpp
* \brief Tap link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#include "Tap.h"


Tap::Tap(const size_t &_indice, const std::string &_tapNode, const std::string &_ifaceName) : Link(_indice)
{
  this->nodes.push_back(_tapNode);
  this->tapNode = _tapNode;
  this->ifaceName = _ifaceName;
  this->linkName = "tap_"+this->getIndice();
  this->ndcName = "ndc_"+this->getLinkName();
  this->allNodeContainer = "all_"+this->getLinkName();
}

Tap::~Tap()
{
}

std::vector<std::string> Tap::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/helper-module.h\"");
  
  return headers;
}

std::vector<std::string> Tap::GenerateLink()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_"+this->getLinkName()+";");
  generatedLink.push_back("csma_"+this->getLinkName()+".SetChannelAttribute (\"DataRate\", StringValue (\""+this->getDataRate()+"\"));");
  generatedLink.push_back("csma_"+this->getLinkName()+".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds ("+this->getLinkDelay()+")));");
  
  return generatedLink;
}

std::vector<std::string> Tap::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer "+this->getNdcName()+" = csma_"+this->getLinkName()+".Install ("+this->getAllNodeContainer()+");");
  
  return ndc;
}

std::vector<std::string> Tap::GenerateTapBridge()
{
  std::vector<std::string> tapBridge;
  
  tapBridge.push_back("TapBridgeHelper tapBridge_"+this->getLinkName()+" (iface_"+this->getNdcName()+".GetAddress(1));");
  tapBridge.push_back("tapBridge_"+this->getLinkName()+".SetAttribute (\"Mode\", StringValue (mode_"+this->getLinkName()+"));");
  tapBridge.push_back("tapBridge_"+this->getLinkName()+".SetAttribute (\"DeviceName\", StringValue (tapName_"+this->getLinkName()+"));");
  tapBridge.push_back("tapBridge_"+this->getLinkName()+".Install ("+this->getTapName()+".Get(0), "+this->getNdcName()+".Get(0));");
  
  return tapBridge;
}

std::string Tap::getTapName()
{
  return this->tapNode;
}

std::string Tap::getIfaceName()
{
  return this->ifaceName;
}

std::vector<std::string> Tap::GenerateVars()
{
  std::vector<std::string> vars;
  vars.push_back("std::string mode_"+this->getLinkName()+" = \"ConfigureLocal\";");
  vars.push_back("std::string tapName_"+this->getLinkName()+" = \""+this->getIfaceName()+"\";");
  return vars;
}
std::vector<std::string> Tap::GenerateCmdLine()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue(\"mode_"+this->getLinkName()+"\", \"Mode setting of TapBridge\", mode_"+this->getLinkName()+");");
  cmdLine.push_back("cmd.AddValue(\"tapName_"+this->getLinkName()+"\", \"Name of the OS tap device\", tapName_"+this->getLinkName()+");");
  return cmdLine;
}
  

