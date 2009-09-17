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
 * \brief udp-echo Class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "udp-echo.h"
#include "generator.h"

#include "utils.h"

UdpEcho::UdpEcho(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime, const size_t &m_port) : Application(m_indice, m_senderNode, m_receiverNode, m_startTime, m_endTime)
{
  this->setPort(m_port);
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

  apps.push_back("uint16_t port_" + this->getAppName() + " = " + utils::toString(this->port) + ";"); 
  apps.push_back("UdpEchoServerHelper server_" + this->getAppName() + " (port_" + this->getAppName() + ");");
  apps.push_back("ApplicationContainer apps_" + this->getAppName() + " = server_" + this->getAppName() + ".Install (" + this->getReceiverNode() + ".Get(0));");
  apps.push_back("apps_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".0));");
  apps.push_back("apps_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  apps.push_back("Time interPacketInterval_" + this->getAppName() + " = Seconds (" + this->packetIntervalTime + ");");
  apps.push_back("UdpEchoClientHelper client_" + this->getAppName() + " (iface_" + netDeviceContainer + ".GetAddress(" + utils::toString(numberIntoNetDevice) + "), " + utils::toString(this->port) + ");");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"MaxPackets\", UintegerValue (" + utils::toString(this->maxPacketCount) + "));");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"Interval\", TimeValue (interPacketInterval_" + this->getAppName() + "));");
  apps.push_back("client_" + this->getAppName() + ".SetAttribute (\"PacketSize\", UintegerValue (" + utils::toString(this->packetSize) + "));");
  apps.push_back("apps_" + this->getAppName() + " = client_" + this->getAppName() + ".Install (" + this->getSenderNode() + ".Get (0));");
  apps.push_back("apps_" + this->getAppName() + ".Start (Seconds (" + this->getStartTime() + ".1));");
  apps.push_back("apps_" + this->getAppName() + ".Stop (Seconds (" + this->getEndTime() + ".0));");

  return apps;
}

size_t UdpEcho::getPort()
{
  return this->port;
}

void UdpEcho::setPort(const size_t &m_port)
{
  this->port = m_port;
}

void UdpEcho::setPacketSize(const size_t &m_packetSize)
{
  this->packetSize = m_packetSize;
}

size_t UdpEcho::getPacketSize()
{
  return this->packetSize;
}

void UdpEcho::setMaxPacketCount(const size_t &m_maxPacketCount)
{
  this->maxPacketCount = m_maxPacketCount;
}

size_t UdpEcho::getMaxPacketCount()
{
  return this->maxPacketCount;
}

void UdpEcho::setPacketIntervalTime(const std::string &m_packetIntervalTime)
{
  this->packetIntervalTime = m_packetIntervalTime;
}

std::string UdpEcho::getPacketIntervalTime()
{
  return this->packetIntervalTime;
}

