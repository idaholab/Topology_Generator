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
 * \file hub.cpp
 * \brief Hub link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "hub.h"

Hub::Hub(const std::string &type, const size_t &indice) : NetworkHardware(type, indice)
{
  this->SetNetworkHardwareName(std::string("hub_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetNetworkHardwareName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetNetworkHardwareName()));
}

Hub::~Hub()
{
}

std::vector<std::string> Hub::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/csma-module.h\"");

  return headers;
}

std::vector<std::string> Hub::GenerateNetworkHardwareCpp()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_" + this->GetNetworkHardwareName() + ";");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"Delay\",  TimeValue (MilliSeconds (" + this->GetNetworkHardwareDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Hub::GenerateNetDeviceCpp()
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

std::vector<std::string> Hub::GenerateTraceCpp()
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

std::vector<std::string> Hub::GenerateNetworkHardwarePython()
{
  std::vector<std::string> ret;
  
  ret.push_back("csma_" + this->GetNetworkHardwareName() + " = ns3.CsmaHelper()");
  ret.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"DataRate\", ns3.DataRateValue(ns3.DataRate(" + this->GetDataRate() + ")))");
  ret.push_back("csma_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"Delay\",  ns3.TimeValue(ns3.MilliSeconds(" + this->GetNetworkHardwareDelay() + ")))");
  return ret;
}

std::vector<std::string> Hub::GenerateNetDevicePython()
{
  std::vector<std::string> ret;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerPython();
  
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ret.push_back(allNodes.at(i));
  }
  ret.push_back(this->GetNdcName() + " = csma_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ")");

  return ret;
}

std::vector<std::string> Hub::GenerateTracePython()
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
