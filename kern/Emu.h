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
* \file Emu.h
* \brief Emu link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#ifndef EMU_H
#define EMU_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Emu link subclasse.
 *
 * This class is a subclasse from Link, it create a Emu link on a csma network.
 * It use an real host interface like eth0
 * 
 */
class Emu : public Link
{
public:
  /**
   * \brief Constructor
   * \param _indice the tap number
   * \param _emuNode the external linux host
   * \param _ifaceName the iface name
   */
  Emu(const size_t &_indice, const std::string &_emuNode, const std::string &_ifaceName);
  
  /**
   * \brief Destructor
   */
  virtual ~Emu();
  
private:
  /**
   * \brief emu node name attribute  
   */
  std::string emuNode;
  
  /**
   * \brief interface name attribute
   */
  std::string ifaceName;
  
  /**
   * \brief Function to get the emu node name.
   * \return emu node name
   */
  std::string getEmuName();
  
  /**
   * \brief Function to get the emu interface name.
   * \return interface name
   */
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
   * \return the vars code.
   */
  std::vector<std::string> GenerateVars();
  
  /**
   * \brief See main class.
   * \return the cmd line code.
   */
  std::vector<std::string> GenerateCmdLine();
  
};

#endif /* EMU_H */
