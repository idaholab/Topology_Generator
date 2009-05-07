/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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
* \file Wifi.cpp
* \brief Wifi link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#include "Wifi.h"


Wifi::Wifi(size_t _indice, std::string _apNode) : Link(_indice)
{
  this->linkName = "wifi_"+this->getIndice();
  this->ndcName = "ndc_"+this->getLinkName();
  this->allNodeContainer = "all_"+this->getLinkName();
  this->apNode = _apNode;
}

Wifi::~Wifi()
{
}
std::string Wifi::getApNode()
{
  return this->apNode;
}

std::vector<std::string> Wifi::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/wifi-module.h\"");
  headers.push_back("#include \"ns3/mobility-module.h\"");
  
  return headers;
}

std::vector<std::string> Wifi::GenerateLink()
{
  std::vector<std::string> generatedLink;
  /* creation of the link. */
  generatedLink.push_back("YansWifiPhyHelper wifiPhy_"+this->getLinkName()+" = YansWifiPhyHelper::Default ();");
  generatedLink.push_back("YansWifiChannelHelper wifiChannel_"+this->getLinkName()+" = YansWifiChannelHelper::Default ();");
  generatedLink.push_back("wifiPhy_"+this->getLinkName()+".SetChannel (wifiChannel_"+this->getLinkName()+".Create ());");
  
  return generatedLink;
}

std::vector<std::string> Wifi::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();//all station nodes !
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  
  ndc.push_back("Ssid ssid_"+this->getLinkName()+" = Ssid (\"wifi-default-"+this->getIndice()+"\");");
  ndc.push_back("WifiHelper wifi_"+this->getLinkName()+" = WifiHelper::Default ();");
  ndc.push_back("wifi_"+this->getLinkName()+".SetRemoteStationManager (\"ns3::ArfWifiManager\");");

  ndc.push_back("wifi_"+this->getLinkName()+".SetMac (\"ns3::NqapWifiMac\", ");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_"+this->getLinkName()+"), ");
  ndc.push_back("   \"BeaconGeneration\", BooleanValue (true),"); 
  ndc.push_back("   \"BeaconInterval\", TimeValue (Seconds (2.5)));");
  ndc.push_back(this->getNdcName()+".Add(wifi_"+this->getLinkName()+".Install (wifiPhy_"+this->getLinkName()+", "+this->getApNode()+"));");
  
  ndc.push_back("wifi_"+this->getLinkName()+".SetMac (\"ns3::NqstaWifiMac\",");
  ndc.push_back("   \"Ssid\", SsidValue (ssid_"+this->getLinkName()+"), ");
  ndc.push_back("   \"ActiveProbing\", BooleanValue (false));");
  ndc.push_back(this->getNdcName()+".Add (wifi_"+this->getLinkName()+".Install (wifiPhy_"+this->getLinkName()+", "+this->getAllNodeContainer()+" );");

  ndc.push_back("MobilityHelper mobility_"+this->getLinkName()+";");
  ndc.push_back("mobility_"+this->getLinkName()+".Install("+this->getAllNodeContainer()+");");
  
  return ndc;
}

  

  

  

