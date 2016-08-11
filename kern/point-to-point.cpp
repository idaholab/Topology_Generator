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
 * \file point-to-point.cpp
 * \brief Point-to-point link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "point-to-point.h"

PointToPoint::PointToPoint(const std::string &type, const size_t &indice) : NetworkHardware(type, indice)
{
  this->SetNetworkHardwareName(std::string("p2p_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetNetworkHardwareName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetNetworkHardwareName()));
}

PointToPoint::~PointToPoint()
{
}

std::vector<std::string> PointToPoint::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");
  headers.push_back("#include \"ns3/point-to-point-module.h\"");

  return headers;
}

std::vector<std::string> PointToPoint::GenerateNetworkHardwareCpp()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("PointToPointHelper p2p_" + this->GetNetworkHardwareName() + ";");
  generatedLink.push_back("p2p_" + this->GetNetworkHardwareName() + ".SetDeviceAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("p2p_" + this->GetNetworkHardwareName() + ".SetChannelAttribute (\"Delay\", TimeValue (MilliSeconds (" + this->GetNetworkHardwareDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> PointToPoint::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp();
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->GetNdcName() + " = p2p_" + this->GetNetworkHardwareName() + ".Install (" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> PointToPoint::GenerateTraceCpp()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    trace.push_back("PointToPointHelper::EnablePcapAll (\"" + this->GetNetworkHardwareName() + "\");");
  }

  return trace;
}

std::vector<std::string> PointToPoint::GenerateNetworkHardwarePython()
{
  std::vector<std::string> generatedLink;
  
  generatedLink.push_back("p2p_" + this->GetNetworkHardwareName() + " = ns3.PointToPointHelper()");
  generatedLink.push_back("p2p_" + this->GetNetworkHardwareName() + ".SetDeviceAttribute(\"DataRate\", ns3.DataRateValue(ns3.DataRate(" + this->GetDataRate() + ")))");
  generatedLink.push_back("p2p_" + this->GetNetworkHardwareName() + ".SetChannelAttribute(\"Delay\", ns3.TimeValue(ns3.MilliSeconds(" + this->GetNetworkHardwareDelay() + ")))");
  return generatedLink;
}

std::vector<std::string> PointToPoint::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerPython();
  
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  
  ndc.push_back(this->GetNdcName() + " = p2p_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ")");

  return ndc;
}

std::vector<std::string> PointToPoint::GenerateTracePython()
{
  std::vector<std::string> trace;
  
  if(this->GetTrace())
  {
    trace.push_back("PointToPointHelper.EnablePcapAll(\"" + this->GetNetworkHardwareName() + "\")");
  }
  
  return trace;
}
