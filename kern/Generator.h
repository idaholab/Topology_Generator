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
 * \file Generator.h
 * \brief The main class of the Generator.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "Node.h"
#include "Link.h"
#include "Application.h"


#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The main class of the Generator.
 *
 * This class is the main class from the generation of simulation.
 * It containt the main method to generate the code for the simulation.
 * 
 */
class Generator
{
  public:
    /**
     * \brief the simulation name.
     */
    std::string simulationName;

    /**
     * \brief the configuration list.
     */
    std::vector<std::string> listConfiguration;

    /**
     * \brief Procedure to add a config line.
     * \param config
     */
    void AddConfig(const std::string &config);

    /**
     * \brief the generator of the class Generator.
     * \param _simulationName
     */
    Generator(const std::string &_simulationName);

    /**
     * \brief the destructor of the class.
     */
    ~Generator();	

    //
    // Part of Node.
    //
  private:
    /**
     * \brief number attribute of Pc Node created.
     */
    size_t indiceNodePc;

    /**
     * \brief number attribute of Router Node created.
     */
    size_t indiceNodeRouter;

    /**
     * \brief number attribute of Ap Node created.
     */
    size_t indiceNodeAp;

    /**
     * \brief number attribute of Station Node created.
     */
    size_t indiceNodeStation;

    /**
     * \brief number attribute of Bridge Node created.
     */
    size_t indiceNodeBridge;

    /**
     * \brief number attribute of Tap Node created.
     */
    size_t indiceNodeTap;

    /**
     * \brief number attribute of Emu Node created.
     */
    size_t indiceNodeEmu;

  public: 
    /**
     * \brief list of Node created instace.
     * 
     * This attribute is the list of the created instance of Node.
     * 
     */
    std::vector<Node*> listNode;

    /**
     * \brief Procedure used to add an Node.
     * 
     * This procedure is used to add an Node. It add the Node to the
     * vector listNode and increment the number of Node.
     * 
     * \param type the type of the Node. (Pc, Hub, Switch,...)
     */
    void AddNode(const std::string &type);

    /**
     * \brief see AddNode(*).
     * \param type
     * \param number the nuber which will be added.
     */
    void AddNode(const std::string &type, const size_t &number);


    /**
     * \brief Procedure used to remove an Node elem.
     * \param name the Node name to remove
     */
    void RemoveNode(const std::string &name);

    /**
     * \brief Procedure used to remove an Node elem.
     * \param index index of the node to remove
     */
    void RemoveNode(size_t index);

    //
    // Part of Application.
    //
  private:
    /**
     * \brief number attribute of Ping application created.
     */
    size_t indiceApplicationPing; 

    /**
     * \brief number attribute of Tcp large transfert application created.
     */
    size_t indiceApplicationTcpLargeTransfer;

    /**
     * \brief number attribute of Udp echo application created.
     */
    size_t indiceApplicationUdpEcho;

  public:

    /**
     * \brief list of application created instace.
     * 
     * This attribute is the list of the created instance of application.
     * 
     */
    std::vector<Application*> listApplication;

    /**
     * \brief Procedure used to add an appplication.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type the type of the application. (Ping, TcpLargeTransfert, Udp_Echo ...)
     * \param senderNode
     * \param receiverNode
     * \param startTime
     * \param endTime
     * \param port
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime, const size_t &port);

    /**
     * \brief Procedure used to add an appplication.
     * 
     * This procedure is used to add an procedure. It add the application to the
     * vector listApplication and increment the number of application.
     * 
     * \param type the type of the application. (Ping, TcpLargeTransfert, Udp_Echo ...)
     * \param senderNode
     * \param receiverNode
     * \param startTime
     * \param endTime
     */
    void AddApplication(const std::string &type, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime);

    /**
     * \brief Procedure used to remove an application elem.
     * \param name the application name to remove
     */
    void RemoveApplication(const std::string &name);

