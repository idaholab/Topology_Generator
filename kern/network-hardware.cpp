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
 * \file network-hardware.cpp
 * \brief Link base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "network-hardware.h"
#include "generator.h"
#include <stdexcept>

#include "utils.h"

NetworkHardware::NetworkHardware(const std::string &type, const size_t &indice)
{
  this->m_type = type;
  this->m_indice = indice;
  this->m_dataRate = std::string("100000000"); /* 100 Mbps */
  this->m_networkHardwareDelay = std::string("10000"); /* 10 ms */

  this->m_enableTrace = false;
  this->m_tracePromisc = false;
}

NetworkHardware::~NetworkHardware()
{
}

std::string NetworkHardware::GetIndice()
{
  return utils::integerToString(this->m_indice);
}

void NetworkHardware::SetIndice(const size_t &indice)
{
  this->m_indice = indice;
}

std::string NetworkHardware::GetNetworkHardwareName()
{
  return this->m_networkHardwareName;
}

std::string NetworkHardware::GetDataRate()
{
  return this->m_dataRate;
}

std::string NetworkHardware::GetNetworkHardwareDelay()
{
  return this->m_networkHardwareDelay;
}

std::string NetworkHardware::GetNdcName()
{
  return this->m_ndcName;
}

std::vector<std::string> NetworkHardware::GetInstalledNodes()
{
  return this->m_nodes;
}

std::string NetworkHardware::GetInstalledNode(const size_t &i)
{
  return this->m_nodes.at(i);
}

void NetworkHardware::removeInstalledNode(const size_t &nb)
{
  try
  {
    this->m_nodes.erase(this->m_nodes.begin() + nb);
  }
  catch(const std::out_of_range &e)
  {
    throw std::out_of_range(e);
    return;
  }
}

void NetworkHardware::SetNetworkHardwareName(const std::string &linkName)
{
  this->m_networkHardwareName = linkName;
}

void NetworkHardware::SetDataRate(const std::string &dataRate)
{
  this->m_dataRate = dataRate;
}

void NetworkHardware::SetNetworkHardwareDelay(const std::string &linkDelay)
{
  this->m_networkHardwareDelay = linkDelay;
}

void NetworkHardware::SetNdcName(const std::string &ndcName)
{
  this->m_ndcName = ndcName;
}

void NetworkHardware::Install(const std::string &node)
{
  this->m_nodes.push_back(node);
  std::vector<std::string> trans;
  std::vector<std::string> transWhitoutRouter;
  for(size_t i = 0; i <  this->m_nodes.size(); i++)
  {
    if((this->m_nodes.at(i)).find("router_") == 0)
    {
      trans.push_back(this->m_nodes.at(i));
    }
    else
    {
      transWhitoutRouter.push_back(this->m_nodes.at(i));
    }
  }
  for(size_t i = 0; i <  transWhitoutRouter.size(); i++)
  {
    trans.push_back(transWhitoutRouter.at(i));
  }
  this->m_nodes = trans;
}

std::string NetworkHardware::GetAllNodeContainer()
{
  return this->m_allNodeContainer;
}

void NetworkHardware::SetAllNodeContainer(const std::string &allNodeContainer)
{
  this->m_allNodeContainer = allNodeContainer;
}

std::vector<std::string> NetworkHardware::GroupAsNodeContainerCpp()
{
  std::vector<std::string> res;
  res.push_back("NodeContainer " + this->m_allNodeContainer + ";");
  for(size_t i = 0; i <  this->m_nodes.size(); i++)
  {
    if((this->m_nodes.at(i)).find("ap_") != 0)
    {
      res.push_back(this->m_allNodeContainer + ".Add (" + this->m_nodes.at(i) + ");");
    }
  }

  return res;
}

std::vector<std::string> NetworkHardware::GroupAsNodeContainerPython()
{
  std::vector<std::string> res;

  res.push_back(this->m_allNodeContainer + " = ns3.NodeContainer()");
  for(size_t i = 0; i <  this->m_nodes.size(); i++)
  {
    if((this->m_nodes.at(i)).find("ap_") != 0)
    {
      res.push_back(this->m_allNodeContainer + ".Add (" + this->m_nodes.at(i) + ")");
    }
  }
  return res;
}

void NetworkHardware::SetTrace(const bool &state)
{
  this->m_enableTrace = state;
}

bool NetworkHardware::GetTrace()
{
  return this->m_enableTrace;
}

void NetworkHardware::SetPromisc(const bool &state)
{
  this->m_tracePromisc = state;
}

bool NetworkHardware::GetPromisc()
{
  return this->m_tracePromisc;
}

std::vector<std::string> NetworkHardware::GenerateTapBridgeCpp()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateVarsCpp()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateCmdLineCpp()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateTraceCpp()
{
  std::vector<std::string> res;
  return res;
}

/* XXX to move elsewhere */
std::vector<std::string> NetworkHardware::GenerateTapBridgePython()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateVarsPython()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateCmdLinePython()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> NetworkHardware::GenerateTracePython()
{
  std::vector<std::string> res;
  return res;
}

std::string NetworkHardware::GetLinkType()
{
  return this->m_type;
}

