/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
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
 */
/**
* \file Link.cpp
* \brief Link Base Class.
* \author Pierre Weiss
* \date 2009
*/

#include "Link.h"
#include "Generator.h"
#include <stdexcept>

Link::Link(const size_t &_indice)
{
  this->indice = _indice;
  this->dataRate = "100Mbps";
  this->linkDelay = "10";//ms
}

Link::~Link()
{
}

std::string Link::getIndice()
{
  return Generator::toString(this->indice);
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
  
void Link::setLinkName(const std::string &_linkName)
{
  this->linkName = _linkName;
}

void Link::setDataRate(const std::string &_dataRate)
{
  this->dataRate = _dataRate;
}
  
void Link::setLinkDelay(const std::string &_linkDelay)
{
  this->linkDelay = _linkDelay;
}

void Link::setNdcName(const std::string &_ndcName)
{
  this->ndcName = _ndcName;
}

void Link::Install(const std::string &_node)
{
  this->nodes.push_back(_node);
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

std::vector<std::string> Link::GroupAsNodeContainer()
{
  std::vector<std::string> res;
  res.push_back("NodeContainer "+this->getAllNodeContainer()+";");
  for(size_t i = 0; i < (size_t) this->nodes.size(); i++)
  {
    if((this->nodes.at(i)).find("ap_") != 0)
    {
      res.push_back(this->getAllNodeContainer()+".Add("+this->nodes.at(i)+");");
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
  
  
  
