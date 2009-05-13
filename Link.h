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
  /**
   *\brief number of the link 
   */
  size_t indice;
  
  /**
   * \brief attribute which represent the link name.
   */
  std::string linkName;
  
  /**
   * \brief attribute which represent the data rate.
   */
  std::string dataRate;
  
  /**
   * \brief attribute which represent the link delay.
   */
  std::string linkDelay;
  
  /**
   * \brief attribute which represent the node device container name.
   */
  std::string ndcName;
  
  /**
   * \brief attribute which represent the node name which are connected to the link.
   */
  std::vector<std::string> nodes;
  
  /**
   * \brief attribute used to save the name of the node container group.
   */
  std::string allNodeContainer;
  
public:
  /**
   * \brief Constructor.
   * 
   * \param _indice the number of the link.
   */
  Link(size_t _indice);
  
  /**
   * \brief Destructor.
   */
  virtual ~Link();
  
  /**
   * \brief Function used to generate the headers.
   * \return headers.
   */
  virtual std::vector<std::string> GenerateHeader() = 0;
  
  /**
   * \brief Function used to generate the c++ code of the link build.
   * \return build link.
   */
  virtual std::vector<std::string> GenerateLink() = 0;
  
  /**
   * \brief Function used to generate the net device container.
   * the net device container contain all nodes installed by the link.
   * \return net device container.
   */
  virtual std::vector<std::string> GenerateNetDevice() = 0;
  
  /**
   * \brief Function used to generate the tap bridge.
   * \return tap bridge code.
   */
  virtual std::vector<std::string> GenerateTapBridge();
  
  /**
   * \brief Function used to generate the vars.
   * \return vars code.
   */
  virtual std::vector<std::string> GenerateVars();
  
  /**
   * \brief Function used to generate the cmd lines.
   * \return cmd line code.
   */
  virtual std::vector<std::string> GenerateCmdLine();
  
  
  /**
   * \brief Function to get the link number.
   * \return the link number.
   */
  std::string getIndice();
  
  /**
   * \brief Function to get link name.
   * \return link name.
   */
  std::string getLinkName();
  
  /**
   * \brief Function to get the link data rate.
   * \return the link data rate.
   */
  std::string getDataRate();
  
  /**
   * \brief Function to get the link delay.
   * Represented in ms.
   * \return link delay.
   */
  std::string getLinkDelay();
  
  /**
   * \brief Function to get the Net device container name.
   * \return the net device container name.
   */
  std::string getNdcName();
  
  /**
   * \brief Function to get the attached nodes list.
   * \return the node list.
   */
  std::vector<std::string> getNodes();
  
  /**
   * \brief Procedure tu set the link rate.
   * \param _linkName the new link name.
   */
  void setLinkName(std::string _linkName);
  
  /**
   * \brief Procedure to set the data rate.
   * \param _dataRate the new data rate.
   */
  void setDataRate(std::string _dataRate);
  
  /**
   * \brief Procedure to set the link delay.
   * \param _linkDelay the new link delay.
   */
  void setLinkDelay(std::string _linkDelay);
  
  /**
   *\brief Procedure to set the net device container name.
   * \param _ndcName the new net device container name.
   */
  void setNdcName(std::string _ndcName);
  
  /**
   * \brief Procedure to add attached to the link node.
   * \param _node the new node to add.
   */
  void AddNodes(std::string _node);

  /**
   * \brief Function to convert size_t to string.
   * \param nbr the number to convert.
   * \return the string of the number.
   */
  std::string toString(size_t nbr);
  
  /**
   * \brief Function use to group all the nodes.
   * \return a node containe with all nodes.
   */
  std::vector<std::string> GroupAsNodeContainer();
  
  /**
   * \brief Function to get the node all node container name.
   * \return the node container name.
   */
  std::string getAllNodeContainer();
  
};


#endif /* LINK_H */
