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

/*
 * © 2015 Battelle Energy Alliance, LLC. ALL RIGHTS RESERVED
 *
 * Prepared by Battelle Energy Alliance, LLC.
 * Under Contract No. DE-AC07-05ID14517
 * With the U. S. Department of Energy
 *
 * NOTICE:  This computer software was prepared by Battelle Energy
 * Alliance, LLC, hereinafter the Contractor, under Contract
 * No. AC07-05ID14517 with the United States (U. S.) Department of
 * Energy (DOE).  The Government is granted for itself and others acting on
 * its behalf a nonexclusive, paid-up, irrevocable worldwide license in this
 * data to reproduce, prepare derivative works, and perform publicly and
 * display publicly, by or on behalf of the Government. There is provision for
 * the possible extension of the term of this license.  Subsequent to that
 * period or any extension granted, the Government is granted for itself and
 * others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide
 * license in this data to reproduce, prepare derivative works, distribute
 * copies to the public, perform publicly and display publicly, and to permit
 * others to do so.  The specific term of the license can be identified by
 * inquiry made to Contractor or DOE.  NEITHER THE UNITED STATES NOR THE UNITED
 * STATES DEPARTMENT OF ENERGY, NOR CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR
 * IMPLIED, OR ASSUMES ANY LIABILITY OR RESPONSIBILITY FOR THE USE, ACCURACY,
 * COMPLETENESS, OR USEFULNESS OR ANY INFORMATION, APPARATUS, PRODUCT, OR
 * PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY
 * OWNED RIGHTS.
 * 
 * Modified by: Jeffrey M. Young <jeffrey.young@inl.gov>
 */

/**
 * \file tap.cpp
 * \brief Tap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "tap.h"

Tap::Tap(const std::string &type, const size_t &indice, const std::string &tapNode, const std::string &ifaceName) : NetworkHardware(type, indice)
{
  this->Install(tapNode);
  this->m_tapNode = tapNode;
  this->m_ifaceName = ifaceName;
  this->SetNetworkHardwareName(std::string("tap_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetNetworkHardwareName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetNetworkHardwareName()));
}

Tap::~Tap()
{
}

std::vector<std::string> Tap::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->GetNdcName() + " = csma_" + this->GetNetworkHardwareName() + ".Install (" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Tap::GenerateTapBridgeCpp()
{
  std::vector<std::string> tapBridge;

  tapBridge.push_back("TapBridgeHelper tapBridge_" + this->GetNetworkHardwareName() + " (iface_" + this->GetNdcName() + ".GetAddress(1));");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".SetAttribute (\"Mode\", StringValue (mode_" + this->GetNetworkHardwareName() + "));");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".SetAttribute (\"DeviceName\", StringValue (tapName_" + this->GetNetworkHardwareName() + "));");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".Install (" + this->m_tapNode + ".Get(0), " + this->GetNdcName() + ".Get(0));");

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
  vars.push_back("std::string mode_" + this->GetNetworkHardwareName() + " = \"ConfigureLocal\";");
  vars.push_back("std::string tapName_" + this->GetNetworkHardwareName() + " = \"" + this->m_ifaceName + "\";");
  return vars;
}

std::vector<std::string> Tap::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/csma-module.h\"");
  headers.push_back("#include \"ns3/tap-bridge-module.h\"");

  return headers;
}

std::vector<std::string> Tap::GenerateNetworkHardwareCpp()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_" + this->GetNetworkHardwareName() + ";");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds (" + this->GetNetworkHardwareDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Tap::GenerateCmdLineCpp()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue (\"mode_" + this->GetNetworkHardwareName() + "\", \"Mode Setting of TapBridge\", mode_" + this->GetNetworkHardwareName() + ");");
  cmdLine.push_back("cmd.AddValue (\"tapName_" + this->GetNetworkHardwareName() + "\", \"Name of the OS tap device\", tapName_" + this->GetNetworkHardwareName() + ");");
  return cmdLine;
}

std::vector<std::string> Tap::GenerateVarsPython()
{
  std::vector<std::string> vars;
  vars.push_back("mode_" + this->GetNetworkHardwareName() + " = \"ConfigureLocal\"");
  vars.push_back("tapName_" + this->GetNetworkHardwareName() + " = \"" + this->m_ifaceName + "\"");
  return vars;
}

std::vector<std::string> Tap::GenerateCmdLinePython()
{
  std::vector<std::string> cmdLine;
  cmdLine.push_back("cmd.AddValue(\"mode_" + this->GetNetworkHardwareName() + "\", \"Mode Setting of TapBridge\", mode_" + this->GetNetworkHardwareName() + ")");
  cmdLine.push_back("cmd.AddValue(\"tapName_" + this->GetNetworkHardwareName() + "\", \"Name of the OS tap device\", tapName_" + this->GetNetworkHardwareName() + ")");
  return cmdLine;
}

std::vector<std::string> Tap::GenerateNetworkHardwarePython()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + " = ns3.CsmaHelper()");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"DataRate\", ns3.DataRateValue(ns3.DataRate(" + this->GetDataRate() + ")));");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"Delay\", ns3.TimeValue(ns3.MilliSeconds(" + this->GetNetworkHardwareDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Tap::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back(this->GetNdcName() + " = csma_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Tap::GenerateTapBridgePython()
{ 
  std::vector<std::string> tapBridge;
  
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + " = ns3.TapBridgeHelper(iface_" + this->GetNdcName() + ".GetAddress(1))");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".SetAttribute(\"Mode\", ns3.StringValue (mode_" + this->GetNetworkHardwareName() + "))");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".SetAttribute(\"DeviceName\", ns3.StringValue (tapName_" + this->GetNetworkHardwareName() + "))");
  tapBridge.push_back("tapBridge_" + this->GetNetworkHardwareName() + ".Install(" + this->m_tapNode + ".Get(0), " + this->GetNdcName() + ".Get(0))");
  
  return tapBridge;
} 
