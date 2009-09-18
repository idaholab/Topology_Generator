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
 * \brief Link Base Class.
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
     * \brief Number of the link.
     */
    size_t m_indice;

    /**
     * \brief Link name.
     */
    std::string m_linkName;

    /**
     * \brief Data rate.
     */
    std::string m_dataRate;

    /**
     * \brief Link delay.
     */
    std::string m_linkDelay;

    /**
     * \brief Node device container name.
     */
    std::string m_ndcName;

    /**
     * \brief Name of the node container group.
     */
    std::string m_allNodeContainer;

    /**
     * \brief Enable/disable trafic.
     */
    bool m_enableTrace;

    /**
     * \brief Promisciuous trace.
     */
    bool m_tracePromisc;

  public:
    /**
     * \brief Constructor.
     * \param indice number of the link
     */
    Link(const size_t &indice);

    /**
     * \brief Destructor.
     */
    virtual ~Link();

    /**
     * \brief Generate the headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief Generate link code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateLink() = 0;

    /**
     * \brief Generate net device container code.
     *
     * The net device container contain all nodes installed by the link.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevice() = 0;

    /**
     * \brief Generate tap bridge code.
     * \return tap bridge code
     */
    virtual std::vector<std::string> GenerateTapBridge();

    /**
     * \brief Generate vars code.
     * \return vars code
     */
    virtual std::vector<std::string> GenerateVars();

    /**
     * \brief Generate cmd line code.
     * \return cmd line code
     */
    virtual std::vector<std::string> GenerateCmdLine();

    /**
     * \brief Generate trace line code.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTrace();

    /**
     * \brief Get link number.
     * \return link number
     */
    std::string getIndice();

    /**
     * \brief Set link number.
     * \param indice new indice
     */
    void setIndice(const size_t &indice);

    /**
     * \brief Get link name.
     * \return link name
     */
    std::string getLinkName();

    /**
     * \brief Get link data rate.
     * \return link data rate
     */
    std::string getDataRate();

    /**
     * \brief Get link delay (in ms).
     * \return link delay
     */
    std::string getLinkDelay();

    /**
     * \brief Get net device container name.
     * \return net device container name
     */
    std::string getNdcName();

    /**
     * \brief Get attached nodes list.
     * \return node list
     */
    std::vector<std::string> getNodes();

    /**
     * \brief Set link rate.
     * \param linkName new link name
     */
    void setLinkName(const std::string &linkName);

    /**
     * \brief Set data rate.
     * \param dataRate new data rate
     */
    void setDataRate(const std::string &dataRate);

    /**
     * \brief Set link delay.
     * \param linkDelay new link delay
     */
    void setLinkDelay(const std::string &linkDelay);

    /**
     * \brief Set net device container name.
     * \param ndcName new net device container name
     */
    void setNdcName(const std::string &ndcName);

    /**
     * \brief Install node on link.
     * \param node new node to add
     */
    void Install(const std::string &node);

    /**
     * \brief Group all link installed nodes.
     * \return all nodes
     */
    std::vector<std::string> GroupAsNodeContainer();

    /**
     * \brief Get all node container name.
     * \return node container name
     */
    std::string getAllNodeContainer();
    
    /**
     * \brief Set name of all node container.
     * \param allNodeContainer all node container
     */
    void setAllNodeContainer(const std::string &allNodeContainer);

    /**
     * \brief Enable/disable tracing.
     * \param state trace state
     */
    void setTrace(const bool &state);

    /**
     * \brief Get tracing mod.
     * \return trace mod
     */
    bool getTrace();

    /**
     * \brief Enable/disable tracing in promiscious state.
     * \param state promisc state
     */
    void setPromisc(const bool &state);

    /**
     * \brief Get promisc mod.
     * \return promisc mod
     */
    bool getPromisc();

    /**
     * \brief Node name which are connected to the link.
     */
    std::vector<std::string> nodes;
};

#endif /* LINK_H */

