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
* \file Bridge.h
* \brief Bridge link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#ifndef BRIDGE_H
#define BRIDGE_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Bridge link subclasse.
 *
 * This class is a subclasse from Link, it create a Bridge link as a Csma network.
 * 
 */
class Bridge : public Link
{
public:
  /**
   * \brief Constructor
   * \param _indice the Bridge number
   * \param _nodeBridge the node which are the bridge.
   */
  Bridge(const size_t &_indice, const std::string &_nodeBridge);
  
  /**
   * \brief Destructor
   */
  virtual ~Bridge();
  
private:

  /**
   * \brief this attribute represent the bridge node name.
   */
  std::string nodeBridge;
  
  /**
   * \brief Function used to get the bridge node name.
   * \return the node name.
   */
  std::string getNodeBridge();
  
  /**
   * \brief Function which return the generated headers.
   * \return headers.
   */
  virtual std::vector<std::string> GenerateHeader();
  
  /**
   * \brief Function which generate the build link code.
   * \return build link code.
   */
  virtual std::vector<std::string> GenerateLink();
  
  /**
   * \brief Function which return the build of the net device container.
   * \return the net device container.
   */
  virtual std::vector<std::string> GenerateNetDevice();
  
};

#endif /* BRIDGE_H */
