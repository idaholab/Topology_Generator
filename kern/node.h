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
     * \brief attribute which represent the node number.
     */
    size_t indice;

    /**
     * \brief attribute which represent the node name.
     */
    std::string nodeName;

    /**
     * \brief attribute which represent the ip interface name. 
     */
    std::string ipInterfaceName;

    /**
     * \brief attribute which represent the nsc use.
     */
    std::string nsc;

    /**
     * \brief attribute which represent the number of machines.
     */
    size_t machinesNumber;

  public:

    /**
     * \brief Constructor.
     * \param _indice is the number of the node.
     * \param _type is the type of the node (pc, router, ...)
     * \param _machinesNumber is the number of machine to create
     */
    Node(const size_t &_indice, const std::string &_type, const size_t &_machinesNumber);

    /**
     * \brief Destructor.
     */
    ~Node();

    /**
     * \brief function wich return the c++ header code from node.
     * This function return a vector which contain the header lines from the specified object.
     * \return the header.
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief function wich return the c++ code from node.
     * This function return a vector which contain the declaration and instanciation of the node.
     * \return the node code.
     */
    std::vector<std::string> GenerateNode();

    /**
     * \brief function wich return the c++ code from IpStack.
     * This function return a vector which contain the c++ code from the Ipv4 stack declaration and instanciation.
     * \return the ipStack code.
     */
    std::vector<std::string> GenerateIpStack();

    /**
     * \brief procedure to set the node name.
     * \param _nodeName is the string which contain the node name.
     */
    void setNodeName(const std::string &_nodeName);


    /**
     * \brief procedure to set the Ip interface name.
     * This procedure is used to the the ipInterfaceName. 
     * Sometimes this var is used in application like as UdpEcho.
     * \param _ipInterfaceName is the ip interface name.
     */
    void setIpInterfaceName(const std::string &_ipInterfaceName);

    /**
     * \brief function wich return the node name.
     * \return the node name.
     */
    std::string getNodeName();

    /**
     * \brief function wich return the node name.
     * \param number
     * \return the node name.
     */
    std::string getNodeName(const size_t &number);

    /**
     * \brief function wich return the name of the Ip interface.
     * \return the ip interface name.
     */
    std::string getIpInterfaceName();

    /**
     * \brief function wich return the node number.
     * \return the node number in type string.
     */
    std::string getIndice();

    /**
     * \brief function to get the NSC (Network Simulation Cradle) use.
     * \return the nsc string declaration
     */
    std::string getNsc();

    /**
     * \brief procedure to set the NSC (Network Simulation Cradle) use.
     * \param _nsc is the new nsc declaration
     */
    void setNsc(const std::string &_nsc);

    /**
     * \brief function to get the number of machines contained in the node.
     * \return the number of machines
     */
    size_t getMachinesNumber();

    /**
     * \brief procedure to set the machines number.
     * \param _machinesNumber is the new machines number.
     */
    void setMachinesNumber(const size_t &_machinesNumber);
};

#endif /* NODE_H */

