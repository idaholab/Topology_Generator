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
 * \file generator.cpp
 * \brief The main class of the generator.
 * \author Pierre Weiss
 * \date 2009
 */

#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "generator.h"
#include "node.h"
#include "hub.h"
#include "point-to-point.h"
#include "bridge.h"
#include "ap.h"
#include "ping.h"
#include "udp-echo.h"
#include "tcp-large-transfer.h"
#include "tap.h"
#include "emu.h"
#include "utils.h"

using utils::split;

Generator::Generator(const std::string &simulationName)
{
  this->m_simulationName = simulationName;

  /* Node. */
  this->m_indiceNodePc = 0;
  this->m_indiceNodeRouter = 0;
  this->m_indiceNodeAp = 0;
  this->m_indiceNodeStation = 0;
  this->m_indiceNodeBridge = 0;
  this->m_indiceNodeTap = 0;
  this->m_indiceNodeEmu = 0;

  /* Link */
  this->m_indiceNetworkHardwareAp = 0;
  this->m_indiceNetworkHardwareEmu = 0;
  this->m_indiceNetworkHardwarePointToPoint = 0;
  this->m_indiceNetworkHardwareTap = 0;
  this->m_indiceNetworkHardwareHub = 0;
  this->m_indiceNetworkHardwareBridge = 0;

  /* Application */
  this->m_indiceApplicationPing = 0; 
  this->m_indiceApplicationTcpLargeTransfer = 0;
  this->m_indiceApplicationUdpEcho = 0;

}

Generator::~Generator()
{
  /* Node */
  for(size_t i = 0; i < this->m_listNode.size(); i++)
  {
    delete this->m_listNode.at(i);
  }

  /* Link */
  for(size_t i = 0; i < this->m_listNetworkHardware.size(); i++)
  {
    delete this->m_listNetworkHardware.at(i);
  }

  /* Application */
  for(size_t i = 0; i < this->m_listApplication.size(); i++)
  {
    delete this->m_listApplication.at(i);
  }
}

void Generator::AddConfig(const std::string &config)
{
  bool isDuplicate = false;
  for(size_t i = 0; i < this->m_listConfiguration.size(); i++)
  {
    if(config == this->m_listConfiguration.at(i))
    {
      isDuplicate = true;
    }
  }
  if(!isDuplicate)
  {
    this->m_listConfiguration.push_back(config);
  }
}

//
// Part of Node.
//
void Generator::AddNode(const std::string &type) 
{
  size_t number = 1;
  Node *equi = NULL;

  // call to the right type constructor. 
  if(type == "Pc" || type == "Pc-group")
  {
    equi = new Node(this->m_indiceNodePc, type, std::string("term_"), number);
    this->m_indiceNodePc += 1;
  } 
  else if(type == "Router")
  {
    equi = new Node(this->m_indiceNodeRouter, type, std::string("router_"), number);
    this->m_indiceNodeRouter += 1;
  } 
  else if(type == "Ap")
  {
    equi = new Node(this->m_indiceNodeAp, type, std::string("ap_"), number);
    this->m_indiceNodeAp += 1;
  } 
  else if(type == "Station")
  {
    equi = new Node(this->m_indiceNodeStation, type, std::string("station_"), number);
    this->m_indiceNodeStation += 1;
  } 
  else if(type == "Bridge")
  {
    equi = new Node(this->m_indiceNodeBridge, type, std::string("bridge_"), number);
    this->m_indiceNodeBridge += 1;
  } 
  else if(type == "Tap")
  {
    equi = new Node(this->m_indiceNodeTap, type, std::string("tap_"), number);
    this->m_indiceNodeTap += 1;
  } 
  else if(type == "Emu")
  {
    equi = new Node(this->m_indiceNodeEmu, type, std::string("emu_"), number);
    this->m_indiceNodeEmu += 1;
  }

  if(equi)
  {
    this->m_listNode.push_back(equi);
  }
  else
  {
    throw std::logic_error("Add Node failed! (" + type + ") unknow.");
  }
}

void Generator::AddNode(const std::string &type, const size_t number) 
{
  Node *equi = NULL;

  // call to the right type constructor. 
  if(type == "Pc" || type == "Pc-group")
  {
    equi = new Node(this->m_indiceNodePc, type, std::string("term_"), number);
    this->m_indiceNodePc += 1;
  } 
  else if(type == "Router")
  {
    equi = new Node(this->m_indiceNodeRouter, type, std::string("router_"), number);
    this->m_indiceNodeRouter += 1;
  } 
  else if(type == "Ap")
  {
    equi = new Node(this->m_indiceNodeAp, type, std::string("ap_"), number);
    this->m_indiceNodeAp += 1;
  } 
  else if(type == "Station")
  {
    equi = new Node(this->m_indiceNodeStation, type, std::string("station_"), number);
    this->m_indiceNodeStation += 1;
  } 
  else if(type == "Bridge")
  {
    equi = new Node(this->m_indiceNodeBridge, type, std::string("bridge_"), number);
    this->m_indiceNodeBridge += 1;
  } 
  else if(type == "Tap")
  {
    equi = new Node(this->m_indiceNodeTap, type, std::string("tap_"), number);
    this->m_indiceNodeTap += 1;
  }
  else if(type == "Emu")
  {
    equi = new Node(this->m_indiceNodeEmu, type, std::string("emu_"), number);
    this->m_indiceNodeEmu += 1;
  }

  if(equi)
  {
    this->m_listNode.push_back(equi);
  }
  else
  {
    throw std::logic_error("Add Node failed! (" + type + ") unknow.");
  }
}


