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
 * \file generator.h
 * \brief The main class of the Generator.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "node.h"
#include "network-hardware.h"
#include "application.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The main class of the Generator.
 *
 *  The Generator class is the main class of the kern folder.
 *  It is used for call all the classes you can found here.
 *  
 *  This class works around three vector which contain Nodes, Links and Applications.
 *  
 *  Usage example:
 *    - create an Generator object,
 *      Generator *gen = new Generator(std::string("Simulation Name"));
 *    - add nodes,
 *      gen->AddNode(std::string("Pc"));// or router, wifi station, ...
 *    - add links,
 *      gen->AddNetworkHardware(std::string("Hub"));// or ap, bridge, ....
 *    - connect nodes to link,
 *      gen->(link)->Install(Node name);
 *    - add applications,
 *      gen->AddApplication(std::string("Ping"), senderNodeName, receiverNodeName, startTime, endTime);
 *
 *    You can see all examples of all implementation into kern/examples/ folder.
 */
class Generator
{
  public:
    /**
     * \brief Constructor.
     * \param simulationName simulation name
     */
    Generator(const std::string &simulationName);

    /**
     * \brief Destructor.
     */
    ~Generator();	

    /**
     * \brief Add a config line.
     * \param config new config to add to config list
     */
    void AddConfig(const std::string &config);

    /**
     * \brief Add an node.
     * 
     * This used to add an node. It add the node to the
     * vector listNode and increment the number of node.
     * 
     * \param type node type. (pc, hub, switch,...)
     */
    void AddNode(const std::string &type);

    /**
     * \brief Add an node group.
     * \param type node type
     * \param number number which will be added
     */
    void AddNode(const std::string &type, const size_t number);

    /**
     * \brief Remove an node element.
     * \param name node name to remove
     */
    void RemoveNode(const std::string &name);

    /**
     * \brief Remove an node element.
     * \param index node index to be removed
     */
    void RemoveNode(const size_t index);

    /**
     * \brief Get node at specified index.
     * \param index index
     * \return node pointer
     */
    Node* GetNode(const size_t index);

    /**
     * \brief Get number of nodes.
     * \return number of nodes.
     */
    size_t GetNNodes() const;

    /**
     * \brief Add an appplication.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type type of the application. (ping, tcp-large-transfert, udp-echo ...)
     * \param senderNode sender node
     * \param receiverNode receiver node
     * \param startTime start time
     * \param endTime end time
     * \param port port
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port);

    /**
     * \brief Add an application.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type the type of the application. (ping, tcp-large-transfert, udp-echo ...)
     * \param senderNode sender node
     * \param receiverNode receiver node
     * \param startTime start time
     * \param endTime end time
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime);

    /**
     * \brief Remove an application element.
     * \param name application name to remove
     */
    void RemoveApplication(const std::string &name);

    /**
     * \brief Get application element at specified index.
     * \param index index
     * \return application pointer
     */
    Application* GetApplication(const size_t index);

    /**
     * \brief Get number of applications.
     * \return number of applications
     */
    size_t GetNApplications() const; 

    /**
     * \brief Add an link.
     * 
     * This procedure is used to add an link. It add the link to the
     * vector listLink and increment the number of link.
     * 
     * \param type type of the link. (point-to-point, csma,...)
     */
    void AddNetworkHardware(const std::string &type);

    /**
     * \brief Add link and his linkNode.
     * 
     *  Example, an Ap, must have an ap node to be generated.  
     *
     * \param type link type
     * \param linkNode node name
     */
    void AddNetworkHardware(const std::string &type, const std::string &linkNode);

    /**
     * \brief Add link with her linkNode and ifaceName.
     * 
     * \param type link type
     * \param linkNode node name
     * \param ifaceName iface name
     */
    void AddNetworkHardware(const std::string &type, const std::string &linkNode, const std::string &ifaceName);

    /**
     * \brief Remove an link element.
     * \param name link name to remove
     */
    void RemoveNetworkHardware(const std::string &name);

    /**
     * \brief Remove an link element.
     * \param index index of the link to remove
     */
    void RemoveNetworkHardware(const size_t index);

    /**
     * \brief Get link at specified index.
     * \param index index
     * \return link pointer
     */
    NetworkHardware* GetNetworkHardware(const size_t index);

    /**
     * \brief Get number of links.
     * \return number of links
     */
    size_t GetNNetworkHardwares() const;

    /**
     * \brief Generate ns-3 C++ code.
     * 
     * This procedure is the main procedure to generate the code from the simulation.
     * It also go to use all the procedure on the bottom like generate all headers, ...
     */
    void GenerateCodeCpp(std::string fileName = "");

    /**
     * \brief Generate ns-3 python code.
     * 
     * This procedure is the main procedure to generate the code from the simulation.
     * It also go to use all the procedure on the bottom like generate all headers, ...
     */
    void GenerateCodePython(std::string fileName = "");

  private:
    /**
     * \brief Simulation name.
     */
    std::string m_simulationName;

    /**
     * \brief Configuration list.
     */
    std::vector<std::string> m_listConfiguration;

    /**
     * \brief Number attribute of term node created.
     */
    size_t m_indiceNodePc;

    /**
     * \brief Number attribute of router node created.
     */
    size_t m_indiceNodeRouter;

    /**
     * \brief Number attribute of ap node created.
     */
    size_t m_indiceNodeAp;

    /**
     * \brief Number attribute of station node created.
     */
    size_t m_indiceNodeStation;

    /**
     * \brief Number attribute of bridge node created.
     */
    size_t m_indiceNodeBridge;

    /**
     * \brief Number attribute of tap node created.
     */
    size_t m_indiceNodeTap;

    /**
     * \brief Number attribute of emu node created.
     */
    size_t m_indiceNodeEmu;

