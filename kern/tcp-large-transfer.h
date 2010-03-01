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
 * \file tcp-large-transfer.h
 * \brief The tcp large transfer echo class subclass of Application.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef TCPLARGETRANSFER_H
#define TCPLARGETRANSFER_H

#include "application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The tcp large transfer echo subclass from Application.
 *
 *  This class represent a tcp large transfer application.
 *  It generate large tcp trafic between sender node and receiver node
 *
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an application with tcp-large-transfert param.
 */
class TcpLargeTransfer : public Application
{
  private:
    /**
     * \brief TCP port.
     */
    size_t m_port;

  public:
    /**
     * \brief Constructor.
     * \param type application type
     * \param indice number of the application on the generator applicaiton vector
     * \param senderNode sender node
     * \param receiverNode receiver node
     * \param startTime application start time
     * \param endTime application end time
     * \param port port which are sended the traffic
     */
    TcpLargeTransfer(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port);

    /**
     * \brief Destructor.
     */
    ~TcpLargeTransfer();

    /**
     * \brief Generate headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate application C++ code.
     * \param netDeviceContainer net device container
     * \param numberIntoNetDevice number of the sender node into the net device container
     * \return the ns3 application code
     */
    virtual std::vector<std::string> GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice);

    /**
     * \brief Generate application python code.
     * \param netDeviceContainer net device container
     * \param numberIntoNetDevice number of the sender node into the net device container
     * \return the ns3 application code
     */
    virtual std::vector<std::string> GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice);

    /**
     * \brief Get port.
     * \return port.
     */
    size_t GetPort();

    /**
     * \brief Set port.
     * \param port new port
     */
    void SetPort(const size_t &port);
};

#endif /* TCPLARGETRANSFER_H */