void Generator::RemoveNode(const std::string &name)
{
  size_t startNumber = this->m_listNode.size();
  for(size_t i = 0; i < this->m_listNode.size(); i++)
  {
    if(this->m_listNode.at(i)->GetNodeName() == name)
    {
      delete this->m_listNode[i];
      this->m_listNode.erase(this->m_listNode.begin() + i);
      break;
    }
  }
  size_t endNumber = this->m_listNode.size();
  if(startNumber == endNumber)
  {
    throw std::logic_error("Node remove failed! (" + name + ") not found.");
  }
}

void Generator::RemoveNode(const size_t index)
{
  if(this->m_listNode.size() < index)
  {
    throw std::out_of_range("Node remove failed ! (index not exists).");
    return;
  }
  
  delete this->m_listNode[index];
  this->m_listNode.erase(this->m_listNode.begin() + index);
}

Node* Generator::GetNode(const size_t index)
{
  if(this->m_listNode.size() < index)
  {
    throw std::out_of_range("Index does not exist.");
    return 0;
  }

  return this->m_listNode.at(index);
}

size_t Generator::GetNNodes() const
{
  return this->m_listNode.size();
}


//
// Part of Application.
//
void Generator::AddApplication(const std::string &type, const std::string &senderNode, 
    const std::string &receiverNode, const size_t &startTime, 
    const size_t &endTime, const size_t &port) 
{
  if(type == "UdpEcho")
  {
    UdpEcho *app = new UdpEcho(type, this->m_indiceApplicationUdpEcho, senderNode, receiverNode, startTime, endTime, port);
    this->m_indiceApplicationUdpEcho += 1;
    this->m_listApplication.push_back(app);
  }
  else if(type == "TcpLargeTransfer")
  {
    TcpLargeTransfer *app = new TcpLargeTransfer(type, this->m_indiceApplicationTcpLargeTransfer, senderNode, receiverNode, startTime, endTime, port);
    this->m_indiceApplicationTcpLargeTransfer += 1;
    this->m_listApplication.push_back(app);
  }
  else
  {
    throw std::logic_error("Application add failed.");
  }

}

void Generator::AddApplication(const std::string &type, const std::string &senderNode, 
    const std::string &receiverNode, const size_t &startTime, const size_t &endTime) 
{
  if(type == "Ping")
  {
    Ping *app = new Ping(type, this->m_indiceApplicationPing, senderNode, receiverNode, startTime, endTime);
    this->m_indiceApplicationPing += 1;
    this->m_listApplication.push_back(app);
  }
  else
  {
    throw std::logic_error("Application add failed.");
  } 
}

void Generator::RemoveApplication(const std::string &name)
{
  size_t startNumber = this->m_listApplication.size();
  for(size_t i = 0; i < this->m_listApplication.size(); i++)
  {
    if(this->m_listApplication.at(i)->GetAppName() == name)
    {
      delete this->m_listApplication[i];
      this->m_listApplication.erase(this->m_listApplication.begin() + i);
      break;
    }
  }
  size_t endNumber = this->m_listApplication.size();
  if(startNumber == endNumber)
  {
    throw std::logic_error("Application remove failed! (" + name + ") not found.");
  }
}

Application* Generator::GetApplication(const size_t index)
{
  if(this->m_listApplication.size() < index)
  {
    throw std::out_of_range("Index does not exist");
    return 0;
  }

  return this->m_listApplication.at(index);
}

size_t Generator::GetNApplications() const
{
  return this->m_listApplication.size();
}

