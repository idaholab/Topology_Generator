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
 * \file bridge.cpp
 * \brief Bridge link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "bridge.h"
#include "generator.h"

#include "utils.h"

Bridge::Bridge(const std::string &type, const size_t &indice, const std::string &nodeBridge) : NetworkHardware(type, indice)
{
  this->SetNetworkHardwareName(std::string("bridge_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetNetworkHardwareName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetNetworkHardwareName()));
  this->m_nodeBridge = nodeBridge;
}

Bridge::~Bridge()
{
}

std::string Bridge::GetNodeBridge()
{
  return this->m_nodeBridge;
}

void Bridge::SetNodeBridge(const std::string &nodeBridge)
{
  this->m_nodeBridge = nodeBridge;
}

std::vector<std::string> Bridge::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/csma-module.h\"");

  return headers;
}

std::vector<std::string> Bridge::GenerateNetworkHardwareCpp()
{
  std::vector<std::string> generatedLink;
  /* creation of the link. */
  generatedLink.push_back("CsmaHelper csma_" + this->GetNetworkHardwareName() + ";");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"Delay\",  TimeValue (MilliSeconds (" + this->GetNetworkHardwareDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Bridge::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;
  //ndc.push_back("NetDeviceContainer " + this->GetNdcName() + " = csma_" + this->GetNetworkHardwareName() + ".Install (" + this->GetAllNodeContainer() + ");");

  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }

  ndc.push_back("NetDeviceContainer terminalDevices_" + this->GetNetworkHardwareName() + ";");
  ndc.push_back("NetDeviceContainer BridgeDevices_" + this->GetNetworkHardwareName() + ";");

  ndc.push_back("for (int i = 0; i < " + utils::integerToString(allNodes.size() - 1) + "; i++)");
  ndc.push_back("{");
  ndc.push_back(" NetDeviceContainer link = csma_" + this->GetNetworkHardwareName() + ".Install(NodeContainer(" + this->GetAllNodeContainer() + ".Get(i), " + this->m_nodeBridge + "));");
  ndc.push_back(" terminalDevices_" + this->GetNetworkHardwareName() + ".Add (link.Get(0));");
  ndc.push_back(" BridgeDevices_" + this->GetNetworkHardwareName() + ".Add (link.Get(1));");
  ndc.push_back("}");

  ndc.push_back("BridgeHelper bridge_" + this->GetNetworkHardwareName() + ";");
  ndc.push_back("bridge_" + this->GetNetworkHardwareName() + ".Install (" + this->m_nodeBridge + ".Get(0), BridgeDevices_" + this->GetNetworkHardwareName() + ");");

  ndc.push_back("NetDeviceContainer ndc_" + this->GetNetworkHardwareName() + " = terminalDevices_" + this->GetNetworkHardwareName() + ";"); 

  return ndc;
}

std::vector<std::string> Bridge::GenerateTraceCpp()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    if(this->GetPromisc())
    {
      trace.push_back("csma_" + this->GetNetworkHardwareName() + ".EnablePcapAll (\"csma_" + this->GetNetworkHardwareName() + "\", true);");
    }
    else
    {
      trace.push_back("csma_" + this->GetNetworkHardwareName() + ".EnablePcapAll (\"csma_" + this->GetNetworkHardwareName() + "\", false);");
    }
  }

  return trace;
}

std::vector<std::string> Bridge::GenerateNetworkHardwarePython()
{
  std::vector<std::string> generatedLink;

  /* creation of the link. */
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + " = ns3.CsmaHelper();");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"DataRate\", ns3.DataRateValue (ns3.DataRate(" + this->GetDataRate() + ")))");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"Delay\",  ns3.TimeValue (ns3.MilliSeconds(" + this->GetNetworkHardwareDelay() + ")))");

  return generatedLink;
}

std::vector<std::string> Bridge::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;
  //ndc.push_back("" + this->GetNdcName() + " = csma_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ")");

  std::vector<std::string> allNodes = this->GroupAsNodeContainerPython();
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }

  ndc.push_back("terminalDevices_" + this->GetNetworkHardwareName() + " = ns3.NetDeviceContainer()");
  ndc.push_back("BridgeDevices_" + this->GetNetworkHardwareName() + " = ns3.NetDeviceContainer()");

  ndc.push_back("for i in range(" + utils::integerToString(allNodes.size() - 1) + "):");
  ndc.push_back("    link = csma_" + this->GetNetworkHardwareName() + ".Install(NodeContainer(" + this->GetAllNodeContainer() + ".Get(i), " + this->GetNodeBridge() + "))");
  ndc.push_back("    terminalDevices_" + this->GetNetworkHardwareName() + ".Add(link.Get(0))");
  ndc.push_back("    BridgeDevices_" + this->GetNetworkHardwareName() + ".Add(link.Get(1))");

  ndc.push_back("bridge_" + this->GetNetworkHardwareName() + " = ns3.BridgeHelper");
  ndc.push_back("bridge_" + this->GetNetworkHardwareName() + ".Install(" + this->m_nodeBridge + ".Get(0), BridgeDevices_" + this->GetNetworkHardwareName() + ")");

  ndc.push_back("ndc_" + this->GetNetworkHardwareName() + " = terminalDevices_" + this->GetNetworkHardwareName() + ""); 

  return ndc;
}

std::vector<std::string> Bridge::GenerateTracePython()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    if(this->GetPromisc())
    {
      trace.push_back("csma_" + this->GetNetworkHardwareName() + ".EnablePcapAll(\"csma_" + this->GetNetworkHardwareName() + "\", true)");
    }
    else
    {
      trace.push_back("csma_" + this->GetNetworkHardwareName() + ".EnablePcapAll(\"csma_" + this->GetNetworkHardwareName() + "\", false)");
    }
  }

  return trace;
}
