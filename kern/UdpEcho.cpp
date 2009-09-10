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
 * \file UdpEcho.cpp
 * \brief UdpEcho Class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "UdpEcho.h"
#include "Generator.h"

UdpEcho::UdpEcho(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime, const size_t &_port) : Application(_indice, _senderNode, _receiverNode, _startTime, _endTime)
{
  this->port = _port;
  this->appName = "udpEcho_"+this->getIndice();
  /* default values */
  this->packetSize = 1024;
  this->maxPacketCount = 1;
  this->packetIntervalTime = "1.0";
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

  apps.push_back("Time interPacketInterval_"+this->getAppName()+" = Seconds ("+this->packetIntervalTime+");");
  apps.push_back("UdpEchoClientHelper client_"+this->getAppName()+" (iface_"+netDeviceContainer+".GetAddress("+Generator::toString(numberIntoNetDevice)+"), "+Generator::toString(this->port)+");");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"MaxPackets\", UintegerValue ("+Generator::toString(this->maxPacketCount)+"));");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"Interval\", TimeValue (interPacketInterval_"+this->getAppName()+"));");
  apps.push_back("client_"+this->getAppName()+".SetAttribute (\"PacketSize\", UintegerValue ("+Generator::toString(this->packetSize)+"));");
  apps.push_back("apps_"+this->getAppName()+" = client_"+this->getAppName()+".Install ("+this->getSenderNode()+".Get (0));");
  apps.push_back("apps_"+this->getAppName()+".Start (Seconds ("+this->getStartTime()+".1));");
  apps.push_back("apps_"+this->getAppName()+".Stop (Seconds ("+this->getEndTime()+".0));");

  return apps;
}

void UdpEcho::setPacketSize(const size_t &_packetSize)
{
  this->packetSize = _packetSize;
}

size_t UdpEcho::getPacketSize()
{
  return this->packetSize;
}

void UdpEcho::setMaxPacketCount(const size_t &_maxPacketCount)
{
  this->maxPacketCount = _maxPacketCount;
}

size_t UdpEcho::getMaxPacketCount()
{
  return this->maxPacketCount;
}

void UdpEcho::setPacketIntervalTime(const std::string &_packetIntervalTime)
{
  this->packetIntervalTime = _packetIntervalTime;
}

std::string UdpEcho::getPacketIntervalTime()
{
  return this->packetIntervalTime;
}

