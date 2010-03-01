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
 * \file ap.h
 * \brief Ap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef AP_H
#define AP_H

#include "network-hardware.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Ap link subclass.
 *
 *  The ap class is a subclass of link.
 * 
 *  This class represent an wifi access point.
 *  It re-writte some methods which are called to generate the ns3 code.  
 *  
 *  Usage:
 *    - Create an ap with generator object.
 *    - Install nodes (wifi station) with install method.
 */
class Ap : public NetworkHardware
{
  private:
    /**
     * \brief Mobility attribute which say if station walk is constant (false) or random (false).
     */
    bool m_mobility;

    /**
     * \brief Ap name (ssid).
     */
    std::string m_apName;

    /**
     * \brief Wifi node name.
     */
    std::string m_apNode;

  public:
    /**
     * \brief Constructor.
     * \param indice the Ap number
     * \param apNode the node which is the ap name
     * \param type the link type
     */
    Ap(const std::string &type, const size_t &indice, const std::string &apNode);

    /**
     * \brief Destructor.
     */
    virtual ~Ap();

    /**
     * \brief Switch mobility on the connected station.
     * \param mobility bool to apply mobility or not
     */
    void SetMobility(const bool &mobility);

    /**
     * \brief Get mobility.
     * \return mobility
     */
    bool GetMobility();

    /**
     * \brief Get the ap node name.
     * \return ap node name
     */
    std::string GetApNode();

    /**
     * \brief Set ap node.
     * \param apNode new ap node
     */
    void SetApNode(const std::string &apNode);

    /**
     * \brief Get ap name.
     * \return ap name
     */
    std::string GetApName();

    /**
     * \brief Set the ap name (ssid).
     * \param apName the new apName
     */
    void SetApName(const std::string &apName);

    /**
     * \brief Generate headers.
     * \return headers
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate the build link C++ code.
     * \return build link code.
     */
    virtual std::vector<std::string> GenerateNetworkHardwareCpp();

    /**
     * \brief Generate build of the net device container C++ code.
     * \return net device container
     */
    virtual std::vector<std::string> GenerateNetDeviceCpp();

    /**
     * \brief Generate the trace line C++ code.
     * \return trace line
     */
    virtual std::vector<std::string> GenerateTraceCpp();
    
    /**
     * \brief Generate link python code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwarePython();

    /**
     * \brief Generate net device container python code.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevicePython();

    /**
     * \brief Generate trace line python code.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTracePython();
};

#endif /* AP_H */

