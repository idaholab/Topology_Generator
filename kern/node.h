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
 * \brief node base class.
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
 * \brief node base class.
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
     * \brief node number.
     */
    size_t indice;

    /**
     * \brief node name.
     */
    std::string nodeName;

    /**
     * \brief ip interface name. 
     */
    std::string ipInterfaceName;

    /**
     * \brief nsc use.
     */
    std::string nsc;

    /**
     * \brief number of machines.
     */
    size_t machinesNumber;

  public:

    /**
     * \brief constructor.
     * \param m_indice number of the node.
     * \param m_type type of the node (pc, router, ...)
     * \param m_machinesNumber number of machine to create
     */
    Node(const size_t &m_indice, const std::string &m_type, const size_t &m_machinesNumber);

    /**
     * \brief destructor.
     */
    ~Node();

    /**
     * \brief generate headers code.
     * This function return a vector which contain the header lines from the specified object.
     * \return headers code.
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief generate node code.
     * This function return a vector which contain the declaration and instanciation of the node.
     * \return node code.
     */
    std::vector<std::string> GenerateNode();

    /**
     * \brief generate ip stack code.
     * This function return a vector which contain the c++ code from the Ipv4 stack declaration and instanciation.
     * \return ip stack code.
     */
    std::vector<std::string> GenerateIpStack();

    /**
     * \brief set node name.
     * \param m_nodeName node name.
     */
    void setNodeName(const std::string &m_nodeName);

    /**
     * \brief set ip interface name.
     * This procedure is used to the the ipInterfaceName. 
     * Sometimes this var is used in application like as UdpEcho.
     * \param m_ipInterfaceName ip interface name.
     */
    void setIpInterfaceName(const std::string &m_ipInterfaceName);

    /**
     * \brief get node name.
     * \return node name.
     */
    std::string getNodeName();

    /**
     * \brief get node name.
     * \param number machine number.
     * \return node name.
     */
    std::string getNodeName(const size_t &number);

    /**
     * \brief get ip interface name.
     * \return ip interface name.
     */
    std::string getIpInterfaceName();

    /**
     * \brief get indice.
     * \return indice.
     */
    std::string getIndice();

    /**
     * \brief set indice.
     * \param m_indice new indice.
     */
    void setIndice(const size_t &m_indice);

    /**
     * \brief get NSC (Network Simulation Cradle) code.
     * \return nsc code.
     */
    std::string getNsc();

    /**
     * \brief set NSC (Network Simulation Cradle) code.
     * \param m_nsc new nsc code
     */
    void setNsc(const std::string &m_nsc);

    /**
     * \brief get machines number.
     * \return machines number.
     */
    size_t getMachinesNumber();

    /**
     * \brief set machines number.
     * \param m_machinesNumber new machines number.
     */
    void setMachinesNumber(const size_t &m_machinesNumber);
};

#endif /* NODE_H */