    //
    // Part of Link.
    //
  private:
    /**
     * \brief number attribute of Ap link created.
     */
    size_t indiceLinkAp;


    /**
     * \brief number attribute of Emu link created.
     */
    size_t indiceLinkEmu;

    /**
     * \brief number attribute of PointToPoint link created.
     */
    size_t indiceLinkPointToPoint;

    /**
     * \brief number attribute of Tap link created.
     */
    size_t indiceLinkTap;

    /**
     * \brief number attribute of Hub link created.
     */
    size_t indiceLinkHub;

    /**
     * \brief number attribute of Bridge link created.
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
     * \brief Procedure used to add an link.
     * 
     * This procedure is used to add an link. It add the link to the
     * vector listLink and increment the number of link.
     * 
     * \param type the type of the link. (PointToPoint, Csma,...)
     */
    void AddLink(const std::string &type);

    /**
     * \brief See the procedure AddLink(*).
     * 
     * \param type
     * \param linkNode
     */
    void AddLink(const std::string &type, const std::string &linkNode);

    /**
     * \brief See the procedure AddLink(*).
     * 
     * \param type
     * \param linkNode
     * \param ifaceName
     */
    void AddLink(const std::string &type, const std::string &linkNode, const std::string &ifaceName);

    /**
     * \brief Procedure used to remove an link elem.
     * \param name the link name to remove
     */
    void RemoveLink(const std::string &name);

    /**
     * \brief Procedure used to remove an link elem.
     * \param index index of the link to remove
     */
    void RemoveLink(size_t index);

    //
    // Part around the code Generation.
    // This part is looking about the code to write.
    // 
  public:
    /**
     * \brief Procedure wich are the main code generator.
     * 
     * This procedure is the main procedure to generate the code from the simulation.
     * It also go to use all the procedure on the bottom like generate all headers, ...
     * 
     */
    void GenerateCode();

  private:
    /**
     * \brief Function which return all headers to use.
     * 
     * This function return a string wich contain all c++ header without duplicate.
     * 
     * \return header 
     */
    std::vector<std::string> GenerateHeader();

    /**
     * \brief Function which return all variables used.
     * 
     * This function return a string wich contain all c++ vars.
     * 
     * \return header 
     */
    std::vector<std::string> GenerateVars();


    /**
     * \brief Function which return all command line c++ code.
     * 
     * \return command line 
     */
    std::vector<std::string> GenerateCmdLine();


    /**
     * \brief Function which return a string with the config option.
     * 
     * \return generated config
     */
    std::vector<std::string> GenerateConfig();


    /**
     * \brief Function which return a string with all c++ node code.
     *
     * \return generated node
     */
    std::vector<std::string> GenerateNode();


    /**
     * \brief Function which return a string with all c++ link code.
     * 
     * \return generated link
     */
    std::vector<std::string> GenerateLink();


    /**
     * \brief Function which return a string with all c++ net device code.
     * 
     * \return generated net device
     */
    std::vector<std::string> GenerateNetDevice();


    /**
     * \brief Function which return a string with all c++ ip stack code.
     * 
     * \return generated ip stack 
     */
    std::vector<std::string> GenerateIpStack();


    /**
     * \brief Function which return a string with all c++ ip assign code.
     * 
     * \return generated ip assign
     */
    std::vector<std::string> GenerateIpAssign();

    /**
     * \brief Function which return a string with all c++ tap bridge code.
     * 
     * \return generated tab bridge
     */
    std::vector<std::string> GenerateTapBridge();


    /**
     * \brief Function which return string with all c++ route code.
     * 
     * \return generated route
     */
    std::vector<std::string> GenerateRoute();


    /**
     * \brief Function which return string with all c++ application code.
     * 
     * \return generated application
     */
    std::vector<std::string> GenerateApplication();

    /**
     * \brief Function to generate the pcap trace application code.
     * 
     * \return generate trace
     */
    std::vector<std::string> GenerateTrace();

    //
    // XML generation operation part.
    //
  private: 

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
  private:

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
  private:  

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

