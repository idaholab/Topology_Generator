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

TcpLargeTransfer::TcpLargeTransfer(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port) : Application(type, indice, senderNode, receiverNode, startTime, endTime)
{
  this->m_port = port;
  this->SetAppName(std::string("tcp_" + this->GetIndice()));
}

TcpLargeTransfer::~TcpLargeTransfer()
{
}

std::vector<std::string> TcpLargeTransfer::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/applications-module.h\"");

  return headers;
}

size_t TcpLargeTransfer::GetPort()
{
  return this->m_port;
}

void TcpLargeTransfer::SetPort(const size_t &port)
{
  this->m_port = port;
}

std::vector<std::string> TcpLargeTransfer::GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("uint16_t port_" + this->GetAppName() + " = " + utils::integerToString(this->m_port) + ";");
  apps.push_back("Address sinkLocalAddress_" + this->GetAppName() + " (InetSocketAddress (Ipv4Address::GetAny (), port_" + this->GetAppName() + "));");
  apps.push_back("PacketSinkHelper sinkHelper_" + this->GetAppName() + " (\"ns3::TcpSocketFactory\", sinkLocalAddress_" + this->GetAppName() + ");");
  apps.push_back("ApplicationContainer sinkApp_" + this->GetAppName() + " = sinkHelper_" + this->GetAppName() + ".Install (" + this->GetReceiverNode() + ");");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  apps.push_back("OnOffHelper clientHelper_" + this->GetAppName() + " (\"ns3::TcpSocketFactory\", Address ());");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"OnTime\", StringValue (\"ns3::ConstantRandomVariable[Constant=1]\"));");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"OffTime\", StringValue (\"ns3::ConstantRandomVariable[Constant=0]\"));");

  apps.push_back("ApplicationContainer clientApps_" + this->GetAppName() + ";");
  apps.push_back("AddressValue remoteAddress_" + this->GetAppName() + " (InetSocketAddress (iface_" + netDeviceContainer + ".GetAddress (" + utils::integerToString(numberIntoNetDevice) + "), port_" + this->GetAppName() + "));");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute (\"Remote\", remoteAddress_" + this->GetAppName() + ");");
  apps.push_back("clientApps_" + this->GetAppName() + ".Add (clientHelper_" + this->GetAppName() + ".Install (" + this->GetSenderNode() + "));");

  apps.push_back("clientApps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("clientApps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  return apps;
}

std::vector<std::string> TcpLargeTransfer::GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("port_" + this->GetAppName() + " = " + utils::integerToString(this->m_port));
  apps.push_back("sinkLocalAddress_" + this->GetAppName() + " = ns3.Address(ns3.InetSocketAddress(ns3.Ipv4Address.GetAny(), port_" + this->GetAppName() + "))");
  apps.push_back("sinkHelper_" + this->GetAppName() + " = ns3.PacketSinkHelper(\"ns3::TcpSocketFactory\", sinkLocalAddress_" + this->GetAppName() + ")");
  apps.push_back("sinkApp_" + this->GetAppName() + " = sinkHelper_" + this->GetAppName() + ".Install(" + this->GetReceiverNode() + ")");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Start(ns3.Seconds(" + this->GetStartTime() + ".0))");
  apps.push_back("sinkApp_" + this->GetAppName() + ".Stop(ns3.Seconds(" + this->GetEndTime() + ".0))");

  apps.push_back("clientHelper_" + this->GetAppName() + " = ns3.OnOffHelper(\"ns3::TcpSocketFactory\", ns3.Address())");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute(\"OnTime\", ns3.StringValue (\"ns3::ConstantRandomVariable[Constant=1]\"))");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute(\"OffTime\", ns3.StringValue (\"ns3::ConstantRandomVariable[Constant=0]\"))");

  apps.push_back("clientApps_" + this->GetAppName() + " = ns3.ApplicationContainer()");
  apps.push_back("remoteAddress_" + this->GetAppName() + " = ns3.AddressValue(ns3.InetSocketAddress(iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "), port_" + this->GetAppName() + "))");
  apps.push_back("clientHelper_" + this->GetAppName() + ".SetAttribute(\"Remote\", remoteAddress_" + this->GetAppName() + ")");
  apps.push_back("clientApps_" + this->GetAppName() + ".Add(clientHelper_" + this->GetAppName() + ".Install(" + this->GetSenderNode() + "))");

  apps.push_back("clientApps_" + this->GetAppName() + ".Start(ns3.Seconds(" + this->GetStartTime() + ".0))");
  apps.push_back("clientApps_" + this->GetAppName() + ".Stop(ns3.Seconds(" + this->GetEndTime() + ".0))");
  return apps;
}
