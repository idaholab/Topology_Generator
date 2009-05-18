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
* \file Ping.h
* \brief The ping class subclasse of Application.
* \author Pierre Weiss
* \date 2009
*/

#ifndef PING_H
#define PING_H

#include "Application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The Ping subclasse from Application.
 *
 * This class generate the code to ping source to destination.
 */
class Ping : public Application
{
public:
  /**
   * \brief Constructor which set default value.
   * \param _indice
   * \param _senderNode
   * \param _receiverNode
   * \param _startTime
   * \param _endTime
   */
  Ping(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime);
  
  /**
   * \brief Destructor
   */
  ~Ping();
  
  /**
   * \brief Function used to generate the headers.
   * \return headers.
   */
  virtual std::vector<std::string> GenerateHeader();
  
  /**
   * \brief Function used to generate the application.
   * 
   * \param netDeviceContainer
   * \param numberIntoNetDevice
   * \return application code.
   */
  virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice);
  
};

#endif /* PING_H */
