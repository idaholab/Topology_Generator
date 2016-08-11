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
 * \file udp-echo.cpp
 * \brief Udp-echo Class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "udp-echo.h"
#include "generator.h"

#include "utils.h"

UdpEcho::UdpEcho(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port) : Application(type, indice, senderNode, receiverNode, startTime, endTime)
{
  this->m_port = port;
  this->SetAppName(std::string("udpEcho_" + this->GetIndice()));
  /* default values */
  this->m_packetSize = 1024;
  this->m_maxPacketCount = 1;
  this->m_packetIntervalTime = std::string("1.0");
}

UdpEcho::~UdpEcho()
{
}

size_t UdpEcho::GetPort()
{
  return this->m_port;
}

void UdpEcho::SetPort(const size_t &port)
{
  this->m_port = port;
}

void UdpEcho::SetPacketSize(const size_t &packetSize)
{
  this->m_packetSize = packetSize;
}

size_t UdpEcho::GetPacketSize()
{
  return this->m_packetSize;
}

void UdpEcho::SetMaxPacketCount(const size_t &maxPacketCount)
{
  this->m_maxPacketCount = maxPacketCount;
}

size_t UdpEcho::GetMaxPacketCount()
{
  return this->m_maxPacketCount;
}

void UdpEcho::SetPacketIntervalTime(const std::string &packetIntervalTime)
{
  this->m_packetIntervalTime = packetIntervalTime;
}

std::string UdpEcho::GetPacketIntervalTime()
{
  return this->m_packetIntervalTime;
}

std::vector<std::string> UdpEcho::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/applications-module.h\"");

  return headers;
}

std::vector<std::string> UdpEcho::GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("uint16_t port_" + this->GetAppName() + " = " + utils::integerToString(this->m_port) + ";"); 
  apps.push_back("UdpEchoServerHelper server_" + this->GetAppName() + " (port_" + this->GetAppName() + ");");
  apps.push_back("ApplicationContainer apps_" + this->GetAppName() + " = server_" + this->GetAppName() + ".Install (" + this->GetReceiverNode() + ".Get(0));");
  apps.push_back("apps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  apps.push_back("Time interPacketInterval_" + this->GetAppName() + " = Seconds (" + this->m_packetIntervalTime + ");");
  apps.push_back("UdpEchoClientHelper client_" + this->GetAppName() + " (iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "), " + utils::integerToString(this->m_port) + ");");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"MaxPackets\", UintegerValue (" + utils::integerToString(this->m_maxPacketCount) + "));");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"Interval\", TimeValue (interPacketInterval_" + this->GetAppName() + "));");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"PacketSize\", UintegerValue (" + utils::integerToString(this->m_packetSize) + "));");
  apps.push_back("apps_" + this->GetAppName() + " = client_" + this->GetAppName() + ".Install (" + this->GetSenderNode() + ".Get (0));");
  apps.push_back("apps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".1));");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  return apps;
}

std::vector<std::string> UdpEcho::GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;
  apps.push_back("port_" + this->GetAppName() + " = " + utils::integerToString(this->m_port));
  apps.push_back("server_" + this->GetAppName() + " = ns3.UdpEchoServerHelper(port_" + this->GetAppName() + ")");
  apps.push_back("apps_" + this->GetAppName() + " = server_" + this->GetAppName() + ".Install (" + this->GetReceiverNode() + ".Get(0))");
  apps.push_back("apps_" + this->GetAppName() + ".Start (ns3.Seconds (" + this->GetStartTime() + ".0))");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (ns3.Seconds (" + this->GetEndTime() + ".0))");

  apps.push_back("interPacketInterval_" + this->GetAppName() + " = ns3.Seconds (" + this->m_packetIntervalTime + ")");
  apps.push_back("client_" + this->GetAppName() + " = ns3.UdpEchoClientHelper(iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "), " + utils::integerToString(this->m_port) + ")");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"MaxPackets\", ns3.UintegerValue (" + utils::integerToString(this->m_maxPacketCount) + "))");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"Interval\", ns3.TimeValue (interPacketInterval_" + this->GetAppName() + "))");
  apps.push_back("client_" + this->GetAppName() + ".SetAttribute (\"PacketSize\", ns3.UintegerValue (" + utils::integerToString(this->m_packetSize) + "))");
  apps.push_back("apps_" + this->GetAppName() + " = client_" + this->GetAppName() + ".Install (" + this->GetSenderNode() + ".Get (0))");
  apps.push_back("apps_" + this->GetAppName() + ".Start (ns3.Seconds (" + this->GetStartTime() + ".1))");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (ns3.Seconds (" + this->GetEndTime() + ".0))");
  return apps;
}
