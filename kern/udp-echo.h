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
 * \file udp-echo.h
 * \brief The udp echo class subclass of Application.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef UDPECHO_H
#define UDPECHO_H

#include "application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The UDP echo subclass from Application.
 *
 *  The udp-echo class is a subclass of application.
 *
 *  This class represent a udp echo application.
 *
 *  It re-writte some methods which are called to generate ns3 code.
 *
 *  Usage:
 *    - Create an application with udp-echo type.
 */
class UdpEcho : public Application
{
  private:
    /**
     * \brief Application port.
     */
    size_t m_port;

    /**
     * \brief Packet size.
     */
    size_t m_packetSize;

    /**
     * \brief Max packet count.
     */
    size_t m_maxPacketCount;

    /**
     * \brief Packet interval time
     */
    std::string m_packetIntervalTime;

  public:
    /**
     * \brief Constructor.
     * \param indice application number.
     * \param senderNode sender node.
     * \param receiverNode receiver node.
     * \param startTime start time.
     * \param endTime end time.
     * \param port port.
     */
    UdpEcho(const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port);

    /**
     * \brief Destructor.
     */
    ~UdpEcho();

    /**
     * \brief Generate headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate application code.
     * \param netDeviceContainer net device container.
     * \param numberIntoNetDevice number into net device.
     * \return application code.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice);

    /**
     * \brief Get port.
     * \return port.
     */
    size_t getPort();

    /**
     * \brief Set port.
     * \param port new port.
     */
    void setPort(const size_t &port);

    /**
     * \brief Set packet size.
     * \param packetSize new packet size.
     */
    void setPacketSize(const size_t &packetSize);

    /**
     * \brief Get packet size.
     * \return packet size.
     */
    size_t getPacketSize();

    /**
     * \brief Set max packet count.
     * \param maxPacketCount max packet count.
     */
    void setMaxPacketCount(const size_t &maxPacketCount);

    /**
     * \brief Get max packet count.
     * \return max packet count.
     */
    size_t getMaxPacketCount();

    /**
     * \brief Set packet interval time.
     * \param packetIntervalTime packet interval time.
     */
    void setPacketIntervalTime(const std::string &packetIntervalTime);

    /**
     * \brief Get packet interval time.
     * \return packet interval time.
     */
    std::string getPacketIntervalTime();
};

#endif /* UDPECHO_H */

