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
 * \file emu.h
 * \brief Emu link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef EMU_H
#define EMU_H

#include "network-hardware.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Emu link subclass.
 *
 *  The emu class is a subclass of link.
 *
 *  This class represent an emu node.
 *
 *  emu schema:
 *   ------------
 *   |  node    |
 *   |          |
 *   |  ---     |
 *   | |   |    |
 *   | |emu|    |
 *   | |   |    |
 *   |  ---     |
 *   |   |      |
 *   ----|-------
 *       |
 *     (device on host system, Set to promiscuous mode)
 *       |
 *      --------- (Interface network) -------
 *
 *  This class represent also a special link which connect to a real interface.
 *  This interface is the host real interface like eth0.
 *
 *  It re-writte some methods which are called to generate the ns3 code.  
 *
 *  Usage:
 *    - Create an emu link with generator object.
 *    - Install nodes with install method.
 */
class Emu : public NetworkHardware
{
  private:
    /**
     * \brief Emu node name.
     */
    std::string m_emuNode;

    /**
     * \brief Interface name.
     */
    std::string m_ifaceName;

  public:
    /**
     * \brief Constructor.
     * \param indice tap number
     * \param emuNode link node name
     * \param ifaceName iface name
     * \param type link type
     */
    Emu(const std::string &type, const size_t &indice, const std::string &emuNode, const std::string &ifaceName);

    /**
     * \brief Destructor.
     */
    virtual ~Emu();

    /**
     * \brief Get emu node name.
     * \return emu node name
     */
    std::string GetEmuName();

    /**
     * \brief Set emu node name.
     * \param nodeName new emu node name
     */
    void SetEmuName(const std::string &nodeName);

    /**
     * \brief Get emu interface name.
     * \return interface name
     */
    std::string GetIfaceName();

    /**
     * \brief Set emu iface name.
     * \param ifaceName new emu iface name
     */
    void SetIfaceName(const std::string &ifaceName);

    /**
     * \brief Generate headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate build link C++ code.
     * \return build link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwareCpp();

    /**
     * \brief Generate build of the net device container C++ code.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDeviceCpp();

    /**
     * \brief Rewritted from base class.
     * \return vars code
     * \see Link
     */
    std::vector<std::string> GenerateVarsCpp();

    /**
     * \brief Rewritted from base class.
     * \return cmd line code
     * \see Link
     */
    virtual std::vector<std::string> GenerateCmdLineCpp();

    /**
     * \brief Generate the trace line C++ code.
     * \return trace line
     */
    virtual std::vector<std::string> GenerateTraceCpp();
    
    /**
     * \brief Generate build link python code.
     * \return build link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwarePython();

    /**
     * \brief Generate build of the net device container python code.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevicePython();

    /**
     * \brief Rewritted from base class.
     * \return vars code
     * \see Link
     */
    std::vector<std::string> GenerateVarsPython();

    /**
     * \brief Rewritted from base class.
     * \return cmd line code
     * \see Link
     */
    virtual std::vector<std::string> GenerateCmdLinePython();

    /**
     * \brief Generate the trace line python code.
     * \return trace line
     */
    virtual std::vector<std::string> GenerateTracePython();
};

#endif /* EMU_H */

