/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
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
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

/**
 * \file tap.cpp
 * \brief Tap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "tap.h"

Tap::Tap(const size_t &indice, const std::string &tapNode, const std::string &ifaceName) : Link(indice)
{
  this->Install(tapNode);
  this->m_tapNode = tapNode;
  this->m_ifaceName = ifaceName;
  this->SetLinkName(std::string("tap_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetLinkName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetLinkName()));
}

Tap::~Tap()
{
}

std::vector<std::string> Tap::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->GetNdcName() + " = csma_" + this->GetLinkName() + ".Install (" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Tap::GenerateTapBridgeCpp()
{
  std::vector<std::string> tapBridge;

  tapBridge.push_back("TapBridgeHelper tapBridge_" + this->GetLinkName() + " (iface_" + this->GetNdcName() + ".GetAddress(1));");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".SetAttribute (\"Mode\", StringValue (mode_" + this->GetLinkName() + "));");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".SetAttribute (\"DeviceName\", StringValue (tapName_" + this->GetLinkName() + "));");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".Install (" + this->m_tapNode + ".Get(0), " + this->GetNdcName() + ".Get(0));");

  return tapBridge;
}

std::string Tap::GetTapName()
{
  return this->m_tapNode;
}

void Tap::SetTapName(const std::string &tapNode)
{
  this->m_tapNode = tapNode;
}

std::string Tap::GetIfaceName()
{
  return this->m_ifaceName;
}

void Tap::SetIfaceName(const std::string &ifaceName)
{
  this->m_ifaceName = ifaceName;
}

std::vector<std::string> Tap::GenerateVarsCpp()
{
  std::vector<std::string> vars;
  vars.push_back("std::string mode_" + this->GetLinkName() + " = \"ConfigureLocal\";");
  vars.push_back("std::string tapName_" + this->GetLinkName() + " = \"" + this->m_ifaceName + "\";");
  return vars;
}

std::vector<std::string> Tap::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/helper-module.h\"");

  return headers;
}

std::vector<std::string> Tap::GenerateLinkCpp()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_" + this->GetLinkName() + ";");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds (" + this->GetLinkDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Tap::GenerateCmdLineCpp()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue (\"mode_" + this->GetLinkName() + "\", \"Mode Setting of TapBridge\", mode_" + this->GetLinkName() + ");");
  cmdLine.push_back("cmd.AddValue (\"tapName_" + this->GetLinkName() + "\", \"Name of the OS tap device\", tapName_" + this->GetLinkName() + ");");
  return cmdLine;
}

std::vector<std::string> Tap::GenerateVarsPython()
{
  std::vector<std::string> vars;
  vars.push_back("mode_" + this->GetLinkName() + " = \"ConfigureLocal\"");
  vars.push_back("tapName_" + this->GetLinkName() + " = \"" + this->m_ifaceName + "\"");
  return vars;
}

std::vector<std::string> Tap::GenerateCmdLinePython()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue(\"mode_" + this->GetLinkName() + "\", \"Mode Setting of TapBridge\", mode_" + this->GetLinkName() + ")");
  cmdLine.push_back("cmd.AddValue(\"tapName_" + this->GetLinkName() + "\", \"Name of the OS tap device\", tapName_" + this->GetLinkName() + ")");
  return cmdLine;
}

std::vector<std::string> Tap::GenerateLinkPython()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("csma_" + this->GetLinkName() + " = ns3.CsmaHelper()");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute(\"DataRate\", ns3.DataRateValue(ns3.DataRate(" + this->GetDataRate() + ")));");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute(\"Delay\", ns3.TimeValue(ns3.MilliSeconds(" + this->GetLinkDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Tap::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back(this->GetNdcName() + " = csma_" + this->GetLinkName() + ".Install(" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Tap::GenerateTapBridgePython()
{ 
  std::vector<std::string> tapBridge;
  
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + " = ns3.TapBridgeHelper(iface_" + this->GetNdcName() + ".GetAddress(1))");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".SetAttribute(\"Mode\", ns3.StringValue (mode_" + this->GetLinkName() + "))");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".SetAttribute(\"DeviceName\", ns3.StringValue (tapName_" + this->GetLinkName() + "))");
  tapBridge.push_back("tapBridge_" + this->GetLinkName() + ".Install(" + this->m_tapNode + ".Get(0), " + this->GetNdcName() + ".Get(0))");
  
  return tapBridge;
} 