//
// Part of Link.
//
void Generator::AddNetworkHardware(const std::string &type) 
{
  // call to the right type constructor. 
  if(type == "Hub")
  {
    Hub *link = new Hub(type, this->m_indiceNetworkHardwareHub);
    this->m_indiceNetworkHardwareHub += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else if(type == "PointToPoint")
  {
    PointToPoint *link = new PointToPoint(type, this->m_indiceNetworkHardwarePointToPoint);
    this->m_indiceNetworkHardwarePointToPoint += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. ( " + type + ") not found.");
  }
}

void Generator::AddNetworkHardware(const std::string &type, const std::string &linkNode) 
{
  if(type == "Bridge")
  {
    Bridge *link = new Bridge(type, this->m_indiceNetworkHardwareBridge, linkNode);
    this->m_indiceNetworkHardwareBridge += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else if(type == "Ap")
  {
    Ap *link = new Ap(type, this->m_indiceNetworkHardwareAp, linkNode);
    this->m_indiceNetworkHardwareAp += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. (" + type + ") not found.");
  }
}

void Generator::AddNetworkHardware(const std::string &type, const std::string &linkNode, const std::string &ifaceName)
{ 
  if(type == "Emu")
  {
    Emu *link = new Emu(type, this->m_indiceNetworkHardwareEmu, linkNode, ifaceName);
    this->m_indiceNetworkHardwareEmu += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else if(type == "Tap")
  {
    Tap *link = new Tap(type, this->m_indiceNetworkHardwareTap, linkNode, ifaceName);
    this->m_indiceNetworkHardwareTap += 1;
    this->m_listNetworkHardware.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. (" + type + ") not found.");
  }
}

void Generator::RemoveNetworkHardware(const std::string &name)
{
  size_t startNumber = this->m_listNetworkHardware.size();
  for(size_t i = 0; i < this->m_listNetworkHardware.size(); i++)
  {
    if(this->m_listNetworkHardware.at(i)->GetNetworkHardwareName() == name)
    {
      delete this->m_listNetworkHardware[i];
      this->m_listNetworkHardware.erase(this->m_listNetworkHardware.begin() + i);
      break;
    }
  }
  size_t endNumber = this->m_listNetworkHardware.size();
  if(startNumber == endNumber)
  {
    throw std::logic_error("Link remove failed! (" + name + ") not found.");
  }
}

void Generator::RemoveNetworkHardware(const size_t index)
{
  if(this->m_listNetworkHardware.size() < index)
  {
    throw std::out_of_range("Link remove failed! (index not exists).");
    return;
  }

  delete this->m_listNetworkHardware[index];
  this->m_listNetworkHardware.erase(this->m_listNetworkHardware.begin() + index);
}

NetworkHardware* Generator::GetNetworkHardware(const size_t index)
{
  if(this->m_listNetworkHardware.size() < index)
  {
    throw std::out_of_range("Index does not exist.");
    return 0;
  }
 
  return this->m_listNetworkHardware.at(index);
}

size_t Generator::GetNNetworkHardwares() const
{
  return this->m_listNetworkHardware.size();
}

//
// Part around the C++ code Generation.
// This part is looking about the code to write.
//

void Generator::GenerateCodeCpp(std::string fileName) 
{
  if(fileName != ""){
    this->m_cppFile.open(fileName.c_str());
  }

  //
  // Generate headers 
  //
  this->WriteCpp("#include \"ns3/core-module.h\"");
  this->WriteCpp("#include \"ns3/global-route-manager.h\"");
  this->WriteCpp("#include \"ns3/network-module.h\"");
  this->WriteCpp("#include \"ns3/internet-module.h\"");

  std::vector<std::string> allHeaders = GenerateHeader();
  for(size_t i = 0; i <  allHeaders.size(); i++)
  {
    this->WriteCpp("" + allHeaders.at(i));
  }

  this->WriteCpp("");
  this->WriteCpp("using namespace ns3;");
  this->WriteCpp("");

  this->WriteCpp("int main(int argc, char *argv[])");
  this->WriteCpp("{");

  //
  // Tap/Emu variables
  //
  std::vector<std::string> allVars = GenerateVarsCpp();
  for(size_t i = 0; i <  allVars.size(); i++)
  {
    this->WriteCpp("  " + allVars.at(i));
    this->WriteCpp("");
  }

  //
  // Generate Command Line 
  //
  this->WriteCpp("  CommandLine cmd;");

  std::vector<std::string> allCmdLine = GenerateCmdLineCpp();
  for(size_t i = 0; i <  allCmdLine.size(); i++)
  {
    this->WriteCpp("  " + allCmdLine.at(i));
  } 

  this->WriteCpp("  cmd.Parse (argc, argv);");

  //
  // Generate Optional configuration
  // 
  this->WriteCpp("");
  this->WriteCpp("  /* Configuration. */");
  std::vector<std::string> conf = GenerateConfigCpp();
  for(size_t i = 0; i <  conf.size(); i++)
  {
    this->WriteCpp("  " + conf.at(i));
  }

  //
  // Generate Nodes. 
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Build nodes. */");
  std::vector<std::string> nodeBuild = GenerateNodeCpp();
  for(size_t i = 0; i <  nodeBuild.size(); i++)
  {
    this->WriteCpp("  " + nodeBuild.at(i));
  }

  //
  // Generate Link.
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Build link. */");
  std::vector<std::string> linkBuild = GenerateNetworkHardwareCpp(); 
  for(size_t i = 0; i <  linkBuild.size(); i++)
  {
    this->WriteCpp("  " + linkBuild.at(i));
  }

  //
  // Generate link net device container.
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Build link net device container. */");
  std::vector<std::string> linkNdcBuild = GenerateNetDeviceCpp(); 
  for(size_t i = 0; i <  linkNdcBuild.size(); i++)
  {
    this->WriteCpp("  " + linkNdcBuild.at(i));
  }

  //
  // Generate Ip Stack. 
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Install the IP stack. */");
  std::vector<std::string> allStacks = GenerateIpStackCpp();
  for(size_t i = 0; i <  allStacks.size(); i++)
  {
    this->WriteCpp("  " + allStacks.at(i));
  }

  //
  // Generate IP assignation.
  // 
  this->WriteCpp("");
  this->WriteCpp("  /* IP assign. */");
  std::vector<std::string> allAssign = GenerateIpAssignCpp();
  for(size_t i = 0; i <  allAssign.size(); i++)
  {
    this->WriteCpp("  " + allAssign.at(i));
  } 

  //
  // Generate TapBridge if tap is used.
  //
  std::vector<std::string> allTapBridge = GenerateTapBridgeCpp();
  if(allTapBridge.size() > 0)
  {
    this->WriteCpp("");
    this->WriteCpp("  /* Tap Bridge. */");
  }
  for(size_t i = 0; i <  allTapBridge.size(); i++)
  {
    this->WriteCpp("  " + allTapBridge.at(i));
  } 

  //
  // Generate Route.
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Generate Route. */");
  std::vector<std::string> allRoutes = GenerateRouteCpp();
  for(size_t i = 0; i <  allRoutes.size(); i++)
  {
    this->WriteCpp("  " + allRoutes.at(i));
  } 

  //
  // Generate Application.
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Generate Application. */");
  std::vector<std::string> allApps = GenerateApplicationCpp();
  for(size_t i = 0; i <  allApps.size(); i++)
  {
    this->WriteCpp("  " + allApps.at(i));
  } 

  //
  // Others
  //
  this->WriteCpp("");
  this->WriteCpp("  /* Simulation. */");

  this->WriteCpp("  /* Pcap output. */");
  std::vector<std::string> allTrace = GenerateTraceCpp();
  for(size_t i = 0; i <  allTrace.size(); i++)
  {
    this->WriteCpp("  " + allTrace.at(i));
  } 

  /* Set stop time. */
  size_t stopTime = 0;/* default stop time. */
  for(size_t i = 0; i <  this->m_listApplication.size(); i++)
  {
    if( (this->m_listApplication.at(i))->GetEndTimeNumber() > stopTime)
    {
      stopTime = (this->m_listApplication.at(i))->GetEndTimeNumber();
    }
  }
  stopTime += 1;

  this->WriteCpp("  /* Stop the simulation after x seconds. */");
  this->WriteCpp("  uint32_t stopTime = "+ utils::integerToString(stopTime) +";"); 
  this->WriteCpp("  Simulator::Stop (Seconds (stopTime));");

  this->WriteCpp("  /* Start and clean simulation. */");
  this->WriteCpp("  Simulator::Run ();");
  this->WriteCpp("  Simulator::Destroy ();");

  this->WriteCpp("}"); 
  
  if(fileName != ""){
    this->m_cppFile.close();
  }
}

std::vector<std::string> Generator::GenerateHeader() 
{
  std::vector<std::string> allHeaders;
  // get all headers.
  /* from m_listNode. */
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateHeader();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }
  /* from m_listLink */
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateHeader();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }
  /* from m_listApplication */
  for(size_t i = 0; i <  this->m_listApplication.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listApplication.at(i))->GenerateHeader();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }

  /* check for duplicate */
  std::vector<std::string> headersWithoutDuplicateElem;
  bool isDuplicate = false;
  /* iterate all headers string */
  for(size_t i = 0; i <  allHeaders.size(); i++)
  {
    isDuplicate = false;
    /* iterate the vector whith no duplicate */
    for(size_t j = 0; j <  headersWithoutDuplicateElem.size(); j++)
    {
      /* check if the string into the allHeaders vector is also in the vector without duplicate */
      if( allHeaders.at(i) == headersWithoutDuplicateElem.at(j))
      {
        /* it's an duplicated elem. */
        isDuplicate = true;
        break;
      }	
    }
    /* add the string from allHeaders if no duplicate have been detected. */
    if(!isDuplicate)
    {
      headersWithoutDuplicateElem.push_back(allHeaders.at(i));
    }
  }
  return headersWithoutDuplicateElem;
}

