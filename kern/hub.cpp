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

Hub::Hub(const size_t &indice) : Link(indice)
{
  this->SetLinkName(std::string("hub_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetLinkName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetLinkName()));
}

Hub::~Hub()
{
}

std::vector<std::string> Hub::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");

  return headers;
}

std::vector<std::string> Hub::GenerateLinkCpp()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_" + this->GetLinkName() + ";");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute (\"DataRate\", DataRateValue (" + this->GetDataRate() + "));");
  generatedLink.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute (\"Delay\",  TimeValue (MilliSeconds (" + this->GetLinkDelay() + ")));");

  return generatedLink;
}

std::vector<std::string> Hub::GenerateNetDeviceCpp()
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

std::vector<std::string> Hub::GenerateTraceCpp()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    if(this->GetPromisc())
    {
      trace.push_back("csma_" + this->GetLinkName() + ".EnablePcapAll (\"csma_" + this->GetLinkName() + "\", true);");
    }
    else
    {
      trace.push_back("csma_" + this->GetLinkName() + ".EnablePcapAll (\"csma_" + this->GetLinkName() + "\", false);");
    }
  }

  return trace;
}

std::vector<std::string> Hub::GenerateLinkPython()
{
  std::vector<std::string> ret;
  
  ret.push_back("csma_" + this->GetLinkName() + " = ns3.CsmaHelper()");
  ret.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute(\"DataRate\", ns3.DataRateValue(ns3.DataRate(" + this->GetDataRate() + ")))");
  ret.push_back("csma_" + this->GetLinkName() + ".SetChannelAttribute(\"Delay\",  ns3.TimeValue(ns3.MilliSeconds(" + this->GetLinkDelay() + ")))");
  return ret;
}

std::vector<std::string> Hub::GenerateNetDevicePython()
{
  std::vector<std::string> ret;
  std::vector<std::string> allNodes = this->GroupAsNodeContainerPython();
  
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ret.push_back(allNodes.at(i));
  }
  ret.push_back(this->GetNdcName() + " = csma_" + this->GetLinkName() + ".Install(" + this->GetAllNodeContainer() + ")");

  return ret;
}

std::vector<std::string> Hub::GenerateTracePython()
{
  std::vector<std::string> trace;
  
  if(this->GetTrace())
  {
    if(this->GetPromisc())
    {
      trace.push_back("csma_" + this->GetLinkName() + ".EnablePcapAll(\"csma_" + this->GetLinkName() + "\", true)");
    }
    else
    {
      trace.push_back("csma_" + this->GetLinkName() + ".EnablePcapAll(\"csma_" + this->GetLinkName() + "\", false)");
    }
  }
  return trace;
}

