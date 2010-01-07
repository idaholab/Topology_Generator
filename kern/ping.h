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
 * \file ping.h
 * \brief The ping class is subclass of Application.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef PING_H
#define PING_H

#include "application.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The Ping subclass from Application.
 *
 *  The ping class is a subclass of application.
 *
 *  This class represent a ping application.
 *  An ICMP Echo Request and an ICMP Echo Reply.
 *
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an application with ping type.
 */
class Ping : public Application
{
  public:
    /**
     * \brief Constructor.
     * \param type application type
     * \param indice indice in the generator vector
     * \param senderNode sender node
     * \param receiverNode receiver node
     * \param startTime application start time
     * \param endTime application end time
     */
    Ping(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime);

    /**
     * \brief Destructor.
     */
    ~Ping();

    /**
     * \brief Generate the headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate the application C++ code.
     * \param netDeviceContainer net device container name which are contain the sender node
     * \param numberIntoNetDevice place of the machine into the net device container
     * \return application code
     */
    virtual std::vector<std::string> GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice);
    
    /**
     * \brief Generate the application python code.
     * \param netDeviceContainer net device container name which are contain the sender node
     * \param numberIntoNetDevice place of the machine into the net device container
     * \return application code
     */
    virtual std::vector<std::string> GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice);
};

#endif /* PING_H */

