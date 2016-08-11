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

Ap::Ap(const std::string &type, const size_t &indice, const std::string &apNode) : NetworkHardware(type, indice)
{
  this->Install(apNode);
  this->SetNetworkHardwareName(std::string("ap_" + this->GetIndice()));
  this->SetNdcName(std::string("ndc_" + this->GetNetworkHardwareName()));
  this->SetAllNodeContainer(std::string("all_" + this->GetNetworkHardwareName()));
  this->m_apNode = apNode;
  this->m_mobility = false;
  this->m_apName = std::string("wifi-default-" + this->GetIndice());
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

  return headers;
}

std::vector<std::string> Ap::GenerateNetworkHardwareCpp()
{
  std::vector<std::string> generatedLink;
  /* creation of the link. */
  generatedLink.push_back("YansWifiPhyHelper wifiPhy_" + this->GetNetworkHardwareName() + " = YansWifiPhyHelper::Default ();");
  generatedLink.push_back("YansWifiChannelHelper wifiChannel_" + this->GetNetworkHardwareName() + " = YansWifiChannelHelper::Default ();");
  generatedLink.push_back("wifiPhy_" + this->GetNetworkHardwareName() + ".SetChannel (wifiChannel_" + this->GetNetworkHardwareName() + ".Create ());");

  return generatedLink;
}

std::vector<std::string> Ap::GenerateNetDeviceCpp()
{
  std::vector<std::string> ndc;

  std::vector<std::string> allNodes = this->GroupAsNodeContainerCpp(); //all station nodes !
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->GetNdcName() + ";");
  ndc.push_back("Ssid ssid_" + this->GetNetworkHardwareName() + " = Ssid (\"" + this->m_apName + "\");");
  ndc.push_back("WifiHelper wifi_" + this->GetNetworkHardwareName() + " = WifiHelper::Default ();");
  ndc.push_back("NqosWifiMacHelper wifiMac_" + this->GetNetworkHardwareName() + " = NqosWifiMacHelper::Default ();");
  ndc.push_back("wifi_" + this->GetNetworkHardwareName() + ".SetRemoteStationManager (\"ns3::ArfWifiManager\");");

  ndc.push_back("wifiMac_" + this->GetNetworkHardwareName() + ".SetType (\"ns3::ApWifiMac\", ");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_" + this->GetNetworkHardwareName() + "), ");
  ndc.push_back("   \"BeaconGeneration\", BooleanValue (true),"); 
  ndc.push_back("   \"BeaconInterval\", TimeValue (Seconds (2.5)));");
  ndc.push_back(this->GetNdcName() + ".Add (wifi_" + this->GetNetworkHardwareName() + ".Install (wifiPhy_" + this->GetNetworkHardwareName() + ", wifiMac_" + this->GetNetworkHardwareName() + ", " + this->m_apNode + "));");

  ndc.push_back("wifiMac_" + this->GetNetworkHardwareName() + ".SetType (\"ns3::StaWifiMac\",");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_" + this->GetNetworkHardwareName() + "), ");
  ndc.push_back("   \"ActiveProbing\", BooleanValue (false));");
  ndc.push_back(this->GetNdcName() + ".Add (wifi_" + this->GetNetworkHardwareName() + ".Install (wifiPhy_" + this->GetNetworkHardwareName() + ", wifiMac_" + this->GetNetworkHardwareName() + ", " + this->GetAllNodeContainer() + " ));");

  ndc.push_back("MobilityHelper mobility_" + this->GetNetworkHardwareName() + ";");
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".SetMobilityModel (\"ns3::ConstantPositionMobilityModel\");");
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".Install (" + this->m_apNode + ");"); 

  if(this->m_mobility)//if random walk is activated.
  {
    ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".SetMobilityModel (\"ns3::RandomWalk2dMobilityModel\",\"Bounds\", RectangleValue (Rectangle (-50, 50, -50, 50)));");
  }
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Ap::GenerateTraceCpp()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    trace.push_back("wifiPhy_" + this->GetNetworkHardwareName() + ".EnablePcap (\"" + this->GetNetworkHardwareName() + "\", " + this->GetNdcName() + ".Get(0));");
  }

  return trace;
}  

