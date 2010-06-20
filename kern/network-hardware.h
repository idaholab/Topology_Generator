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
 * \file network-hardware.h
 * \brief Link Base Class.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef NETWORKHARDWARE_H
#define NETWORKHARDWARE_H

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
 *  include "network-hardware.h"
 *  class LinkImpl : public NetworkHardware
 *  {
 *    LinkImpl(...);
 *    ~LinkImpl();
 *
 *    virtual std::vector<std::string> GenerateHeader();
 *    virtual std::vector<std::string> GenerateNetworkHardwareCpp();
 *    virtual std::vector<std::string> GenerateNetdeviceCpp();
 *    virtual std::vector<std::string> GenerateNetworkHardwarePython();
 *    virtual std::vector<std::string> GenerateNetdevicePython();
 *    # and if you need
 *    virtual std::vector<std::string> GenerateTraceCpp();
 *    virtual std::vector<std::string> GenerateTapBridgeCpp();
 *    virtual std::vector<std::string> GenerateVarsCpp();
 *    virtual std::vector<std::string> GenerateCmdLineCpp();
 *    virtual std::vector<std::string> GenerateTracePython();
 *    virtual std::vector<std::string> GenerateTapBridgePython();
 *    virtual std::vector<std::string> GenerateVarsPython();
 *    virtual std::vector<std::string> GenerateCmdLinePython();
 *  }
 */
class NetworkHardware
{
  private:
    /**
     * \brief Type of the link.
     */
    std::string m_type;

    /**
     * \brief Number of the link.
     */
    size_t m_indice;

    /**
     * \brief Link name.
     */
    std::string m_networkHardwareName;

    /**
     * \brief Data rate.
     */
    std::string m_dataRate;

    /**
     * \brief Link delay.
     */
    std::string m_networkHardwareDelay;

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

    /**
     * \brief Node name which are connected to the link.
     */
    std::vector<std::string> m_nodes;

  public:
    /**
     * \brief Constructor.
     * \param indice number of the link
     * \param type link type
     */
    NetworkHardware(const std::string &type, const size_t &indice);

    /**
     * \brief Destructor.
     */
    virtual ~NetworkHardware();

    /**
     * \brief Generate the headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief Generate link C++ code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwareCpp() = 0;

    /**
     * \brief Generate net device container C++ code.
     *
     * The net device container contain all nodes installed by the link.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDeviceCpp() = 0;

    /**
     * \brief Generate tap bridge C++ code.
     * \return tap bridge code
     */
    virtual std::vector<std::string> GenerateTapBridgeCpp();

    /**
     * \brief Generate vars C++ code.
     * \return vars code
     */
    virtual std::vector<std::string> GenerateVarsCpp();

    /**
     * \brief Generate cmd line C++ code.
     * \return cmd line code
     */
    virtual std::vector<std::string> GenerateCmdLineCpp();

    /**
     * \brief Generate trace line C++ code.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTraceCpp();

    /**
     * \brief Generate link python code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateNetworkHardwarePython() = 0;

    /**
     * \brief Generate net device container python code.
     *
     * The net device container contain all nodes installed by the link.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevicePython() = 0;

    /**
     * \brief Generate tap bridge python code.
     * \return tap bridge code
     */
    virtual std::vector<std::string> GenerateTapBridgePython();

    /**
     * \brief Generate vars python code.
     * \return vars code
     */
    virtual std::vector<std::string> GenerateVarsPython();

    /**
     * \brief Generate cmd line python code.
     * \return cmd line code
     */
    virtual std::vector<std::string> GenerateCmdLinePython();

    /**
     * \brief Generate trace line python code.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTracePython();

    /**
     * \brief Get link number.
     * \return link number
     */
    std::string GetIndice();

    /**
     * \brief Set link number.
     * \param indice new indice
     */
    void SetIndice(const size_t &indice);

    /**
     * \brief Get link name.
     * \return link name
     */
    std::string GetNetworkHardwareName();

    /**
     * \brief Get link data rate.
     * \return link data rate
     */
    std::string GetDataRate();

    /**
     * \brief Get link delay (in ms).
     * \return link delay
     */
    std::string GetNetworkHardwareDelay();

    /**
     * \brief Get net device container name.
     * \return net device container name
     */
    std::string GetNdcName();

    /**
     * \brief Get attached nodes list.
     * \return node list
     */
    std::vector<std::string> GetInstalledNodes();

    /**
     * \brief Get n node.
     * \param i index from Get node
     */
    std::string GetInstalledNode(const size_t &i);

    /**
     * \brief Remove installed selected node.
     * \param nb remove node index
     */
    void removeInstalledNode(const size_t &nb);

    /**
     * \brief Set link rate.
     * \param linkName new link name
     */
    void SetNetworkHardwareName(const std::string &linkName);

    /**
     * \brief Set data rate in bps.
     * \param dataRate new data rate
     */
    void SetDataRate(const std::string &dataRate);

    /**
     * \brief Set link delay in millisecond.
     * \param linkDelay new link delay
     */
    void SetNetworkHardwareDelay(const std::string &linkDelay);

    /**
     * \brief Set net device container name.
     * \param ndcName new net device container name
     */
    void SetNdcName(const std::string &ndcName);

    /**
     * \brief Install node on link.
     * \param node new node to add
     */
    void Install(const std::string &node);

    /**
     * \brief Group all link installed nodes.
     * \return all nodes
     */
    std::vector<std::string> GroupAsNodeContainerCpp();

    /**
     * \brief Group all link installed nodes.
     * \return all nodes
     */
    std::vector<std::string> GroupAsNodeContainerPython();

    /**
     * \brief Get all node container name.
     * \return node container name
     */
    std::string GetAllNodeContainer();
    
    /**
     * \brief Set name of all node container.
     * \param allNodeContainer all node container
     */
    void SetAllNodeContainer(const std::string &allNodeContainer);

    /**
     * \brief Enable/disable tracing.
     * \param state trace state
     */
    void SetTrace(const bool &state);

    /**
     * \brief Get tracing mod.
     * \return trace mod
     */
    bool GetTrace();

    /**
     * \brief Enable/disable tracing in promiscious state.
     * \param state promisc state
     */
    void SetPromisc(const bool &state);

    /**
     * \brief Get promisc mod.
     * \return promisc mod
     */
    bool GetPromisc();

    /**
     * \brief Get the link type
     * \return link type
     */
    std::string GetLinkType();
};

#endif /* NETWORKHARDWARE_H */

