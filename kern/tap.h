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
 * \file tap.h
 * \brief Tap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef TAP_H
#define TAP_H

#include "network-hardware.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Tap link subclass.
 *
 *  The tap class is a subclass of link.
 *
 *  This class represent an tap node.
 *
 *  +----------+                                                                  
 *  | external |                                                                  
 *  |  Linux   |                                                                  
 *  |   Host   |                                                                  
 *  |          |
 *  | "mytap"  |                                                                  
 *  +----------+  
 *       |
 *    (host)
 *
 *  This is a special functionnalities of ns3.
 *  It create a new interface on the host machine
 *
 *  This class work as all link child.
 *  - Create it from generator object
 *  - Install node with Install method.
 */
class Tap : public NetworkHardware
{
  private:
    /**
     * \brief Tap name attribute.
     */
    std::string m_tapNode;

    /**
     * \brief Tap interface name.
     */
    std::string m_ifaceName;

  public:
    /**
     * \brief Constructor.
     * \param indice tap number
     * \param tapNode external linux host
     * \param ifaceName iface name
     * \param type link type
     */
    Tap(const std::string &type, const size_t &indice, const std::string &tapNode, const std::string &ifaceName);

    /**
     * \brief Destructor.
     */
    virtual ~Tap();

    /**
     * \brief Get tap node name.
     * \return tap name
     */   
    std::string GetTapName();

    /**
     * \brief Set tap node name.
     * \param tapNode new tap name
     */
    void SetTapName(const std::string &tapNode);

    /**
     * \brief Get interface name.
     * \return interface name
     */
    std::string GetIfaceName();

    /**
     * \brief Set interface name.
     * \param ifaceName new interface name
     */
    void SetIfaceName(const std::string &ifaceName);

    /**
     * \brief Generate headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate link C++ code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwareCpp();

    /**
     * \brief Generate net device container C++ code.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDeviceCpp();

    /**
     * \brief Function re-writted from link main class.
     * \return tap bridge code
     */
    std::vector<std::string> GenerateTapBridgeCpp();

    /**
     * \brief Function re-writted from link main class.
     * \return vars code
     */
    std::vector<std::string> GenerateVarsCpp();

    /**
     * \brief Function re-wrotted from link main class.
     * \return cmd line code
     */
    std::vector<std::string> GenerateCmdLineCpp();
    
    /**
     * \brief Function re-writted from link main class.
     * \return tap bridge code
     */
    std::vector<std::string> GenerateTapBridgePython();

    /**
     * \brief Function re-writted from link main class.
     * \return vars code
     */
    std::vector<std::string> GenerateVarsPython();

    /**
     * \brief Function re-wrotted from link main class.
     * \return cmd line code
     */
    std::vector<std::string> GenerateCmdLinePython();
    
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
};

#endif /* TAP_H */