std::vector<std::string> Generator::GenerateVarsCpp()
{
  std::vector<std::string> allVars;
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateVarsCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allVars.push_back(trans.at(j));
    }
  }

  /* add nsc var if used. */
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    if( (this->m_listNode.at(i))->GetNsc() != "")
    {
      allVars.push_back("std::string nscStack = \"" + (this->m_listNode.at(i))->GetNsc() + "\";");
    }
  }
  return allVars;
}

std::vector<std::string> Generator::GenerateCmdLineCpp() 
{
  std::vector<std::string> allCmdLine;
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateCmdLineCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allCmdLine.push_back(trans.at(j));
    }
  }
  return allCmdLine;
}

std::vector<std::string> Generator::GenerateConfigCpp() 
{
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    if( ((this->m_listNode.at(i))->GetNodeName()).find("tap_") == 0)
    {
      this->AddConfig("GlobalValue::Bind (\"SimulatorImplementationType\", StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("GlobalValue::Bind (\"ChecksumEnabled\", BooleanValue (true));");
    }
  }

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  { 
    if( ((this->m_listNetworkHardware.at(i))->GetNetworkHardwareName()).find("emu_") == 0 )
    {
      this->AddConfig("GlobalValue::Bind (\"SimulatorImplementationType\", StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("GlobalValue::Bind (\"ChecksumEnabled\", BooleanValue (true));");
    }
  } 

  std::vector<std::string> allConf;
  for(size_t i = 0; i <  this->m_listConfiguration.size(); i++)
  {
    allConf.push_back(this->m_listConfiguration.at(i));
  }

  return allConf;
}

std::vector<std::string> Generator::GenerateNodeCpp() 
{
  std::vector<std::string> allNodes;
  /* get all the node code. */
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateNodeCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allNodes.push_back(trans.at(j));
    }
  }
  return allNodes;
}

