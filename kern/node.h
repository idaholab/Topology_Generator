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
 * \file node.h
 * \brief Node base class.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Node base class.
 *
 *  The node class represent the nodes.
 *  You can create here différents node type :
 *    - pc
 *    - router
 *    - ap
 *    - station (wifi)
 *    - bridge
 *    - tap
 *    - emu
 *
 *  If you see node named as links, it is totaly normal.
 *  The different links need sometimes an node to be created in ns3.
 */
class Node 
{
  private:
    /**
     * \brief Node number.
     */
    size_t m_indice;

    /**
     * \brief Node name.
     */
    std::string m_nodeName;

    /**
     * \brief Ip interface name. 
     */
    std::string m_ipInterfaceName;

    /**
     * \brief Nsc use.
     */
    std::string m_nsc;

    /**
     * \brief Number of machines.
     */
    size_t m_machinesNumber;

    /**
     * \brief Node type.
     */
    std::string m_type;

  public:
    /**
     * \brief Constructor.
     * \param indice number of the node
     * \param type type of the node (pc, router, ...)
     * \param namePrefix the prefix name of the node
     * \param machinesNumber number of machine to create
     */
    Node(const size_t &indice, const std::string &type, const std::string &namePrefix, const size_t &machinesNumber);

    /**
     * \brief Destructor.
     */
    ~Node();

    /**
     * \brief Generate headers code.
     * This function return a vector which contain the header lines from the specified object
     * \return headers code
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate node C++ code.
     * This function return a vector which contain the declaration and instanciation of the node
     * \return node code
     */
    std::vector<std::string> GenerateNodeCpp();

    /**
     * \brief Generate IP stack C++ code.
     * This function return a vector which contain the c++ code from the Ipv4 stack declaration and instanciation
     * \return IP stack code.
     */
    std::vector<std::string> GenerateIpStackCpp();

    /**
     * \brief Generate node python code.
     * This function return a vector which contain the declaration and instanciation of the node
     * \return node code
     */
    std::vector<std::string> GenerateNodePython();

    /**
     * \brief Generate IP stack python code.
     * This function return a vector which contain the c++ code from the Ipv4 stack declaration and instanciation
     * \return IP stack code.
     */
    std::vector<std::string> GenerateIpStackPython();

    /**
     * \brief Set node name.
     * \param nodeName node name
     */
    void SetNodeName(const std::string &nodeName);

    /**
     * \brief Set ip interface name.
     *
     * This procedure is used to the the ipInterfaceName.
     * Sometimes this var is used in application like as UdpEcho.
     * \param ipInterfaceName ip interface name
     */
    void SetIpInterfaceName(const std::string &ipInterfaceName);

    /**
     * \brief Get node name.
     * \return node name
     */
    std::string GetNodeName();

    /**
     * \brief Get node name.
     * \param number machine number
     * \return node name
     */
    std::string GetNodeName(const size_t &number);

    /**
     * \brief Get ip interface name.
     * \return IP interface name
     */
    std::string GetIpInterfaceName();

    /**
     * \brief Get indice.
     * \return indice
     */
    std::string GetIndice();

    /**
     * \brief Set indice.
     * \param indice new indice
     */
    void SetIndice(const size_t &indice);

    /**
     * \brief Get NSC (Network Simulation Cradle) code.
     * \return nsc code
     */
    std::string GetNsc();

    /**
     * \brief Set NSC (Network Simulation Cradle) code.
     * \param nsc new nsc code
     */
    void SetNsc(const std::string &nsc);

    /**
     * \brief Get machines number.
     * \return machines number
     */
    size_t GetMachinesNumber();

    /**
     * \brief Set machines number.
     * \param machinesNumber new machines number
     */
    void SetMachinesNumber(const size_t machinesNumber);

    /**
     * \brief Get node type.
     * \return type the node type
     */
    std::string GetNodeType();
};

#endif /* NODE_H */

