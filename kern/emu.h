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
 * \brief emu link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef EMU_H
#define EMU_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief emu link subclass.
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
 *     (device on host system, set to promiscuous mode)
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
class Emu : public Link
{
  private:
    /**
     * \brief emu node name.
     */
    std::string emuNode;

    /**
     * \brief interface name.
     */
    std::string ifaceName;

  public:
    /**
     * \brief constructor.
     * \param m_indice tap number
     * \param m_emuNode link node name
     * \param m_ifaceName iface name
     */
    Emu(const size_t &m_indice, const std::string &m_emuNode, const std::string &m_ifaceName);

    /**
     * \brief destructor.
     */
    virtual ~Emu();

    /**
     * \brief get emu node name.
     * \return emu node name.
     */
    std::string getEmuName();

    /**
     * \brief set emu node name.
     * \param m_nodeName new emu node name.
     */
    void setEmuName(const std::string &m_nodeName);

    /**
     * \brief get emu interface name.
     * \return interface name.
     */
    std::string getIfaceName();

    /**
     * \brief set emu iface name.
     * \param m_ifaceName new emu iface name.
     */
    void setIfaceName(const std::string &m_ifaceName);

    /**
     * \brief generate headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief generate build link code.
     * \return build link code.
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief generate build of the net device container.
     * \return net device container code.
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief rewritted from main class. Please see main class.
     * \return vars code.
     */
    std::vector<std::string> GenerateVars();

    /**
     * \brief rewritted from main class. Please see main class.
     * \return cmd line code.
     */
    std::vector<std::string> GenerateCmdLine();

    /**
     * \brief generate the trace line.
     * \return trace line.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* EMU_H */