std::vector<std::string> Generator::GenerateNetworkHardwareCpp() 
{
  std::vector<std::string> allLink;
  /* get all the link build code. */
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateNetworkHardwareCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allLink.push_back(trans.at(j));
    }
  }
  return allLink;
}
std::vector<std::string> Generator::GenerateNetDeviceCpp() 
{
  std::vector<std::string> allNdc;
  /* get all the link build code. */
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateNetDeviceCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allNdc.push_back(trans.at(j));
    }
  }
  return allNdc;
}

std::vector<std::string> Generator::GenerateIpStackCpp() 
{
  std::vector<std::string> allStack;

  /* construct node without bridge Node. */
  allStack.push_back("InternetStackHelper internetStackH;");
  std::string nodeName = "";
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    nodeName = (this->m_listNode.at(i))->GetNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      std::vector<std::string> trans = (this->m_listNode.at(i)->GenerateIpStackCpp());
      for(size_t j = 0; j <  trans.size(); j++)
      {
        allStack.push_back(trans.at(j));
      }
    }
  }

  return allStack;
}

std::vector<std::string> Generator::GenerateIpAssignCpp() 
{
  std::vector<std::string> ipAssign;
  ipAssign.push_back("Ipv4AddressHelper ipv4;");

  size_t ipRange = 0;
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    ipAssign.push_back("ipv4.SetBase (\"10.0." + utils::integerToString(ipRange) + ".0\", \"255.255.255.0\");");
    ipAssign.push_back("Ipv4InterfaceContainer iface_" + this->m_listNetworkHardware.at(i)->GetNdcName() + " = ipv4.Assign (" + this->m_listNetworkHardware.at(i)->GetNdcName() + ");");
    ipRange += 1;
  } 

  return ipAssign;
}

std::vector<std::string> Generator::GenerateRouteCpp() 
{
  std::vector<std::string> allRoutes;
 
  allRoutes.push_back("Ipv4GlobalRoutingHelper::PopulateRoutingTables ();");

  return allRoutes;
}

std::vector<std::string> Generator::GenerateApplicationCpp() 
{
  size_t nodeNumber = 0;
  std::string ndcName = "";
  size_t linkNumber = 0;
  std::vector<std::string> allApps;
  /* get all the ip assign code. */
  for(size_t i = 0; i <  this->m_listApplication.size(); i++)
  {
    /* get NetDeviceContainer and number from the receiver. */
    std::string receiverName = this->m_listApplication.at(i)->GetReceiverNode();
    nodeNumber = 0;
    ndcName = "";
    linkNumber = 0;

    /* if the receiver is in NodeContainer */
    if(receiverName.find("NodeContainer(") == 0)
    {
      std::string oldReceiverName = receiverName;
      
      std::vector<std::string> tab_name;
      split(tab_name, receiverName, '(');
      
      std::string str_get = tab_name.at(1);
      std::vector<std::string> tab_name2;
      split(tab_name2, str_get, '.');
      
      receiverName = tab_name2.at(0);
      for(size_t x = 0;  x < this->m_listNetworkHardware.size(); x++)
      {
        nodeNumber = 0;
        for(size_t y = 0; y < this->m_listNetworkHardware.at(x)->GetInstalledNodes().size(); y++)
        {
          if(this->m_listNetworkHardware.at(x)->GetInstalledNodes().at(y) == receiverName || this->m_listNetworkHardware.at(x)->GetInstalledNodes().at(y) == oldReceiverName)
          {
            ndcName = (this->m_listNetworkHardware.at(x))->GetNdcName();
            linkNumber = x;
            break;
          }
          if(ndcName != "")
          {
            break;
          }
        }
      }
      std::vector<std::string> linksNode = this->m_listNetworkHardware.at(linkNumber)->GetInstalledNodes();
      for(size_t j = 0; j < linksNode.size(); j++)
      {
        if(linksNode.at(j) == oldReceiverName)
        {
          nodeNumber = j;
          break;
        }
      }
    }
    else
    {
      for(size_t j = 0; j <  this->m_listNetworkHardware.size(); j++)
      {
        nodeNumber = 0;
        linkNumber = 0;
        std::vector<std::string> nodes = (this->m_listNetworkHardware.at(j))->GetInstalledNodes();
        for(size_t k = 0; k <  nodes.size(); k++)
        {
          if( nodes.at(k) == receiverName)
          {
            ndcName = (this->m_listNetworkHardware.at(j))->GetNdcName();
            break;
          }
          else
          {
            for(size_t l = 0; l <  this->m_listNode.size(); l++)
            {
              if(this->m_listNode.at(l)->GetNodeName() == nodes.at(k))
              {
                nodeNumber += this->m_listNode.at(l)->GetMachinesNumber();
                break;
              }
            }
          }
        }
        if(ndcName != "")
        {
          break;
        }
      }
    }
    /* get the application code with param. */
    std::vector<std::string> trans = (this->m_listApplication.at(i)->GenerateApplicationCpp(ndcName, nodeNumber));
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allApps.push_back(trans.at(j));
    }
  }

  return allApps;
}

