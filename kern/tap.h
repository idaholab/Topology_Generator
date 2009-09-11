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
  public:
    /**
     * \brief Constructor.
     * \param _indice is the tap number
     * \param _tapNode is the external linux host
     * \param _ifaceName is the iface name
     */
    Tap(const size_t &_indice, const std::string &_tapNode, const std::string &_ifaceName);

    /**
     * \brief Destructor.
     */
    virtual ~Tap();

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
     * \brief function to get the tap node name.
     * \return the tap name
     */   
    std::string getTapName();

    /**
     * \brief function to get the interface name.
     * \return the interface name. 
     */
    std::string getIfaceName();

    /**
     * \brief function which return the generated headers.
     * \return the headers.
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
     * \brief function re-writted from link main class.
     * \return the tap bridge code.
     */
    std::vector<std::string> GenerateTapBridge();

    /**
     * \brief function re-writted from link main class.
     * \return the vars code.
     */
    std::vector<std::string> GenerateVars();

    /**
     * \brief function re-wrotted from link main class.
     * \return the cmd line code.
     */
    std::vector<std::string> GenerateCmdLine();
};

#endif /* TAP_H */

