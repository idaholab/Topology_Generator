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
 * \file tcp-large-transfer.cpp
 * \brief Tcp large transfer class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "tcp-large-transfer.h"
#include "generator.h"

#include "utils.h"

TcpLargeTransfer::TcpLargeTransfer(const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port) : Application(indice, senderNode, receiverNode, startTime, endTime)
{
  this->SetPort(port);
  this->SetAppName(std::string("tcp_" + this->GetIndice()));
}

TcpLargeTransfer::~TcpLargeTransfer()
{
}

std::vector<std::string> TcpLargeTransfer::GenerateHeader()
{
  std::vector<std::string> headers;
  return headers;
}

std::vector<std::string> TcpLargeTransfer::GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("uint16_t port_" + this->GetAppName() + " = " + utils::integerToString(this->GetPort()) + ";");
  apps.push_back("Address sinkLocalAddress_" + this->GetAppName() + "(InetSocketAddress (Ipv4Address::GetAny (), port_" + this->GetAppName() + "));");
  apps.push_back("PacketSinkHelper sinkHelper_" + this->GetAppName() + " (\"ns3::TcpSocketFactory\", sinkLocalAddress_" + this->GetAppName() + ");");
  apps.push_back("ApplicationContainer sinkApp_" + this->GetAppName() + " = sinkHelper_" + this->GetAppName() + ".Install (" + this->GetReceiverNode() + ");");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  apps.push_back("OnOffHelper clientHelper_" + this->GetAppName() + " (\"ns3::TcpSocketFactory\", Address ());");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"OnTime\", RandomVariableValue (ConstantVariable (1)));");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"OffTime\", RandomVariableValue (ConstantVariable (0)));");

  apps.push_back("ApplicationContainer clientApps_" + this->GetAppName() + ";");
  apps.push_back("AddressValue remoteAddress_" + this->GetAppName() + "(InetSocketAddress (iface_" + netDeviceContainer + ".GetAddress (" + utils::integerToString(numberIntoNetDevice) + "), port_" + this->GetAppName() + "));");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"Remote\", remoteAddress_" + this->GetAppName() + ");");
  apps.push_back("clientApps_" + this->GetAppName() + ".Add(clientHelper_" + this->GetAppName() + ".Install (" + this->GetSenderNode() + "));");

  apps.push_back("clientApps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("clientApps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  return apps;
}

size_t TcpLargeTransfer::GetPort()
{
  return this->m_port;
}

void TcpLargeTransfer::SetPort(const size_t &port)
{
  this->m_port = port;
}