std::vector<std::string> Ap::GenerateNetworkHardwarePython()
{
  std::vector<std::string> generatedLink;

  /* creation of the link. */
  generatedLink.push_back("wifiPhy_" + this->GetNetworkHardwareName() + " = ns3.YansWifiPhyHelper.Default()");
  generatedLink.push_back("wifiChannel_" + this->GetNetworkHardwareName() + " = ns3.YansWifiChannelHelper.Default()");
  generatedLink.push_back("wifiPhy_" + this->GetNetworkHardwareName() + ".SetChannel(wifiChannel_" + this->GetNetworkHardwareName() + ".Create())");

  return generatedLink;
}

std::vector<std::string> Ap::GenerateNetDevicePython()
{
  std::vector<std::string> ndc;

  std::vector<std::string> allNodes = this->GroupAsNodeContainerPython(); //all station nodes !
  for(size_t i = 0; i <  allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back(this->GetNdcName() + " = ns3.NetDeviceContainer()");
  ndc.push_back("ssid_" + this->GetNetworkHardwareName() + " = ns3.Ssid(\"" + this->m_apName + "\")");
  ndc.push_back("wifi_" + this->GetNetworkHardwareName() + " = ns3.WifiHelper.Default()");
  ndc.push_back("wifiMac_" + this->GetNetworkHardwareName() + " = ns3.NqosWifiMacHelper.Default()");
  ndc.push_back("wifi_" + this->GetNetworkHardwareName() + ".SetRemoteStationManager(\"ns3::ArfWifiManager\")");

  ndc.push_back("wifiMac_" + this->GetNetworkHardwareName() + ".SetType (\"ns3::ApWifiMac\", ");
  ndc.push_back("   \"Ssid\", ns3.SsidValue(ssid_" + this->GetNetworkHardwareName() + "), ");
  ndc.push_back("   \"BeaconGeneration\", ns3.BooleanValue(True),");
  ndc.push_back("   \"BeaconInterval\", ns3.TimeValue(ns3.Seconds(2.5)))");
  ndc.push_back(this->GetNdcName() + ".Add(wifi_" + this->GetNetworkHardwareName() + ".Install(wifiPhy_" + this->GetNetworkHardwareName() + ", wifiMac_" + this->GetNetworkHardwareName() + ", " + this->m_apNode + "))");

  ndc.push_back("wifiMac_" + this->GetNetworkHardwareName() + ".SetType(\"ns3::StaWifiMac\",");
  ndc.push_back("   \"Ssid\", ns3.SsidValue(ssid_" + this->GetNetworkHardwareName() + "), ");
  ndc.push_back("   \"ActiveProbing\", ns3.BooleanValue(False))");
  ndc.push_back(this->GetNdcName() + ".Add(wifi_" + this->GetNetworkHardwareName() + ".Install(wifiPhy_" + this->GetNetworkHardwareName() + ", wifiMac_" + this->GetNetworkHardwareName() + ", " + this->GetAllNodeContainer() + " ))");

  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + " = ns3.MobilityHelper()");
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".SetMobilityModel (\"ns3::ConstantPositionMobilityModel\")");
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".Install(" + this->m_apNode + ")");

  if(this->m_mobility)//if random walk is activated.
  {
    ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".SetMobilityModel (\"ns3::RandomWalk2dMobilityModel\",\"Bounds\", RectangleValue (Rectangle (-50, 50, -50, 50)))");
  }
  ndc.push_back("mobility_" + this->GetNetworkHardwareName() + ".Install(" + this->GetAllNodeContainer() + ")");

  return ndc;
}

std::vector<std::string> Ap::GenerateTracePython()
{
  std::vector<std::string> trace;

  if(this->GetTrace())
  {
    trace.push_back("wifiPhy_" + this->GetNetworkHardwareName() + ".EnablePcap(\"" + this->GetNetworkHardwareName() + "\", " + this->GetNdcName() + ".Get(0))");
  }

  return trace;
}
