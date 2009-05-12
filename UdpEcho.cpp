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
* \file UdpEcho.cpp
* \brief UdpEcho Class.
* \author Pierre Weiss
* \date 2009
*/

#include "UdpEcho.h"
#include "Generator.h"

UdpEcho::UdpEcho(size_t _indice, std::string _senderNode, std::string _receiverNode, size_t _startTime, size_t _endTime, size_t _port) : Application(_indice, _senderNode, _receiverNode, _startTime, _endTime)
{
  this->port = _port;
  this->appName = "udpEcho_"+this->getIndice();
}

UdpEcho::~UdpEcho()
{
}

std::vector<std::string> UdpEcho::GenerateHeader()
{
  std::vector<std::string> headers;
  return headers;
}
  
std::vector<std::string> UdpEcho::GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;
  
  apps.push_back("uint16_t port_"+this->getAppName()+" = "+Generator::toString(this->port)+";"); 
  apps.push_back("UdpEchoServerHelper server_"+this->getAppName()+" (port_"+this->getAppName()+");");
  apps.push_back("ApplicationContainer apps_"+this->getAppName()+" = server_"+this->getAppName()+".Install ("+this->getReceiverNode()+".Get(0));");
  apps.push_back("apps_"+this->getAppName()+".Start (Seconds ("+this->getStartTime()+".0));");
  apps.push_back("apps_"+this->getAppName()+".Stop (Seconds ("+this->getEndTime()+".0));");

  apps.push_back("uint32_t packetSize_"+this->getAppName()+" = 1024;");
  apps.push_back("uint32_t maxPacketCount_"+this->getAppName()+" = 1;");
  apps.push_back("Time interPacketInterval_"+this->getAppName()+" = Seconds (1.);");
  apps.push_back("UdpEchoClientHelper client_"+this->getAppName()+" (iface_"+netDeviceContainer+".GetAddress("+Generator::toString(numberIntoNetDevice)+"), "+Generator::toString(this->port)+");");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"MaxPackets\", UintegerValue (maxPacketCount_"+this->getAppName()+"));");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"Interval\", TimeValue (interPacketInterval_"+this->getAppName()+"));");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"PacketSize\", UintegerValue (packetSize_"+this->getAppName()+"));");
  apps.push_back("apps_"+this->getAppName()+" = client_"+this->getAppName()+".Install ("+this->getSenderNode()+".Get (0));");
  apps.push_back("apps_"+this->getAppName()+".Start (Seconds ("+this->getStartTime()+".1));");
  apps.push_back("apps_"+this->getAppName()+".Stop (Seconds ("+this->getEndTime()+".0));");
  
  return apps;
}

