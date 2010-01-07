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
 * \file bridge.h
 * \brief Bridge link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include "network-hardware.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Bridge link subclass.
 *
 *  The bridge class is a subclass of link.
 *
 *  This class represent a bridge.
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an bridge with generator object.
 *    - Install nodes with install method.
 */
class Bridge : public NetworkHardware
{
  private:
    /**
     * \brief Bridge node name.
     */
    std::string m_nodeBridge;

  public:
    /**
     * \brief Constructor.
     * \param indice bridge number
     * \param nodeBridge node name
     * \param type link type
     */
    Bridge(const std::string &type, const size_t &indice, const std::string &nodeBridge);

    /**
     * \brief Destructor.
     */
    virtual ~Bridge();

    /**
     * \brief Get bridge node name.
     * \return node name
     */
    std::string GetNodeBridge();
    
    /**
     * \brief Set bridge node name.
     * \param nodeBridge new node name
     */
    void SetNodeBridge(const std::string &nodeBridge);

    /**
     * \brief Generate headers.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate build link C++ code.
     * \return build link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwareCpp();

    /**
     * \brief Generate build of the net device container for C++.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDeviceCpp();

    /**
     * \brief Generate trace line for C++.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTraceCpp();
    
    /**
     * \brief Generate build link python code.
     * \return build link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwarePython();

    /**
     * \brief Generate build of the net device container for python.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevicePython();

    /**
     * \brief Generate trace line for python.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTracePython();
};

#endif /* BRIDGE_H */

