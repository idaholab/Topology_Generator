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
 * \brief ap link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef AP_H
#define AP_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief ap link subclass.
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
class ap : public Link
{
  public:
    /**
     * \brief Constructor.
     * \param _indice is the Ap number
     * \param _apNode is the node which is the ap name.
     */
    Ap(const size_t &_indice, const std::string &_apNode);

    /**
     * \brief Destructor.
     */
    virtual ~Ap();

  private:
    /**
     * \brief mobility attribute which say if station walk is constant (false) or random (false).
     */
    bool mobility;

    /**
     * \brief the ap name (ssid).
     */
    std::string apName;

    /**
     * \brief attribute which represent the wifi node name.
     */
    std::string apNode;

    /**
     * \brief function to get the ap node name.
     * \return the ap node name.
     */
    std::string getApNode();

    /**
     * \brief procedure to switch mobility on the connected station.
     * \param _mobility is a bool to apply mobility or not.
     */
    void setMobility(const bool &_mobility);

    /**
     * \brief procedure to set the ap name (ssid).
     * \param _apName is the new apName
     */
    void setApName(const std::string &_apName);

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
     * \brief function to generate the trace line.
     * \return the trace line.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* AP_H */

