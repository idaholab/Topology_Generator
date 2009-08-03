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
  Application(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime);
  
  /**
   * \brief Destructor from the class Application.
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
  void setIndice(const size_t &_indice);
  
  /**
   * \brief Function to get the app node name.
   * \return app node name.
   */
  std::string getAppName();
  
  /**
   * \brief Procedure to set the app name.
   * \param _appName the new app name.
   */
  void setAppName(const std::string &_appName);
  
  /**
   * \brief Function to get the sender node name.
   * \return sender node name.
   */
  std::string getSenderNode();
  
  /**
   * \brief Procedure to set the sender node name.
   * \param _senderNode the new sender node name.
   */
  void setSenderNode(const std::string &_senderNode);
  
  /**
   * \brief Function to get the receiver node name.
   * \return receiver node name.
   */
  std::string getReceiverNode();
  
  /**
   * \brief Procedure to set the receiver node name.
   * \param _receiverNode the new receiver node name.
   */
  void setReceiverNode(const std::string &_receiverNode);
  
  /**
   * \brief Function to get start time.
   * \return start time.
   */
  std::string getStartTime();
  
  /**
   * \brief Procedure to set the start time.
   * \param _startTime the start time.
   */
  void setStartTime(const size_t &_startTime);
  
  /**
   * \brief Function to get end time.
   * \return end time.
   */
  std::string getEndTime();
  
   /**
   * \brief Function to get end time.
   * \return end time in number.
   */
  size_t getEndTimeNumber();
  
  /**
   * \brief Procedure to set the end time.
   * \param _endTime the end time.
   */
  void setEndTime(const size_t &_endTime);

  /* UPD ECHO PARAMS */
  
  /**
   * \brief procedure to set packet size.(Udp Echo)
   * \param _packetSize the new packet size.
   */
  virtual void setPacketSize(const size_t &_packetSize);

  /**
   * \brief function to get the packet size.(Udp Echo)
   * \return packet size
   */
  virtual size_t getPacketSize();

  /**
   * \brief procedure to set the max packet count.(Udp Echo)
   * \param _maxPacketCount
   */
  virtual void setMaxPacketCount(const size_t &_maxPacketCount);

  /**
   * \brief function to get the max packet count.(Udp Echo)
   * \return max packet count
   */
  virtual size_t getMaxPacketCount();

  /**
   * \brief procedure to set the packet interval time.(Udp Echo)
   * \param _packetIntervalTime
   */
  virtual void setPacketIntervalTime(const std::string &_packetIntervalTime);

  /**
   * \brief function to get the packet interval time.(Udp Echo)
   * \return packet interval time
   */
  virtual std::string getPacketIntervalTime();

};


#endif /* APPLICATION_H */

