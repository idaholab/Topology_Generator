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
 *  include "link.h"
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
  private:
    /**
     *\brief number of the link.
     */
    size_t indice;

    /**
     * \brief link name.
     */
    std::string linkName;

    /**
     * \brief data rate.
     */
    std::string dataRate;

    /**
     * \brief link delay.
     */
    std::string linkDelay;

    /**
     * \brief node device container name.
     */
    std::string ndcName;

    /**
     * \brief name of the node container group.
     */
    std::string allNodeContainer;

    /**
     * \brief enable/disable trafic.
     */
    bool enableTrace;

    /**
     * \brief promisciuous trace.
     */
    bool tracePromisc;

  public:
    /**
     * \brief constructor.
     * 
     * \param m_indice number of the link
     */
    Link(const size_t &m_indice);

    /**
     * \brief destructor.
     */
    virtual ~Link();

    /**
     * \brief generate the headers code.
     * \return headers code.
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief generate link code.
     * \return link code.
     */
    virtual std::vector<std::string> GenerateLink() = 0;

    /**
     * \brief generate net device container code.
     * The net device container contain all nodes installed by the link.
     * \return net device container code.
     */
    virtual std::vector<std::string> GenerateNetDevice() = 0;

    /**
     * \brief generate tap bridge code.
     * \return tap bridge code.
     */
    virtual std::vector<std::string> GenerateTapBridge();

    /**
     * \brief generate vars code.
     * \return vars code.
     */
    virtual std::vector<std::string> GenerateVars();

    /**
     * \brief generate cmd line code.
     * \return cmd line code.
     */
    virtual std::vector<std::string> GenerateCmdLine();

    /**
     * \brief generate trace line code.
     * \return trace line code.
     */
    virtual std::vector<std::string> GenerateTrace();

    /**
     * \brief get link number.
     * \return link number.
     */
    std::string getIndice();

    /**
     * \brief set link number.
     * \param m_indice new indice.
     */
    void setIndice(const size_t &m_indice);

    /**
     * \brief get link name.
     * \return link name.
     */
    std::string getLinkName();

    /**
     * \brief get link data rate.
     * \return link data rate.
     */
    std::string getDataRate();

    /**
     * \brief get link delay.
     *  (in ms)
     * \return link delay.
     */
    std::string getLinkDelay();

    /**
     * \brief get net device container name.
     * \return net device container name.
     */
    std::string getNdcName();

    /**
     * \brief get attached nodes list.
     * \return node list.
     */
    std::vector<std::string> getNodes();

    /**
     * \brief set link rate.
     * \param m_linkName new link name.
     */
    void setLinkName(const std::string &m_linkName);

    /**
     * \brief set data rate.
     * \param m_dataRate new data rate.
     */
    void setDataRate(const std::string &m_dataRate);

    /**
     * \brief set link delay.
     * \param m_linkDelay new link delay.
     */
    void setLinkDelay(const std::string &m_linkDelay);

    /**
     *\brief set net device container name.
     * \param m_ndcName new net device container name.
     */
    void setNdcName(const std::string &m_ndcName);

    /**
     * \brief install node on link.
     * \param m_node new node to add.
     */
    void Install(const std::string &m_node);

    /**
     * \brief group all link installed nodes.
     * \return all nodes.
     */
    std::vector<std::string> GroupAsNodeContainer();

    /**
     * \brief get all node container name.
     * \return node container name.
     */
    std::string getAllNodeContainer();
    
    /**
     * \brief set name of all node container.
     * \param m_allNodeContainer all node container.
     */
    void setAllNodeContainer(const std::string &m_allNodeContainer);

    /**
     * \brief enable/disable tracing.
     * \param m_state trace state.
     */
    void setTrace(const bool &m_state);

    /**
     * \brief get tracing mod.
     * \return trace mod.
     */
    bool getTrace();

    /**
     * \brief enable/disable tracing in promiscious state.
     * \param m_state promisc state.
     */
    void setPromisc(const bool &m_state);

    /**
     * \brief get promisc mod.
     * \return promisc mod.
     */
    bool getPromisc();

    /**
     * \brief node name which are connected to the link.
     */
    std::vector<std::string> nodes;

};

#endif /* LINK_H */

