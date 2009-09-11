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
 * \file hub.cpp
 * \brief Hub link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#include "hub.h"

Hub::Hub(const size_t &_indice) : Link(_indice)
{
  this->linkName = "hub_" + this->getIndice();
  this->ndcName = "ndc_" + this->getLinkName();
  this->allNodeContainer = "all_" + this->getLinkName();
}

Hub::~Hub()
{
}

std::vector<std::string> Hub::GenerateHeader()
{
  std::vector<std::string> headers;
  headers.push_back("#include \"ns3/bridge-module.h\"");

  return headers;
}

std::vector<std::string> Hub::GenerateLink()
{
  std::vector<std::string> generatedLink;
  generatedLink.push_back("CsmaHelper csma_" + this->getLinkName() + ";");
  generatedLink.push_back("csma_" + this->getLinkName() + ".SetChannelAttribute (\"DataRate\", StringValue (\"" + this->getDataRate() + "\"));");
  generatedLink.push_back("csma_" + this->getLinkName() + ".SetChannelAttribute (\"Delay\",  StringValue (\"" + this->getLinkDelay() + "\"));");

  return generatedLink;
}

std::vector<std::string> Hub::GenerateNetDevice()
{
  std::vector<std::string> ndc;
  std::vector<std::string> allNodes = this->GroupAsNodeContainer();
  for(size_t i = 0; i < (size_t) allNodes.size(); i++)
  {
    ndc.push_back(allNodes.at(i));
  }
  ndc.push_back("NetDeviceContainer " + this->getNdcName() + " = csma_" + this->getLinkName() + ".Install (" + this->getAllNodeContainer() + ");");

  return ndc;
}

std::vector<std::string> Hub::GenerateTrace()
{
  std::vector<std::string> trace;

  if(this->enableTrace)
  {
    if(this->tracePromisc)
    {
      trace.push_back("csma_" + this->getLinkName() + ".EnablePcapAll (\"csma_" + this->getLinkName() + "\", true);");
    }
    else
    {
      trace.push_back("csma_" + this->getLinkName() + ".EnablePcapAll (\"csma_" + this->getLinkName() + "\", false);");
    }
  }

  return trace;
}

