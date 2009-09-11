/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
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
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

/**
 * \file application.h
 * \brief application base class.
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
 *  The applications class is the main class of all applications.
 *  
 *  Usage : (Call a subclass)
 *    - ping
 *    - tcp-large-transfert
 *    - udp-echo
 *
 *  To add a new application, please see the subclasse for example.
 *  example of .h file :
 *
 *    #include "application.h"
 *    class new-class : public Application
 *    {
 *      new-class(...);
 *      ~new-class();
 *      
 *      virtual std::vector<std::string> GenerateHeader();
 *      virtual std::vector<std::string> GenerateApplication(std::string, size_t);
 *    }
 */
class Application
{
  protected:
    /**
     * \brief attribute which represent the application number.
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
     * \brief constructor which set default value.
     * \param _indice is the application number
     * \param _senderNode is the sender node
     * \param _receiverNode is the receiver node
     * \param _startTime is the application start time
     * \param _endTime is the application end time
     */
    Application(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime);

    /**
     * \brief destructor from the class application.
     */
    virtual ~Application();

    /**
     * \brief function used to generate the headers.
     * \return the headers.
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief function used to generate the application code.
     * \param netDeviceContainer is the ns3 net device containe
     * \param numberIntoNetDevice is the place from the sender node in the assigned ip network.
     * \parem numberIntoNetDevice example sender node is 192.168.0.5, then the number is 5.
     * \return the code from the application.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice) = 0;

    /**
     * \brief function to get the application number.
     * \return application number.
     */
    std::string getIndice();

    /**
     * \brief procedure to set the application number.
     * \param _indice is the new indice.
     */
    void setIndice(const size_t &_indice);

    /**
     * \brief function to get the application node name.
     * \return the application node name.
     */
    std::string getAppName();

    /**
     * \brief procedure to set the application name.
     * \param _appName is the new application name.
     */
    void setAppName(const std::string &_appName);

    /**
     * \brief function to get the sender node name.
     * \return the sender node name.
     */
    std::string getSenderNode();

    /**
     * \brief procedure to set the sender node name.
     * \param _senderNode is the new sender node name.
     */
    void setSenderNode(const std::string &_senderNode);

    /**
     * \brief function to get the receiver node name.
     * \return the receiver node name.
     */
    std::string getReceiverNode();

    /**
     * \brief procedure to set the receiver node name.
     * \param _receiverNode is the new receiver node name.
     */
    void setReceiverNode(const std::string &_receiverNode);

    /**
     * \brief function to get application start time.
     * \return the application start time.
     */
    std::string getStartTime();

    /**
     * \brief procedure to set the application start time.
     * \param _startTime is the application start time.
     */
    void setStartTime(const size_t &_startTime);

    /**
     * \brief function to get the application end time.
     * \return the application end time.
     */
    std::string getEndTime();

    /**
     * \brief function to get the application end time.
     * \return the end time in number.
     */
    size_t getEndTimeNumber();

    /**
     * \brief procedure to set the application end time.
     * \param _endTime is the application end time.
     */
    void setEndTime(const size_t &_endTime);

    /* UDP ECHO PARAMS */
/* must be removed. See .cpp source code. */

    /**
     * \brief procedure to set packet size (Udp Echo).
     * \param _packetSize the new packet size.
     */
    virtual void setPacketSize(const size_t &_packetSize);

    /**
     * \brief function to get the packet size (Udp Echo).
     * \return packet size
     */
    virtual size_t getPacketSize();

    /**
     * \brief procedure to set the max packet count (Udp Echo).
     * \param _maxPacketCount
     */
    virtual void setMaxPacketCount(const size_t &_maxPacketCount);

    /**
     * \brief function to get the max packet count (Udp Echo).
     * \return max packet count
     */
    virtual size_t getMaxPacketCount();

    /**
     * \brief procedure to set the packet interval time (Udp Echo).
     * \param _packetIntervalTime
     */
    virtual void setPacketIntervalTime(const std::string &_packetIntervalTime);

    /**
     * \brief function to get the packet interval time (Udp Echo).
     * \return packet interval time
     */
    virtual std::string getPacketIntervalTime();
};

#endif /* APPLICATION_H */

