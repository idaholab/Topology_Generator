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
  public:
    /**
     * \brief constructor.
     * \param _indice is the tap number
     * \param _emuNode is the link node name
     * \param _ifaceName is the iface name
     */
    Emu(const size_t &_indice, const std::string &_emuNode, const std::string &_ifaceName);

    /**
     * \brief destructor.
     */
    virtual ~Emu();

  private:
    /**
     * \brief emu node name attribute.
     */
    std::string emuNode;

    /**
     * \brief interface name attribute.
     */
    std::string ifaceName;

  public:
    /**
     * \brief function to get the emu node name.
     * \return the emu node name.
     */
    std::string getEmuName();

    /**
     * \brief function to get the emu interface name.
     * \return the interface name.
     */
    std::string getIfaceName();

    /**
     * \brief function which return the generated headers.
     * \return the generated headers.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief function which generate the build link code.
     * \return the build link code.
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief function which return the build of the net device container.
     * \return the net device container.
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief function rewritted from main class. Please see main class.
     * \return the vars code.
     */
    std::vector<std::string> GenerateVars();

    /**
     * \brief function rewritted from main class. Please see main class.
     * \return the cmd line code.
     */
    std::vector<std::string> GenerateCmdLine();

    /**
     * \brief function to generate the trace line.
     * \return the trace line.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* EMU_H */

