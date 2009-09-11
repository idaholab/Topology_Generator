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
 * \file link.h
 * \brief link Base Class.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <string>
#include <vector>


/**
 * \ingroup generator
 * \brief This is the link class.
 *
 *  The link class is the main class of all links.
 *
 *  Usage : (Call a subclass)
 *    - ap
 *    - bridge
 *    - emu
 *    - hub
 *    - point-to-point
 *    - tap
 *
 *  To add a new link, please see the subclass for example.
 *  example of .h file :
 *
 *  #include "link.h"
 *  class new-class : public Link
 *  {
 *    new-class(...);
 *    ~new-class();
 *
 *    virtual std::vector<std::string> GenerateHeader();
 *    virtual std::vector<std::string> GenerateLink();
 *    virtual std::vector<std::string> GenerateNetdevice();
 *    # and if you need
 *    virtual std::vector<std::string> GenerateTrace();
 *    virtual std::vector<std::string> GenerateTapBridge();
 *    virtual std::vector<std::string> GenerateVars();
 *    virtual std::vector<std::string> GenerateCmdLine();
 *  }
 */
class Link
{
  protected:
    /**
     *\brief number of the link.
     */
    size_t indice;

    /**
     * \brief attribute which represent the link name.
     */
    std::string linkName;

    /**
     * \brief attribute which represent the data rate.
     */
    std::string dataRate;

    /**
     * \brief attribute which represent the link delay.
     */
    std::string linkDelay;

    /**
     * \brief attribute which represent the node device container name.
     */
    std::string ndcName;

    /**
     * \brief attribute used to save the name of the node container group.
     */
    std::string allNodeContainer;

    /**
     * \brief attribute which represent enable/disable trafic.
     */
    bool enableTrace;

    /**
     * \brief attribute which represent the promisciuous trace.
     */
    bool tracePromisc;

  public:
    /**
     * \brief Constructor.
     * 
     * \param _indice is the number of the link
     */
    Link(const size_t &_indice);

    /**
     * \brief Destructor.
     */
    virtual ~Link();

    /**
     * \brief function used to generate the headers.
     * \return the headers.
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief function used to generate the c++ code of the link build.
     * \return the build link.
     */
    virtual std::vector<std::string> GenerateLink() = 0;

    /**
     * \brief function used to generate the net device container.
     * The net device container contain all nodes installed by the link.
     * \return the net device container.
     */
    virtual std::vector<std::string> GenerateNetDevice() = 0;

    /**
     * \brief function used to generate the tap bridge.
     * \return the tap bridge code.
     */
    virtual std::vector<std::string> GenerateTapBridge();

    /**
     * \brief function used to generate the vars.
     * \return the vars code.
     */
    virtual std::vector<std::string> GenerateVars();

    /**
     * \brief function used to generate the cmd lines.
     * \return the cmd line code.
     */
    virtual std::vector<std::string> GenerateCmdLine();

    /**
     * \brief function to generate the trace line.
     * \return the trace line.
     */
    virtual std::vector<std::string> GenerateTrace();

    /**
     * \brief function to get the link number.
     * \return the link number.
     */
    std::string getIndice();

    /**
     * \brief function to get link name.
     * \return the link name.
     */
    std::string getLinkName();

    /**
     * \brief function to get the link data rate.
     * \return the link data rate.
     */
    std::string getDataRate();

    /**
     * \brief function to get the link delay.
     * Represented in ms.
     * \return the link delay.
     */
    std::string getLinkDelay();

    /**
     * \brief function to get the Net device container name.
     * \return the net device container name.
     */
    std::string getNdcName();

    /**
     * \brief function to get the attached nodes list.
     * \return the node list.
     */
    std::vector<std::string> getNodes();

    /**
     * \brief procedure tu set the link rate.
     * \param _linkName is the new link name.
     */
    void setLinkName(const std::string &_linkName);

    /**
     * \brief procedure to set the data rate.
     * \param _dataRate is the new data rate.
     */
    void setDataRate(const std::string &_dataRate);

    /**
     * \brief procedure to set the link delay.
     * \param _linkDelay is the new link delay.
     */
    void setLinkDelay(const std::string &_linkDelay);

    /**
     *\brief procedure to set the net device container name.
     * \param _ndcName is the new net device container name.
     */
    void setNdcName(const std::string &_ndcName);

    /**
     * \brief procedure to add attached to the link node.
     * \param _node is the new node to add.
     */
    void Install(const std::string &_node);

    /**
     * \brief function to convert size_t to string.
     * \param nbr is the number to convert.
     * \return the string of the number.
     */
    std::string toString(const size_t &nbr);

    /**
     * \brief function use to group all the nodes.
     * \return a vector with all nodes.
     */
    std::vector<std::string> GroupAsNodeContainer();

    /**
     * \brief function to get the node all node container name.
     * \return the node container name.
     */
    std::string getAllNodeContainer();

    /**
     * \brief attribute which represent the node name which are connected to the link.
     */
    std::vector<std::string> nodes;

/* procedure to be removed from this class, it just be used in Ap class. */
    /**
     * \brief see Ap class for more info.
     * \param _mobility
     */
    virtual void setMobility(const bool &_mobility);

    /**
     * \brief procedure to enable/disable tracing.
     * \param _state
     */
    void setTrace(const bool &_state);

    /**
     * \brief procedure to enable/disable tracing in promiscious state.
     * \param _state
     */
    void setPromisc(const bool &_state);
};

#endif /* LINK_H */

