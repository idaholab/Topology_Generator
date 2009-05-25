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
* \file Emu.cpp
* \brief Emu link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#include "Emu.h"


Emu::Emu(const size_t &_indice, const std::string &_emuNode, const std::string &_ifaceName) : Link(_indice)
{
  this->nodes.push_back(_emuNode);
  this->emuNode = _emuNode;
  this->ifaceName = _ifaceName;
  this->linkName = "emu_"+this->getIndice();
  this->ndcName = "ndc_"+this->getLinkName();
  this->allNodeContainer = "all_"+this->getLinkName();
}

Emu::~Emu()
{
}

std::vector<std::string> Emu::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/emu-helper.h\"");
  
  return headers;
}

std::vector<std::string> Emu::GenerateLink()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("EmuHelper "+this->getLinkName()+";");
  generatedLink.push_back(this->getLinkName()+".SetAttribute (\"DeviceName\", StringValue (emuDevice_"+this->getLinkName()+"));");
  
  return generatedLink;
}

std::vector<std::string> Emu::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer "+this->getNdcName()+" = "+this->getLinkName()+".Install ("+this->getAllNodeContainer()+");");
  
  return ndc;
}

std::string Emu::getEmuName()
{
  return this->emuNode;
}

std::string Emu::getIfaceName()
{
  return this->ifaceName;
}

std::vector<std::string> Emu::GenerateVars()
{
  std::vector<std::string> vars;
  vars.push_back("std::string emuDevice_"+this->getLinkName()+" = \""+this->getIfaceName()+"\";");
  return vars;
}
std::vector<std::string> Emu::GenerateCmdLine()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue(\"deviceName_"+this->getLinkName()+"\", \"device name\", emuDevice_"+this->getLinkName()+");");
  return cmdLine;
}
  

