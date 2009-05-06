/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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
* \file Link.h
* \brief Link Base Class.
* \author Pierre Weiss
* \date 2009
*/

#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <string>
#include <vector>


/**
 * \ingroup generator
 * \brief This is the link class.
 *
 * This class is used to used to join Equipement.
 * Like plug pc to a switch.
 * It build the link and join the equipement.
 * 
 */
class Link
{
protected:
  size_t indice;
  std::string linkName;
  std::string dataRate;
  std::string linkDelay;
  std::string ndcName;//ndc == net device container
  std::vector<std::string> nodes;
  std::string allNodeContainer;
  
public:
  Link(size_t _indice);
  virtual ~Link();
  
  virtual std::vector<std::string> GenerateHeader() = 0;
  virtual std::vector<std::string> GenerateLink() = 0;
  virtual std::vector<std::string> GenerateNetDevice() = 0;
  
  std::string getIndice();
  std::string getLinkName();
  std::string getDataRate();
  std::string getLinkDelay();
  std::string getNdcName();
  std::vector<std::string> getNodes();
  
  void setLinkName(std::string _linkName);
  void setDataRate(std::string _dataRate);
  void setLinkDelay(std::string _linkDelay);
  void setNdcName(std::string _ndcName);
  void AddNodes(std::string _node);

  std::string toString(size_t nbr);
  std::vector<std::string> GroupAsNodeContainer();
  std::string getAllNodeContainer();
  
};


#endif /* LINK_H */
