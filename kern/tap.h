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
 * \brief tap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef TAP_H
#define TAP_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief tap link subclass.
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
class Tap : public Link
{
  private:
    /**
     * \brief tap name attribute.
     */
    std::string tapNode;

    /**
     * \brief tap interface name.
     */
    std::string ifaceName;

  public:
    /**
     * \brief constructor.
     * \param m_indice tap number
     * \param m_tapNode external linux host
     * \param m_ifaceName iface name
     */
    Tap(const size_t &m_indice, const std::string &m_tapNode, const std::string &m_ifaceName);

    /**
     * \brief destructor.
     */
    virtual ~Tap();

    /**
     * \brief get tap node name.
     * \return tap name
     */   
    std::string getTapName();

    /**
     * \brief set tap node name.
     * \param m_tapNode new tap name.
     */
    void setTapName(const std::string &m_tapNode);

    /**
     * \brief get interface name.
     * \return interface name. 
     */
    std::string getIfaceName();

    /**
     * \brief set interface name.
     * \param m_ifaceName new interface name.
     */
    void setIfaceName(const std::string &m_ifaceName);

    /**
     * \brief generate headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief generate link code.
     * \return link code.
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief generate net device container code.
     * \return net device container code.
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief function re-writted from link main class.
     * \return tap bridge code.
     */
    std::vector<std::string> GenerateTapBridge();

    /**
     * \brief function re-writted from link main class.
     * \return vars code.
     */
    std::vector<std::string> GenerateVars();

    /**
     * \brief function re-wrotted from link main class.
     * \return cmd line code.
     */
    std::vector<std::string> GenerateCmdLine();
};

#endif /* TAP_H */

