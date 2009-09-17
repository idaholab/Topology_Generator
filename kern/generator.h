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
#include "link.h"
#include "application.h"


#include <iostream>
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
 *      gen->AddLink(std::string("Hub"));// or ap, bridge, ....
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
     * \brief simulation name.
     */
    std::string simulationName;

    /**
     * \brief configuration list.
     */
    std::vector<std::string> listConfiguration;

    /**
     * \brief add a config line.
     * \param config new config to add to config list.
     */
    void AddConfig(const std::string &config);

    /**
     * \brief constructor.
     * \param m_simulationName simulation name.
     */
    Generator(const std::string &m_simulationName);

    /**
     * \brief destructor.
     */
    ~Generator();	

    //
    // Part of Node.
    //
  private:
    /**
     * \brief number attribute of term node created.
     */
    size_t indiceNodePc;

    /**
     * \brief number attribute of router node created.
     */
    size_t indiceNodeRouter;

    /**
     * \brief number attribute of ap node created.
     */
    size_t indiceNodeAp;

    /**
     * \brief number attribute of station node created.
     */
    size_t indiceNodeStation;

    /**
     * \brief number attribute of bridge node created.
     */
    size_t indiceNodeBridge;

    /**
     * \brief number attribute of tap node created.
     */
    size_t indiceNodeTap;

    /**
     * \brief number attribute of emu node created.
     */
    size_t indiceNodeEmu;

  public: 
    /**
     * \brief list of node created instance.
     * 
     * This attribute is the list of the created instance of node.
     * 
     */
    std::vector<Node*> listNode;

    /**
     * \brief add an node.
     * 
     * This used to add an node. It add the node to the
     * vector listNode and increment the number of node.
     * 
     * \param type node type. (pc, hub, switch,...)
     */
    void AddNode(const std::string &type);

    /**
     * \brief add an node group.
     * \param type node type.
     * \param number number which will be added.
     */
    void AddNode(const std::string &type, const size_t &number);

    /**
     * \brief remove an node element.
     * \param name node name to remove.
     */
    void RemoveNode(const std::string &name);

    /**
     * \brief remove an node element.
     * \param index node index to be removed.
     */
    void RemoveNode(size_t index);

    //
    // Part of Application.
    //
  private:
    /**
     * \brief number attribute of ping application created.
     */
    size_t indiceApplicationPing; 

    /**
     * \brief number attribute of tcp large transfert application created.
     */
    size_t indiceApplicationTcpLargeTransfer;

    /**
     * \brief number attribute of udp echo application created.
     */
    size_t indiceApplicationUdpEcho;

  public:

    /**
     * \brief list of application created instance.
     * 
     * This attribute is the list of the created instance of application.
     */
    std::vector<Application*> listApplication;

    /**
     * \brief add an appplication.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type type of the application. (ping, tcp-large-transfert, udp-echo ...)
     * \param senderNode sender node.
     * \param receiverNode receiver node.
     * \param startTime start time.
     * \param endTime end time.
     * \param port port.
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port);

    /**
     * \brief add an application.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type the type of the application. (ping, tcp-large-transfert, udp-echo ...)
     * \param senderNode sender node.
     * \param receiverNode receiver node.
     * \param startTime start time.
     * \param endTime end time.
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime);

    /**
     * \brief remove an application element.
     * \param name application name to remove
     */
    void RemoveApplication(const std::string &name);

    //
    // Part of Link.
    //
  private:
    /**
     * \brief number attribute of ap link created.
     */
    size_t indiceLinkAp;

    /**
     * \brief number attribute of emu link created.
     */
    size_t indiceLinkEmu;

    /**
     * \brief number attribute of point-to-point link created.
     */
    size_t indiceLinkPointToPoint;

    /**
     * \brief number attribute of tap link created.
     */
    size_t indiceLinkTap;

    /**
     * \brief number attribute of hub link created.
     */
    size_t indiceLinkHub;

    /**
     * \brief number attribute of bridge link created.
     */
    size_t indiceLinkBridge; 

  public:
    /**
     * \brief list of link created instace.
     * 
     * This attribute is the list of the created instance of link.
     * 
     */
    std::vector<Link*> listLink;

    /**
     * \brief add an link.
     * 
     * This procedure is used to add an link. It add the link to the
     * vector listLink and increment the number of link.
     * 
     * \param type type of the link. (point-to-point, csma,...)
     */
    void AddLink(const std::string &type);

    /**
     * \brief add link and his linkNode.
     * 
     *  Example, an Ap, must have an ap node to be generated.  
     *
     * \param type link type.
     * \param linkNode node name.
     */
    void AddLink(const std::string &type, const std::string &linkNode);

    /**
     * \brief add link with her linkNode and ifaceName.
     * 
     * \param type link type.
     * \param linkNode node name.
     * \param ifaceName iface name.
     */
    void AddLink(const std::string &type, const std::string &linkNode, const std::string &ifaceName);

    /**
     * \brief remove an link element.
     * \param name link name to remove.
     */
    void RemoveLink(const std::string &name);

    /**
     * \brief remove an link element.
     * \param index index of the link to remove
     */
    void RemoveLink(size_t index);

    //
    // Part around the code Generation.
    // This part is looking about the code to write.
    // 
    
    /**
     * \brief generate ns3 code.
     * 
     * This procedure is the main procedure to generate the code from the simulation.
     * It also go to use all the procedure on the bottom like generate all headers, ...
     * 
     */
    void GenerateCode();

  private:
    /**
     * \brief generate headers code.
     * 
     * This function return a string wich contain all c++ header without duplicate.
     * 
     * \return headers code. 
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief generate vars code.
     * 
     * This function return a string wich contain all c++ vars.
     * 
     * \return vars code. 
     */
    std::vector<std::string> GenerateVars();


    /**
     * \brief generate command line code.
     * 
     * \return commend line code.
     */
    std::vector<std::string> GenerateCmdLine();


    /**
     * \brief generate config code.
     * 
     * \return config code.
     */
    std::vector<std::string> GenerateConfig();


    /**
     * \brief generate node declaration code.
     *
     * \return declaration code.
     */
    std::vector<std::string> GenerateNode();


    /**
     * \brief generate link code.
     * 
     * \return link code.
     */
    std::vector<std::string> GenerateLink();


    /**
     * \brief generate net device code.
     * 
     * \return net device code.
     */
    std::vector<std::string> GenerateNetDevice();


    /**
     * \brief generate ip stack declaration.
     * 
     * \return ip stack code.
     */
    std::vector<std::string> GenerateIpStack();


    /**
     * \brief generate ip assign code.
     * 
     * \return ip assign code.
     */
    std::vector<std::string> GenerateIpAssign();

    /**
     * \brief generate tap bridge code.
     * 
     * \return tab bridge code.
     */
    std::vector<std::string> GenerateTapBridge();


    /**
     * \brief generate route code.
     * 
     * \return route code.
     */
    std::vector<std::string> GenerateRoute();


    /**
     * \brief generate application code.
     * 
     * \return application code.
     */
    std::vector<std::string> GenerateApplication();

    /**
     * \brief generate trace code.
     * 
     * \return trace code.
     */
    std::vector<std::string> GenerateTrace();

    //
    // XML generation operation part.
    //

    /**
     * \brief xml file name atribute.
     * 
     * This file name is used to export the current simulation into xml to save it.
     */
    std::string xmlFileName;

    /**
     * \brief function which return the attribute xml file name.
     *
     * \return xml file name
     */
    std::string getXmlFileName();

    /**
     * \brief procedure which set the xml file name.
     *
     * \param _xmlFileName the new xml file name.
     */
    void setXmlFileName(const std::string &_xmlFileName );

    /**
     * \brief Procedure wich write the simulation into xml file.
     * 
     * \param _line the line to add to the xml file.
     */
    void WriteXml(const std::string &_line);

    /**
     * \brief procedure wich open and print graphicaly the xml file.
     */
    void OpenXml();

    //
    // Cpp generation operation part.
    //

    /**
     * \brief attribute which are the name of the c++ output file name.
     */  
    std::string cppFileName;

    /**
     * \brief function which return the c++ output file name.
     * 
     * \return c++ file name
     */
    std::string getCppFileName();

    /**
     * \brief procedure to set the c++ file name.
     * 
     * \param _cppFileName the new c++ file name
     */
    void setCppFileName(const std::string &_cppFileName);

    /**
     * \brief Procedure to write c++ code into the attribute file name.
     * 
     * \param _line the new line to add to the attribute file name.
     */
    void WriteCpp(const std::string &_line);

    //
    // Python generation operation part.
    //

    /**
     * \brief Attribute which are the name of the python output file.
     */
    std::string pyFileName;

    /**
     * \brief Function which return the python artribute name.
     * 
     * \return python file name
     */
    std::string getPyFileName();

    /**
     * \brief Procedure used to set the python file name attribute.
     * 
     * \param _pyFileName the new python file name.
     */
    void setPyFileName(const std::string &_pyFileName);

    /**
     * \brief Procedure to write python code into the attribute file name.
     * 
     * \param _line the line to be writted. 
     */
    void WritePython(const std::string &_line);
};

#endif /* GENERATOR_H */

