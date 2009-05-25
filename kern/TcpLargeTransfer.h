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
* \file TcpLargeTransfer.h
* \brief The tcp large transfer echo class subclasse of Application.
* \author Pierre Weiss
* \date 2009
*/

#ifndef TCPLARGETRANSFER_H
#define TCPLARGETRANSFER_H

#include "Application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The tcp large transfer echo subclasse from Application.
 *
 * This class generate the code to tcp tranfer source to destination.
 */
class TcpLargeTransfer : public Application
{
private:
  size_t port;
  
public:
  /**
   * \brief Constructor which set default value.
   * \param _indice
   * \param _senderNode
   * \param _receiverNode
   * \param _startTime
   * \param _endTime
   * \param port
   */
  TcpLargeTransfer(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime, const size_t &port);
  
  /**
   * \brief Destructor
   */
  ~TcpLargeTransfer();
  
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

#endif /* TCPLARGETRANSFER_H */
