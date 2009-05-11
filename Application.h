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
* \file Application.h
* \brief Application Base Class.
* \author Pierre Weiss
* \date 2009
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <vector>


/**
 * \ingroup generator
 * \brief The main class of applications.
 *
 * This classe is the main class of applications.
 * 
 */
class Application
{
protected:
  /**
   * \brief attribute which represent the app number.
   */
  size_t indice;
  
  /**
   * \brief attribute which represent the application name.
   */
  std::string appName;
  
  /**
   * \brief attribute which represent the pinger sender node.
   */
  std::string senderNode;
  
  /**
   * \brief attribute which represent the pinger receiver node.
   */
  std::string receiverNode;
  
  /**
   * \brief atribute which represent the start time.
   */
  size_t startTime;
  
  /**
   * \brief atribute which represent the end time.
   */
  size_t endTime;
  
  
  
public:
  /**
   * \brief Constructor which set default value.
   * \param _indice
   * \param _senderNode
   * \param _receiverNode
   * \param _startTime
   * \param _endTime
   */
  Application(size_t _indice, std::string _senderNode, std::string _receiverNode, size_t _startTime, size_t _endTime);
  
  /**
   * \brief Destructor from the class Equipement.
   */
  virtual ~Application();

  /**
   * \brief Function used to generate the headers.
   * \return headers.
   */
  virtual std::vector<std::string> GenerateHeader() = 0;
  
  /**
   * \brief Function used to generate the application.
   * 
   * \param netDeviceContainer
   * \param numberIntoNetDevice
   * \return application code.
   */
  virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice) = 0;
  
  /**
   * \brief Function to get the app number.
   * \return app number.
   */
  std::string getIndice();
  
  /**
   * \brief Procedure to set the app number.
   * \param _indice
   */
  void setIndice(size_t _indice);
  
  /**
   * \brief Function to get the app node name.
   * \return app node name.
   */
  std::string getAppName();
  
  /**
   * \brief Procedure to set the app name.
   * \param _appName the new app name.
   */
  void setAppName(std::string _appName);
  
  /**
   * \brief Function to get the sender node name.
   * \return sender node name.
   */
  std::string getSenderNode();
  
  /**
   * \brief Procedure to set the sender node name.
   * \param _senderNode the new sender node name.
   */
  void setSenderNode(std::string _senderNode);
  
  /**
   * \brief Function to get the receiver node name.
   * \return receiver node name.
   */
  std::string getReceiverNode();
  
  /**
   * \brief Procedure to set the receiver node name.
   * \param _receiverNode the new receiver node name.
   */
  void setReceiverNode(std::string _receiverNode);
  
  /**
   * \brief Function to get start time.
   * \return start time.
   */
  std::string getStartTime();
  
  /**
   * \brief Procedure to set the start time.
   * \param _startTime the start time.
   */
  void setStartTime(size_t _startTime);
  
  /**
   * \brief Function to get end time.
   * \return end time.
   */
  std::string getEndTime();
  
  /**
   * \brief Procedure to set the end time.
   * \param _endTime the end time.
   */
  void setEndTime(size_t _endTime);
  
};


#endif /* APPLICATION_H */

