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
 * \brief the ping class is subclass of Application.
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
     * \brief Constructor which set default value.
     * \param _indice is the indice in the generator vector.
     * \param _senderNode is the sender node.
     * \param _receiverNode is the receiver node.
     * \param _startTime is the application start time.
     * \param _endTime is the application end time.
     */
    Ping(const size_t &_indice, const std::string &_senderNode, const std::string &_receiverNode, const size_t &_startTime, const size_t &_endTime);

    /**
     * \brief destructor.
     */
    ~Ping();

    /**
     * \brief function used to generate the headers.
     * \return the headers.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief function used to generate the application.
     * \param netDeviceContainer is the net device container name which are contain the sender node.
     * \param numberIntoNetDevice is the place of the machine into the net device container.
     * \return the application code.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice);
};

#endif /* PING_H */

