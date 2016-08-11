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
 * \file ping.cpp
 * \brief Ping Class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "ping.h"
#include "generator.h"

#include "utils.h"

Ping::Ping(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime) : Application(type, indice, senderNode, receiverNode, startTime, endTime)
{
  this->SetAppName(std::string("ping_" + this->GetIndice()));
}

Ping::~Ping()
{
}

std::vector<std::string> Ping::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/applications-module.h\"");
  headers.push_back("#include \"ns3/v4ping-helper.h\"");
  headers.push_back("#include \"ns3/v4ping.h\"");

  return headers;
}

std::vector<std::string> Ping::GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("InetSocketAddress dst_" + this->GetAppName() + " = InetSocketAddress (iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "));");
  apps.push_back("OnOffHelper onoff_" + this->GetAppName() + " = OnOffHelper (\"ns3::Ipv4RawSocketFactory\", dst_" + this->GetAppName() + ");");
  apps.push_back("onoff_" + this->GetAppName() + ".SetAttribute (\"OnTime\", StringValue (\"ns3::ConstantRandomVariable[Constant=1]\"));");
  apps.push_back("onoff_" + this->GetAppName() + ".SetAttribute (\"OffTime\", StringValue (\"ns3::ConstantRandomVariable[Constant=0]\"));");

  apps.push_back("ApplicationContainer apps_" + this->GetAppName() + " = onoff_" + this->GetAppName() + ".Install(" + this->GetSenderNode() + ".Get(0));");
  apps.push_back("apps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".1));");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".1));");

  apps.push_back("PacketSinkHelper sink_" + this->GetAppName() + " = PacketSinkHelper (\"ns3::Ipv4RawSocketFactory\", dst_" + this->GetAppName() + ");");
  apps.push_back("apps_" + this->GetAppName() + " = sink_" + this->GetAppName() + ".Install (" + this->GetReceiverNode() + ".Get(0));");
  apps.push_back("apps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".0));");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".2));");

  apps.push_back("V4PingHelper ping_" + this->GetAppName() + " = V4PingHelper(iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "));");
  apps.push_back("apps_" + this->GetAppName() + " = ping_" + this->GetAppName() + ".Install(" + this->GetSenderNode() + ".Get(0));");
  apps.push_back("apps_" + this->GetAppName() + ".Start (Seconds (" + this->GetStartTime() + ".2));");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (Seconds (" + this->GetEndTime() + ".0));");

  return apps;
}

std::vector<std::string> Ping::GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice)
{
  std::vector<std::string> apps;

  apps.push_back("dst_" + this->GetAppName() + " = ns3.InetSocketAddress(iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "))");
  apps.push_back("onoff_" + this->GetAppName() + " = ns3.OnOffHelper(\"ns3::Ipv4RawSocketFactory\", dst_" + this->GetAppName() + ")");
  apps.push_back("onoff_" + this->GetAppName() + ".SetAttribute(\"OnTime\", ns3.StringValue (\"ns3::ConstantRandomVariable[Constant=1]\"))");
  apps.push_back("onoff_" + this->GetAppName() + ".SetAttribute(\"OffTime\", ns3.StringValue (\"ns3::ConstantRandomVariable[Constant=0]\"))");

  apps.push_back("apps_" + this->GetAppName() + " = onoff_" + this->GetAppName() + ".Install(" + this->GetSenderNode() + ".Get(0))");
  apps.push_back("apps_" + this->GetAppName() + ".Start(ns3.Seconds (" + this->GetStartTime() + ".1))");
  apps.push_back("apps_" + this->GetAppName() + ".Stop(ns3.Seconds (" + this->GetEndTime() + ".1))");

  apps.push_back("sink_" + this->GetAppName() + " = ns3.PacketSinkHelper(\"ns3::Ipv4RawSocketFactory\", dst_" + this->GetAppName() + ")");
  apps.push_back("apps_" + this->GetAppName() + " = sink_" + this->GetAppName() + ".Install(" + this->GetReceiverNode() + ".Get(0))");
  apps.push_back("apps_" + this->GetAppName() + ".Start(ns3.Seconds(" + this->GetStartTime() + ".0))");
  apps.push_back("apps_" + this->GetAppName() + ".Stop(ns3.Seconds(" + this->GetEndTime() + ".2))");

  apps.push_back("ping_" + this->GetAppName() + " = ns3.V4PingHelper(iface_" + netDeviceContainer + ".GetAddress(" + utils::integerToString(numberIntoNetDevice) + "))");
  apps.push_back("apps_" + this->GetAppName() + " = ping_" + this->GetAppName() + ".Install(" + this->GetSenderNode() + ".Get(0))");
  apps.push_back("apps_" + this->GetAppName() + ".Start (ns3.Seconds(" + this->GetStartTime() + ".2))");
  apps.push_back("apps_" + this->GetAppName() + ".Stop (ns3.Seconds(" + this->GetEndTime() + ".0))");
  return apps;
}
