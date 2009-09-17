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
 * \brief bridge link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief bridge link subclass.
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
class Bridge : public Link
{
  private:
    /**
     * \brief bridge node name.
     */
    std::string nodeBridge;

  public:
    /**
     * \brief constructor.
     * \param m_indice bridge number
     * \param m_nodeBridge node name.
     */
    Bridge(const size_t &m_indice, const std::string &m_nodeBridge);

    /**
     * \brief destructor.
     */
    virtual ~Bridge();

    /**
     * \brief get bridge node name.
     * \return node name.
     */
    std::string getNodeBridge();
    
    /**
     * \brief set bridge node name.
     * \param m_nodeBridge new node name.
     */
    void setNodeBridge(const std::string &m_nodeBridge);

    /**
     * \brief generate headers.
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
     * \brief generate trace line.
     * \return trace line code.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* BRIDGE_H */

