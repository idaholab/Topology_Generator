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
* \file Wifi.h
* \brief Wifi link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#ifndef WIFI_H
#define WIFI_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Wifi link subclasse.
 *
 * This class is a subclasse from Link, it create a wifi station and 
 * you can add station to it.
 * 
 */
class Wifi : public Link
{
public:
  /**
   * \brief Constructor
   * \param _indice the Wifi number
   * \param _apNode the node which is the ap.
   * \param _random
   */
  Wifi(const size_t &_indice, const std::string &_apNode, const bool &_random);
  
  /**
   * \brief Destructor
   */
  virtual ~Wifi();
  
private:
  /**
   * \brief attribute which say if station walk is constant or random.
   */
  bool random;
  
  /**
   * \brief attribute which represent the Wifi node.
   */
  std::string apNode;
  
  /**
   * \brief Function to the ap node name.
   * \returnt the ap node name.
   */
  std::string getApNode();
  
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

#endif /* WIFI_H */