    /**
     * \brief List of node created instance.
     * 
     * This attribute is the list of the created instance of node.
     */
    std::vector<Node*> m_listNode;

    /**
     * \brief List of application created instance.
     * 
     * This attribute is the list of the created instance of application.
     */
    std::vector<Application*> m_listApplication;

    /**
     * \brief List of link created instace.
     * 
     * This attribute is the list of the created instance of link.
     */
    std::vector<NetworkHardware*> m_listNetworkHardware;

    /**
     * \brief Number attribute of ping application created.
     */
    size_t m_indiceApplicationPing; 

    /**
     * \brief Number attribute of tcp large transfert application created.
     */
    size_t m_indiceApplicationTcpLargeTransfer;

    /**
     * \brief Number attribute of udp echo application created.
     */
    size_t m_indiceApplicationUdpEcho;

    /**
     * \brief Number attribute of ap link created.
     */
    size_t m_indiceNetworkHardwareAp;

    /**
     * \brief Number attribute of emu link created.
     */
    size_t m_indiceNetworkHardwareEmu;

    /**
     * \brief Number attribute of point-to-point link created.
     */
    size_t m_indiceNetworkHardwarePointToPoint;

    /**
     * \brief Number attribute of tap link created.
     */
    size_t m_indiceNetworkHardwareTap;

    /**
     * \brief Number attribute of hub link created.
     */
    size_t m_indiceNetworkHardwareHub;

    /**
     * \brief Number attribute of bridge link created.
     */
    size_t m_indiceNetworkHardwareBridge; 

    //
    // C++ code generation operation part
    //

    /**
     * \brief Generate headers code.
     * 
     * This function return a string wich contain all C++ header without duplicate.
     * 
     * \return headers code
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate vars C++ code.
     * 
     * This function return a string wich contain all C++ vars.
     * \return vars code
     */
    std::vector<std::string> GenerateVarsCpp();

    /**
     * \brief Generate command line C++ code.
     * \return commend line code
     */
    std::vector<std::string> GenerateCmdLineCpp();

    /**
     * \brief Generate config C++ code.
     * \return config code
     */
    std::vector<std::string> GenerateConfigCpp();

    /**
     * \brief Generate node declaration C++ code.
     * \return declaration code
     */
    std::vector<std::string> GenerateNodeCpp();

    /**
     * \brief Generate link C++ code.
     * \return link code
     */
    std::vector<std::string> GenerateNetworkHardwareCpp();

    /**
     * \brief Generate net device C++ code.
     * \return net device code
     */
    std::vector<std::string> GenerateNetDeviceCpp();

    /**
     * \brief Generate ip stack declaration.
     * \return IP stack code
     */
    std::vector<std::string> GenerateIpStackCpp();

    /**
     * \brief Generate ip assign C++ code.
     * \return IP assign code
     */
    std::vector<std::string> GenerateIpAssignCpp();

    /**
     * \brief Generate tap bridge C++ code.
     * \return tab bridge code
     */
    std::vector<std::string> GenerateTapBridgeCpp();

    /**
     * \brief Generate route C++ code.
     * \return route code
     */
    std::vector<std::string> GenerateRouteCpp();

    /**
     * \brief Generate application C++ code.
     * \return application code
     */
    std::vector<std::string> GenerateApplicationCpp();

    /**
     * \brief Generate trace C++ code.
     * \return trace code
     */
    std::vector<std::string> GenerateTraceCpp();

    //
    // Python code generation operation part
    //

    /**
     * \brief Generate vars python code.
     * 
     * This function return a string wich contain all python vars.
     * 
     * \return vars code
     */
    std::vector<std::string> GenerateVarsPython();

    /**
     * \brief Generate command line python code.
     * \return commend line code
     */
    std::vector<std::string> GenerateCmdLinePython();

    /**
     * \brief Generate config python code.
     * \return config code
     */
    std::vector<std::string> GenerateConfigPython();

    /**
     * \brief Generate node declaration python code.
     * \return declaration code
     */
    std::vector<std::string> GenerateNodePython();

    /**
     * \brief Generate link python code.
     * \return link code
     */
    std::vector<std::string> GenerateNetworkHardwarePython();

    /**
     * \brief Generate net device python code.
     * \return net device code
     */
    std::vector<std::string> GenerateNetDevicePython();

    /**
     * \brief Generate ip stack declaration.
     * \return IP stack code
     */
    std::vector<std::string> GenerateIpStackPython();

    /**
     * \brief Generate ip assign python code.
     * \return IP assign code
     */
    std::vector<std::string> GenerateIpAssignPython();

    /**
     * \brief Generate tap bridge python code.
     * \return tab bridge code
     */
    std::vector<std::string> GenerateTapBridgePython();

    /**
     * \brief Generate route python code.
     * \return route code
     */
    std::vector<std::string> GenerateRoutePython();

    /**
     * \brief Generate application python code.
     * \return application code
     */
    std::vector<std::string> GenerateApplicationPython();

    /**
     * \brief Generate trace python code.
     * \return trace code
     */
    std::vector<std::string> GenerateTracePython();

    //
    // C++ generation operation part.
    //

    /**
     * \brief Name of the C++ output file name.
     */  
    std::ofstream m_cppFile;

    /**
     * \brief Write C++ code into the attribute file name.
     * \param line the new line to add to the attribute file name
     */
    void WriteCpp(const std::string &line);

    //
    // Python generation operation part.
    //

    /**
     * \brief Name of the python output file name.
     */
    std::ofstream m_pyFile;

    /**
     * \brief Write python code into the output file name.
     * \param line the line to be writted 
     */
    void WritePython(const std::string &line);
};

#endif /* GENERATOR_H */