std::vector<std::string> Generator::GenerateTapBridgeCpp()
{
  std::vector<std::string> allTapBridge;

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateTapBridgeCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allTapBridge.push_back(trans.at(j));
    }
  }

  return allTapBridge;
}

std::vector<std::string> Generator::GenerateTraceCpp()
{
  std::vector<std::string> allTrace;

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateTraceCpp();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allTrace.push_back(trans.at(j));
    }
  }

  return allTrace;
}

//
// Part around the C++ code Generation.
// This part is looking about the code to write.

void Generator::GenerateCodePython(std::string fileName)
{
  if(fileName != ""){
    this->m_pyFile.open(fileName.c_str());
  }
  
  //
  // Generate headers 
  //
  this->WritePython("import ns3");
  this->WritePython("");
  this->WritePython("def main(argv):");
  this->WritePython("");

  //
  // Tap/Emu variables
  //
  std::vector<std::string> allVars = GenerateVarsPython();
  for(size_t i = 0; i <  allVars.size(); i++)
  {
    this->WritePython("    " + allVars.at(i));
    this->WritePython("");
  }

  //
  // Generate Command Line 
  //
  this->WritePython("    cmd = ns3.CommandLine()");

  std::vector<std::string> allCmdLine = GenerateCmdLinePython();
  for(size_t i = 0; i <  allCmdLine.size(); i++)
  {
    this->WritePython("    " + allCmdLine.at(i));
  } 

  this->WritePython("    cmd.Parse (argv)");

  //
  // Generate Optional configuration
  // 
  this->WritePython("");
  this->WritePython("    # Configuration.");
  std::vector<std::string> conf = GenerateConfigPython();
  for(size_t i = 0; i <  conf.size(); i++)
  {
    this->WritePython("    " + conf.at(i));
  }

  //
  // Generate Nodes. 
  //
  this->WritePython("");
  this->WritePython("    # Build nodes");
  std::vector<std::string> nodeBuild = GenerateNodePython();
  for(size_t i = 0; i <  nodeBuild.size(); i++)
  {
    this->WritePython("    " + nodeBuild.at(i));
  }

  //
  // Generate Link.
  //
  this->WritePython("");
  this->WritePython("    # Build link.");
  std::vector<std::string> linkBuild = GenerateNetworkHardwarePython();
  for(size_t i = 0; i <  linkBuild.size(); i++)
  {
    this->WritePython("    " + linkBuild.at(i));
  }

  //
  // Generate link net device container.
  //
  this->WritePython("");
  this->WritePython("    # Build link net device container.");
  std::vector<std::string> linkNdcBuild = GenerateNetDevicePython(); 
  for(size_t i = 0; i <  linkNdcBuild.size(); i++)
  {
    this->WritePython("    " + linkNdcBuild.at(i));
  }

  //
  // Generate IP Stack. 
  //
  this->WritePython("");
  this->WritePython("    # Install the IP stack.");
  std::vector<std::string> allStacks = GenerateIpStackPython();
  for(size_t i = 0; i <  allStacks.size(); i++)
  {
    this->WritePython("    " + allStacks.at(i));
  }

  //
  // Generate IP assignation.
  // 
  this->WritePython("");
  this->WritePython("    # IP assign.");
  std::vector<std::string> allAssign = GenerateIpAssignPython();
  for(size_t i = 0; i <  allAssign.size(); i++)
  {
    this->WritePython("    " + allAssign.at(i));
  } 

  //
  // Generate TapBridge if tap is used.
  //
  std::vector<std::string> allTapBridge = GenerateTapBridgePython();
  if(allTapBridge.size() > 0)
  {
    this->WritePython("");
    this->WritePython("    # Tap Bridge.");
  }
  for(size_t i = 0; i <  allTapBridge.size(); i++)
  {
    this->WritePython("    " + allTapBridge.at(i));
  } 

  //
  // Generate Route.
  //
  this->WritePython("");
  this->WritePython("    # Generate Route.");
  std::vector<std::string> allRoutes = GenerateRoutePython();
  for(size_t i = 0; i <  allRoutes.size(); i++)
  {
    this->WritePython("    " + allRoutes.at(i));
  } 

  //
  // Generate Application.
  //
  this->WritePython("");
  this->WritePython("    # Generate Application.");
  std::vector<std::string> allApps = GenerateApplicationPython();
  for(size_t i = 0; i <  allApps.size(); i++)
  {
    this->WritePython("    " + allApps.at(i));
  } 

  //
  // Others
  //
  this->WritePython("");
  this->WritePython("    # Simulation.");


  this->WritePython("    # Pcap output.");
  std::vector<std::string> allTrace = GenerateTracePython();
  for(size_t i = 0; i <  allTrace.size(); i++)
  {
    this->WritePython("    " + allTrace.at(i));
  } 

  /* Set stop time. */
  size_t stopTime = 0;/* default stop time. */
  for(size_t i = 0; i <  this->m_listApplication.size(); i++)
  {
    if( (this->m_listApplication.at(i))->GetEndTimeNumber() > stopTime)
    {
      stopTime = (this->m_listApplication.at(i))->GetEndTimeNumber();
    }
  }
  stopTime += 1;

  this->WritePython("    # Stop the simulation after x seconds.");
  this->WritePython("    stopTime = "+ utils::integerToString(stopTime) ); 
  this->WritePython("    ns3.Simulator.Stop (ns3.Seconds(stopTime))");

  this->WritePython("    # Start and clean simulation.");
  this->WritePython("    ns3.Simulator.Run()");
  this->WritePython("    ns3.Simulator.Destroy()");

  this->WritePython("");
  this->WritePython("if __name__ == '__main__':");
  this->WritePython("    import sys");
  this->WritePython("    main(sys.argv)");
  
  if(fileName != ""){
    this->m_pyFile.close();
  }
}


