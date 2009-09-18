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

UdpEcho::UdpEcho(const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port) : Application(indice, senderNode, receiverNode, startTime, endTime)
{
  this->setPort(port);
  this->setAppName(std::string("udpEcho_" + this->getIndice()));
  /* default values */
  this->setPacketSize(1024);
  this->setMaxPacketCount(1);
  this->setPacketIntervalTime(std::string("1.0"));
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

  apps.push_back("uint16_t port_" + this->getAppName() + " = " + utils::toString(this->getPort()) + ";"); 
  apps.push_back("UdpEchoServerHelper server_" + this->getAppName() + " (port_" + this->getAppName() + ");");
  apps.push_back("ApplicationContainer apps_" + this->getAppName() + " = server_" + this->getAppName() + ".Install (" + this->getReceiverNode() + ".Get(0));");
  apps.push_back("apps_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".0));");
  apps.push_back("apps_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  apps.push_back("Time interPacketInterval_" + this->getAppName() + " = Seconds (" + this->getPacketIntervalTime() + ");");
  apps.push_back("UdpEchoClientHelper client_" + this->getAppName() + " (iface_" + netDeviceContainer + ".GetAddress(" + utils::toString(numberIntoNetDevice) + "), " + utils::toString(this->getPort()) + ");");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"MaxPackets\", UintegerValue (" + utils::toString(this->getMaxPacketCount()) + "));");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"Interval\", TimeValue (interPacketInterval_" + this->getAppName() + "));");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"PacketSize\", UintegerValue (" + utils::toString(this->getPacketSize()) + "));");
  apps.push_back("apps_" + this->getAppName() + " = client_" + this->getAppName() + ".Install (" + this->getSenderNode() + ".Get (0));");
  apps.push_back("apps_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".1));");
  apps.push_back("apps_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  return apps;
}

size_t UdpEcho::getPort()
{
  return this->m_port;
}

void UdpEcho::setPort(const size_t &port)
{
  this->m_port = port;
}

void UdpEcho::setPacketSize(const size_t &packetSize)
{
  this->m_packetSize = packetSize;
}

size_t UdpEcho::getPacketSize()
{
  return this->m_packetSize;
}

void UdpEcho::setMaxPacketCount(const size_t &maxPacketCount)
{
  this->m_maxPacketCount = maxPacketCount;
}

size_t UdpEcho::getMaxPacketCount()
{
  return this->m_maxPacketCount;
}

void UdpEcho::setPacketIntervalTime(const std::string &packetIntervalTime)
{
  this->m_packetIntervalTime = packetIntervalTime;
}

std::string UdpEcho::getPacketIntervalTime()
{
  return this->m_packetIntervalTime;
}

