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
 * \file UdpEcho.h
 * \brief The udp echo class subclass of Application.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef UDPECHO_H
#define UDPECHO_H

#include "Application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The UDP echo subclass from Application.
 *
 * This class generate the code to UDP echo source to destination.
 */
class UdpEcho : public Application
{
  private:
    /**
     * \brief the application port.
     */
    size_t port;

    /**
     * \brief the packet size.
     */
    size_t packetSize;

    /**
     * \brief the max packet count.
     */
    size_t maxPacketCount;

    /**
     * \brief the packet interval time
     */
    std::string packetIntervalTime;

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
    UdpEcho(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime, const size_t &port);

    /**
     * \brief Destructor
     */
    ~UdpEcho();

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

    /**
     * \brief procedure to set packet size.
     * \param _packetSize the new packet size.
     */
    void setPacketSize(const size_t &_packetSize);

    /**
     * \brief function to get the packet size.
     * \return packet size
     */
    size_t getPacketSize();

    /**
     * \brief procedure to set the max packet count.
     * \param _maxPacketCount
     */
    void setMaxPacketCount(const size_t &_maxPacketCount);

    /**
     * \brief function to get the max packet count.
     * \return max packet count
     */
    size_t getMaxPacketCount();

    /**
     * \brief procedure to set the packet interval time.
     * \param _packetIntervalTime
     */
    void setPacketIntervalTime(const std::string &_packetIntervalTime);

    /**
     * \brief function to get the packet interval time.
     * \return packet interval time
     */
    std::string getPacketIntervalTime();
};

#endif /* UDPECHO_H */