std::vector<std::string> Generator::GenerateVarsPython()
{
  std::vector<std::string> ret;
  return ret;
}

std::vector<std::string> Generator::GenerateCmdLinePython()
{
  std::vector<std::string> allCmdLine;

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateCmdLinePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allCmdLine.push_back(trans.at(j));
    }
  }
  return allCmdLine;
}

std::vector<std::string> Generator::GenerateConfigPython()
{
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    if( ((this->m_listNode.at(i))->GetNodeName()).find("tap_") == 0)
    {
      this->AddConfig("ns3.GlobalValue.Bind (\"SimulatorImplementationType\", ns3.StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("ns3.GlobalValue.Bind (\"ChecksumEnabled\", ns3.BooleanValue (true));");
    }
  }

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    if( ((this->m_listNetworkHardware.at(i))->GetNetworkHardwareName()).find("emu_") == 0 )
    {
      this->AddConfig("ns3.GlobalValue.Bind (\"SimulatorImplementationType\", ns3.StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("ns3.GlobalValue.Bind (\"ChecksumEnabled\", ns3.BooleanValue (true));");
    }
  }

  std::vector<std::string> allConf;
  for(size_t i = 0; i <  this->m_listConfiguration.size(); i++)
  {
    allConf.push_back(this->m_listConfiguration.at(i));
  }

  return allConf;
}

std::vector<std::string> Generator::GenerateNodePython()
{
  std::vector<std::string> allNodes;
  /* get all the node code. */
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateNodePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allNodes.push_back(trans.at(j));
    }
  }
  return allNodes;
}

std::vector<std::string> Generator::GenerateNetworkHardwarePython()
{
  std::vector<std::string> allLink;
  /* get all the link build code. */
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateNetworkHardwarePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allLink.push_back(trans.at(j));
    }
  }
  return allLink;
}

std::vector<std::string> Generator::GenerateNetDevicePython()
{
  std::vector<std::string> allNdc;
  /* get all the link build code. */
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateNetDevicePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allNdc.push_back(trans.at(j));
    }
  }
  return allNdc;
}

std::vector<std::string> Generator::GenerateIpStackPython()
{
  std::vector<std::string> allStack;

  /* construct node without bridge Node. */
  allStack.push_back("internetStackH = ns3.InternetStackHelper()");
  std::string nodeName = "";
  for(size_t i = 0; i <  this->m_listNode.size(); i++)
  {
    nodeName = (this->m_listNode.at(i))->GetNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      std::vector<std::string> trans = (this->m_listNode.at(i)->GenerateIpStackPython());
      for(size_t j = 0; j <  trans.size(); j++)
      {
        allStack.push_back(trans.at(j));
      }
    }
  }

  return allStack;
}

