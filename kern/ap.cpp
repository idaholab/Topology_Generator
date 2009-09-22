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
 * \file ap.cpp
 * \brief Ap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "ap.h"

Ap::Ap(const size_t &indice, const std::string &apNode) : Link(indice)
{
  this->Install(apNode);
  this->SetLinkName(std::string("ap_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetLinkName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetLinkName()));
  this->SetApNode(apNode);
  this->SetMobility(false);
  this->SetApName(std::string("wifi-default-" + this->GetIndice()));
}

Ap::~Ap()
{
}

std::string Ap::GetApNode()
{
  return this->m_apNode;
}

void Ap::SetApNode(const std::string &apNode)
{
  this->m_apNode = apNode;
}

void Ap::SetMobility(const bool &mobility)
{
  this->m_mobility = mobility;
}

bool Ap::GetMobility()
{
  return this->m_mobility;
}

void Ap::SetApName(const std::string &apName)
{
  this->m_apName = apName;
}

std::string Ap::GetApName()
{
  return this->m_apName;
}

std::vector<std::string> Ap::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/wifi-module.h\"");
  headers.push_back("#include \"ns3/mobility-module.h\"");
  headers.push_back("#include \"ns3/contrib-module.h\"");

  return headers;
}

std::vector<std::string> Ap::GenerateLinkCpp()
{
  std::vector<std::string> generatedLink;
  /* creation of the link. */
  generatedLink.push_back("YansWifiPhyHelper wifiPhy_" + this->GetLinkName() + " = YansWifiPhyHelper::Default ();");
  generatedLink.push_back("YansWifiChannelHelper wifiChannel_" + this->GetLinkName() + " = YansWifiChannelHelper::Default ();");
  generatedLink.push_back("wifiPhy_" + this->GetLinkName() + ".SetChannel (wifiChannel_" + this->GetLinkName() + ".Create ());");

  return generatedLink;
}

std::vector<std::string> Ap::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;

  std::vector<std::string> allNodes = this->GroupAsNodeContainer();//all station nodes !
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->GetNdcName() + ";");
  ndc.push_back("Ssid ssid_" + this->GetLinkName() + " = Ssid (\"" + this->GetApName() + "\");");
  ndc.push_back("WifiHelper wifi_" + this->GetLinkName() + " = WifiHelper::Default ();");
  ndc.push_back("NqosWifiMacHelper wifiMac_" + this->GetLinkName() + " = NqosWifiMacHelper::Default ();");
  ndc.push_back("wifi_" + this->GetLinkName() + ".SetRemoteStationManager (\"ns3::ArfWifiManager\");");

  ndc.push_back("wifiMac_" + this->GetLinkName() + ".SetType (\"ns3::NqapWifiMac\", ");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_" + this->GetLinkName() + "), ");
  ndc.push_back("   \"BeaconGeneration\", BooleanValue (true),"); 
  ndc.push_back("   \"BeaconInterval\", TimeValue (Seconds (2.5)));");
  ndc.push_back(this->GetNdcName() + ".Add(wifi_" + this->GetLinkName() + ".Install (wifiPhy_" + this->GetLinkName() + ", wifiMac_" + this->GetLinkName() + ", " + this->GetApNode() + "));");

  ndc.push_back("wifiMac_" + this->GetLinkName() + ".SetType (\"ns3::NqstaWifiMac\",");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_" + this->GetLinkName() + "), ");
  ndc.push_back("   \"ActiveProbing\", BooleanValue (false));");
  ndc.push_back(this->GetNdcName() + ".Add (wifi_" + this->GetLinkName() + ".Install (wifiPhy_" + this->GetLinkName() + ", wifiMac_" + this->GetLinkName() + ", " + this->GetAllNodeContainer() + " ));");

  ndc.push_back("MobilityHelper mobility_" + this->GetLinkName() + ";");
  ndc.push_back("mobility_" + this->GetLinkName() + ".SetMobilityModel (\"ns3::ConstantPositionMobilityModel\");");
  ndc.push_back("mobility_" + this->GetLinkName() + ".Install(" + this->GetApNode() + ");"); 

  if(this->GetMobility())//if random walk is activated.
  {
    ndc.push_back("mobility_" + this->GetLinkName() + ".SetMobilityModel (\"ns3::RandomWalk2dMobilityModel\",\"Bounds\", RectangleValue (Rectangle (-50, 50, -50, 50)));");
  }
  ndc.push_back("mobility_" + this->GetLinkName() + ".Install(" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Ap::GenerateTraceCpp()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    trace.push_back("wifiPhy_" + this->GetLinkName() + ".EnablePcap (\"" + this->GetLinkName() + "\", " + this->GetNdcName() + ".Get(0));");
  }

  return trace;
}  

std::vector<std::string> Ap::GenerateLinkPython()
{
  std::vector<std::string> generatedLink;
  return generatedLink;
}

std::vector<std::string> Ap::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;
  return ndc;
}

std::vector<std::string> Ap::GenerateTracePython()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    trace.push_back("wifiPhy_" + this->GetLinkName() + ".EnablePcap (\"" + this->GetLinkName() + "\", " + this->GetNdcName() + ".Get(0));");
  }

  return trace;
}

