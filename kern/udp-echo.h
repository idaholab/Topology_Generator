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
     * \brief application port.
     */
    size_t port;

    /**
     * \brief packet size.
     */
    size_t packetSize;

    /**
     * \brief max packet count.
     */
    size_t maxPacketCount;

    /**
     * \brief packet interval time
     */
    std::string packetIntervalTime;

  public:
    /**
     * \brief constructor.
     * \param m_indice application number.
     * \param m_senderNode sender node.
     * \param m_receiverNode receiver node.
     * \param m_startTime start time.
     * \param m_endTime end time.
     * \param port port.
     */
    UdpEcho(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime, const size_t &port);

    /**
     * \brief destructor.
     */
    ~UdpEcho();

    /**
     * \brief generate headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief generate application code.
     * \param netDeviceContainer net device container.
     * \param numberIntoNetDevice number into net device.
     * \return application code.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice);

    /**
     * \brief get port.
     * \return port.
     */
    size_t getPort();

    /**
     * \brief set port.
     * \param m_port new port.
     */
    void setPort(const size_t &m_port);

    /**
     * \brief set packet size.
     * \param m_packetSize new packet size.
     */
    void setPacketSize(const size_t &m_packetSize);

    /**
     * \brief get packet size.
     * \return packet size.
     */
    size_t getPacketSize();

    /**
     * \brief set max packet count.
     * \param m_maxPacketCount max packet count.
     */
    void setMaxPacketCount(const size_t &m_maxPacketCount);

    /**
     * \brief get max packet count.
     * \return max packet count.
     */
    size_t getMaxPacketCount();

    /**
     * \brief set packet interval time.
     * \param m_packetIntervalTime packet interval time.
     */
    void setPacketIntervalTime(const std::string &m_packetIntervalTime);

    /**
     * \brief get packet interval time.
     * \return packet interval time.
     */
    std::string getPacketIntervalTime();
};

#endif /* UDPECHO_H */