std::vector<std::string> Generator::GenerateIpAssignPython()
{
  std::vector<std::string> ipAssign;
  ipAssign.push_back("ipv4 = ns3.Ipv4AddressHelper()");

  size_t ipRange = 0;
  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    ipAssign.push_back("ipv4.SetBase (ns3.Ipv4Address(\"10.0." + utils::integerToString(ipRange) + ".0\"), ns3.Ipv4Mask(\"255.255.255.0\"))");
    ipAssign.push_back("iface_" + this->m_listNetworkHardware.at(i)->GetNdcName() + " = ipv4.Assign (" + this->m_listNetworkHardware.at(i)->GetNdcName() + ")");
    ipRange += 1;
  }

  return ipAssign;
}

std::vector<std::string> Generator::GenerateTapBridgePython()
{
  std::vector<std::string> allTapBridge;

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateTapBridgePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allTapBridge.push_back(trans.at(j));
    }
  }

  return allTapBridge;
}

std::vector<std::string> Generator::GenerateRoutePython()
{
  std::vector<std::string> allRoutes;

  allRoutes.push_back("ns3.Ipv4GlobalRoutingHelper.PopulateRoutingTables ()");

  return allRoutes;
}

std::vector<std::string> Generator::GenerateApplicationPython()
{
  size_t nodeNumber = 0;
  std::string ndcName = "";
  size_t linkNumber = 0;
  std::vector<std::string> allApps;
  
  /* get all the ip assign code. */
  for(size_t i = 0; i <  this->m_listApplication.size(); i++)
  {
    /* get NetDeviceContainer and number from the receiver. */
    std::string receiverName = this->m_listApplication.at(i)->GetReceiverNode();
    nodeNumber = 0;
    ndcName = "";
    linkNumber = 0;

    /* if the receiver is in NodeContainer */
    if(receiverName.find("NodeContainer(") == 0)
    {
      std::string oldReceiverName = receiverName;
      
      std::vector<std::string> tab_name;
      split(tab_name, receiverName, '(');
      
      std::string str_get = tab_name.at(1);
      std::vector<std::string> tab_name2;
      split(tab_name2, str_get, '.');
      
      receiverName = tab_name2.at(0);
      for(size_t x = 0;  x < this->m_listNetworkHardware.size(); x++)
      {
        nodeNumber = 0;
        for(size_t y = 0; y < this->m_listNetworkHardware.at(x)->GetInstalledNodes().size(); y++)
        {
          if(this->m_listNetworkHardware.at(x)->GetInstalledNodes().at(y) == receiverName || this->m_listNetworkHardware.at(x)->GetInstalledNodes().at(y) == oldReceiverName)
          {
            ndcName = (this->m_listNetworkHardware.at(x))->GetNdcName();
            linkNumber = x;
            break;
          }
          if(ndcName != "")
          {
            break;
          }
        }
      }
      std::vector<std::string> linksNode = this->m_listNetworkHardware.at(linkNumber)->GetInstalledNodes();
      for(size_t j = 0; j < linksNode.size(); j++)
      {
        if(linksNode.at(j) == oldReceiverName)
        {
          nodeNumber = j;
          break;
        }
      }
    }
    else
    {
      for(size_t j = 0; j <  this->m_listNetworkHardware.size(); j++)
      {
        nodeNumber = 0;
        linkNumber = 0;
        std::vector<std::string> nodes = (this->m_listNetworkHardware.at(j))->GetInstalledNodes();
        for(size_t k = 0; k <  nodes.size(); k++)
        {
          if( nodes.at(k) == receiverName)
          {
            ndcName = (this->m_listNetworkHardware.at(j))->GetNdcName();
            break;
          }
          else
          {
            for(size_t l = 0; l <  this->m_listNode.size(); l++)
            {
              if(this->m_listNode.at(l)->GetNodeName() == nodes.at(k))
              {
                nodeNumber += this->m_listNode.at(l)->GetMachinesNumber();
                break;
              }
            }
          }
        }
        if(ndcName != "")
        {
          break;
        }
      }
    }
    /* get the application code with param. */
    std::vector<std::string> trans = (this->m_listApplication.at(i)->GenerateApplicationPython(ndcName, nodeNumber));
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allApps.push_back(trans.at(j));
    }
  }

  return allApps;
}

std::vector<std::string> Generator::GenerateTracePython()
{
  std::vector<std::string> allTrace;

  for(size_t i = 0; i <  this->m_listNetworkHardware.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNetworkHardware.at(i))->GenerateTracePython();
    for(size_t j = 0; j <  trans.size(); j++)
    {
      allTrace.push_back(trans.at(j));
    }
  }

  return allTrace;
}

//
// Cpp generation operation part.
//

void Generator::WriteCpp(const std::string &line) 
{
  std::cout << line << std::endl;
  if(this->m_cppFile.is_open())
  {
    this->m_cppFile << line + '\n';
  }
}

//
// Python generation operation part.
//

void Generator::WritePython(const std::string &line)
{
  std::cout << line << std::endl;
  if(this->m_pyFile.is_open())
  {
    this->m_pyFile << line + '\n';
  }
}
