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
* \file Tap.h
* \brief Tap link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#ifndef TAP_H
#define TAP_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Tap link subclasse.
 *
 * This class is a subclasse from Link, it create a tap link on a csma network.
 * The tap link work like an Hub(csma) ... Just it create the tap bridge to use your host.
 * 
 */
class Tap : public Link
{
public:
  /**
   * \brief Constructor
   * \param _indice the tap number
   * \param _tapNode the external linux host
   * \param _ifaceName the iface name
   */
  Tap(size_t _indice, std::string _tapNode, std::string _ifaceName);
  
  /**
   * \brief Destructor
   */
  virtual ~Tap();
  
private:
  std::string tapNode;
  std::string ifaceName;
  
  std::string getTapName();
  std::string getIfaceName();

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
  
  /**
   * \brief See main class.
   * \return the tap bridge code.
   */
  std::vector<std::string> GenerateTapBridge();
  
  /**
   * \brief See main class.
   * \return the vars code.
   */
  std::vector<std::string> GenerateVars();
  
  /**
   * \brief See main class.
   * \return the cmd line code.
   */
  std::vector<std::string> GenerateCmdLine();
  
};

#endif /* TAP_H */
