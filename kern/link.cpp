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
 * \brief link base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "link.h"
#include "generator.h"
#include <stdexcept>

#include "utils.h"

Link::Link(const size_t &m_indice)
{
  this->setIndice(m_indice);
  this->setDataRate(std::string("100Mbps"));
  this->setLinkDelay(std::string("10ms"));

  this->setTrace(false);
  this->setPromisc(false);
}

Link::~Link()
{
}

std::string Link::getIndice()
{
  return utils::toString(this->indice);
}

void Link::setIndice(const size_t &m_indice)
{
  this->indice = m_indice;
}

std::string Link::getLinkName()
{
  return this->linkName;
}

std::string Link::getDataRate()
{
  return this->dataRate;
}

std::string Link::getLinkDelay()
{
  return this->linkDelay;
}

std::string Link::getNdcName()
{
  return this->ndcName;
}

std::vector<std::string> Link::getNodes()
{
  return this->nodes;
}

void Link::setLinkName(const std::string &m_linkName)
{
  this->linkName = m_linkName;
}

void Link::setDataRate(const std::string &m_dataRate)
{
  this->dataRate = m_dataRate;
}

void Link::setLinkDelay(const std::string &m_linkDelay)
{
  this->linkDelay = m_linkDelay;
}

void Link::setNdcName(const std::string &m_ndcName)
{
  this->ndcName = m_ndcName;
}

void Link::Install(const std::string &m_node)
{
  this->nodes.push_back(m_node);
  std::vector<std::string> trans;
  std::vector<std::string> transWhitoutRouter;
  for(size_t i = 0; i < (size_t) this->nodes.size(); i++)
  {
    if((this->nodes.at(i)).find("router_") == 0)
    {
      trans.push_back(this->nodes.at(i));
    }
    else
    {
      transWhitoutRouter.push_back(this->nodes.at(i));
    }
  }
  for(size_t i = 0; i < (size_t) transWhitoutRouter.size(); i++)
  {
    trans.push_back(transWhitoutRouter.at(i));
  }
  this->nodes = trans;
}

std::string Link::getAllNodeContainer()
{
  return this->allNodeContainer;
}

void Link::setAllNodeContainer(const std::string &m_allNodeContainer)
{
  this->allNodeContainer = m_allNodeContainer;
}

std::vector<std::string> Link::GroupAsNodeContainer()
{
  std::vector<std::string> res;
  res.push_back("NodeContainer " + this->getAllNodeContainer() + ";");
  for(size_t i = 0; i < (size_t) this->nodes.size(); i++)
  {
    if((this->nodes.at(i)).find("ap_") != 0)
    {
      res.push_back(this->getAllNodeContainer() + ".Add(" + this->nodes.at(i) + ");");
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

void Link::setTrace(const bool &m_state)
{
  this->enableTrace = m_state;
}

bool Link::getTrace()
{
  return this->enableTrace;
}

void Link::setPromisc(const bool &m_state)
{
  this->tracePromisc = m_state;
}

bool Link::getPromisc()
{
  return this->tracePromisc;
}

