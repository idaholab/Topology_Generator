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
 * \file link.cpp
 * \brief Link base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "link.h"
#include "generator.h"
#include <stdexcept>

#include "utils.h"

Link::Link(const size_t &indice)
{
  this->SetIndice(indice);
  this->SetDataRate(std::string("100Mbps"));
  this->SetLinkDelay(std::string("10ms"));

  this->SetTrace(false);
  this->SetPromisc(false);
}

Link::~Link()
{
}

std::string Link::GetIndice()
{
  return utils::integerToString(this->m_indice);
}

void Link::SetIndice(const size_t &indice)
{
  this->m_indice = indice;
}

std::string Link::GetLinkName()
{
  return this->m_linkName;
}

std::string Link::GetDataRate()
{
  return this->m_dataRate;
}

std::string Link::GetLinkDelay()
{
  return this->m_linkDelay;
}

std::string Link::GetNdcName()
{
  return this->m_ndcName;
}

std::vector<std::string> Link::GetInstalledNodes()
{
  return this->m_nodes;
}

std::string Link::GetNInstalledNodes(const size_t &i)
{
  return this->m_nodes.at(i);
}

void Link::removeInstalledNodes(const size_t &nb)
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

void Link::SetLinkName(const std::string &linkName)
{
  this->m_linkName = linkName;
}

void Link::SetDataRate(const std::string &dataRate)
{
  this->m_dataRate = dataRate;
}

void Link::SetLinkDelay(const std::string &linkDelay)
{
  this->m_linkDelay = linkDelay;
}

void Link::SetNdcName(const std::string &ndcName)
{
  this->m_ndcName = ndcName;
}

void Link::Install(const std::string &node)
{
  this->m_nodes.push_back(node);
  std::vector<std::string> trans;
  std::vector<std::string> transWhitoutRouter;
  for(size_t i = 0; i < (size_t) this->GetInstalledNodes().size(); i++)
  {
    if((this->m_nodes.at(i)).find("router_") == 0)
    {
      trans.push_back(this->GetNInstalledNodes(i));
    }
    else
    {
      transWhitoutRouter.push_back(this->GetNInstalledNodes(i));
    }
  }
  for(size_t i = 0; i < (size_t) transWhitoutRouter.size(); i++)
  {
    trans.push_back(transWhitoutRouter.at(i));
  }
  this->m_nodes = trans;
}

std::string Link::GetAllNodeContainer()
{
  return this->m_allNodeContainer;
}

void Link::SetAllNodeContainer(const std::string &allNodeContainer)
{
  this->m_allNodeContainer = allNodeContainer;
}

std::vector<std::string> Link::GroupAsNodeContainer()
{
  std::vector<std::string> res;
  res.push_back("NodeContainer " + this->GetAllNodeContainer() + ";");
  for(size_t i = 0; i < (size_t) this->GetInstalledNodes().size(); i++)
  {
    if((this->GetNInstalledNodes(i)).find("ap_") != 0)
    {
      res.push_back(this->GetAllNodeContainer() + ".Add(" + this->GetNInstalledNodes(i) + ");");
    }
  }

  return res;
}

std::vector<std::string> Link::GenerateTapBridge()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> Link::GenerateVars()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> Link::GenerateCmdLine()
{
  std::vector<std::string> res;
  return res;
}

std::vector<std::string> Link::GenerateTrace()
{
  std::vector<std::string> res;
  return res;
}

void Link::SetTrace(const bool &state)
{
  this->m_enableTrace = state;
}

bool Link::GetTrace()
{
  return this->m_enableTrace;
}

void Link::SetPromisc(const bool &state)
{
  this->m_tracePromisc = state;
}

bool Link::GetPromisc()
{
  return this->m_tracePromisc;
}

