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
#include <stdexcept>

#include "generator.h"
#include "node.h"
#include "hub.h"
#include "point-to-point.h"
#include "bridge.h"
#include "ap.h"
#include "link.h"
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
  this->m_indiceLinkAp = 0;
  this->m_indiceLinkEmu = 0;
  this->m_indiceLinkPointToPoint = 0;
  this->m_indiceLinkTap = 0;
  this->m_indiceLinkHub = 0;
  this->m_indiceLinkBridge = 0;

  /* Application */
  this->m_indiceApplicationPing = 0; 
  this->m_indiceApplicationTcpLargeTransfer = 0;
  this->m_indiceApplicationUdpEcho = 0;

}

Generator::~Generator()
{
  /* Node */
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    delete this->m_listNode.at(i);
  }

  /* Link */
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    delete this->m_listLink.at(i);
  }

  /* Application */
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
  {
    delete this->m_listApplication.at(i);
  }
}

void Generator::AddConfig(const std::string &config)
{
  bool isDuplicate = false;
  for(size_t i = 0; i < (size_t) this->m_listConfiguration.size(); i++)
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
  if(type == "Pc")
  {
    equi = new Node(this->m_indiceNodePc, std::string("term_"), number);
    this->m_indiceNodePc += 1;
  } 
  else if(type == "Router")
  {
    equi = new Node(this->m_indiceNodeRouter, std::string("router_"), number);
    this->m_indiceNodeRouter += 1;
  } 
  else if(type == "Ap")
  {
    equi = new Node(this->m_indiceNodeAp, std::string("ap_"), number);
    this->m_indiceNodeAp += 1;
  } 
  else if(type == "Station")
  {
    equi = new Node(this->m_indiceNodeStation, std::string("station_"), number);
    this->m_indiceNodeStation += 1;
  } 
  else if(type == "Bridge")
  {
    equi = new Node(this->m_indiceNodeBridge, std::string("bridge_"), number);
    this->m_indiceNodeBridge += 1;
  } 
  else if(type == "Tap")
  {
    equi = new Node(this->m_indiceNodeTap, std::string("tap_"), number);
    this->m_indiceNodeTap += 1;
  } 
  else if(type == "Emu")
  {
    equi = new Node(this->m_indiceNodeEmu, std::string("emu_"), number);
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
  if(type == "Pc")
  {
    equi = new Node(this->m_indiceNodePc, std::string("term_"), number);
    this->m_indiceNodePc += 1;
  } 
  else if(type == "Router")
  {
    equi = new Node(this->m_indiceNodeRouter, std::string("router_"), number);
    this->m_indiceNodeRouter += 1;
  } 
  else if(type == "Ap")
  {
    equi = new Node(this->m_indiceNodeAp, std::string("ap_"), number);
    this->m_indiceNodeAp += 1;
  } 
  else if(type == "Station")
  {
    equi = new Node(this->m_indiceNodeStation, std::string("station_"), number);
    this->m_indiceNodeStation += 1;
  } 
  else if(type == "Bridge")
  {
    equi = new Node(this->m_indiceNodeBridge, std::string("bridge_"), number);
    this->m_indiceNodeBridge += 1;
  } 
  else if(type == "Tap")
  {
    equi = new Node(this->m_indiceNodeTap, std::string("tap_"), number);
    this->m_indiceNodeTap += 1;
  }
  else if(type == "Emu")
  {
    equi = new Node(this->m_indiceNodeEmu, std::string("emu_"), number);
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
  for(int i = 0; (size_t) i < this->m_listNode.size(); i++)
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
    UdpEcho *app = new UdpEcho(this->m_indiceApplicationUdpEcho, senderNode, receiverNode, startTime, endTime, port);
    this->m_indiceApplicationUdpEcho += 1;
    this->m_listApplication.push_back(app);
  }
  else if(type == "TcpLargeTransfer")
  {
    TcpLargeTransfer *app = new TcpLargeTransfer(this->m_indiceApplicationTcpLargeTransfer, senderNode, receiverNode, startTime, endTime, port);
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
    Ping *app = new Ping(this->m_indiceApplicationPing, senderNode, receiverNode, startTime, endTime);
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
  for(int i = 0; (size_t) i < this->m_listApplication.size(); i++)
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
void Generator::AddLink(const std::string &type) 
{
  // call to the right type constructor. 
  if(type == "Hub")
  {
    Hub *link = new Hub(this->m_indiceLinkHub);
    this->m_indiceLinkHub += 1;
    this->m_listLink.push_back(link);
  } 
  else if(type == "PointToPoint")
  {
    PointToPoint *link = new PointToPoint(this->m_indiceLinkPointToPoint);
    this->m_indiceLinkPointToPoint += 1;
    this->m_listLink.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. ( " + type + ") not found.");
  }
}

void Generator::AddLink(const std::string &type, const std::string &linkNode) 
{
  if(type == "Bridge")
  {
    Bridge *link = new Bridge(this->m_indiceLinkBridge, linkNode);
    this->m_indiceLinkBridge += 1;
    this->m_listLink.push_back(link);
  } 
  else if(type == "Ap")
  {
    Ap *link = new Ap(this->m_indiceLinkAp, linkNode);
    this->m_indiceLinkAp += 1;
    this->m_listLink.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. (" + type + ") not found.");
  }
}

void Generator::AddLink(const std::string &type, const std::string &linkNode, const std::string &ifaceName)
{ 
  if(type == "Emu")
  {
    Emu *link = new Emu(this->m_indiceLinkEmu, linkNode, ifaceName);
    this->m_indiceLinkEmu += 1;
    this->m_listLink.push_back(link);
  } 
  else if(type == "Tap")
  {
    Tap *link = new Tap(this->m_indiceLinkTap, linkNode, ifaceName);
    this->m_indiceLinkTap += 1;
    this->m_listLink.push_back(link);
  } 
  else
  {
    throw std::logic_error("Add Link failed. (" + type + ") not found.");
  }
}

void Generator::RemoveLink(const std::string &name)
{
  size_t startNumber = this->m_listLink.size();
  for(int i = 0; (size_t) i < this->m_listLink.size(); i++)
  {
    if(this->m_listLink.at(i)->GetLinkName() == name)
    {
      delete this->m_listLink[i];
      this->m_listLink.erase(this->m_listLink.begin() + i);
      break;
    }
  }
  size_t endNumber = this->m_listLink.size();
  if(startNumber == endNumber)
  {
    throw std::logic_error("Link remove failed! (" + name + ") not found.");
  }
}

void Generator::RemoveLink(const size_t index)
{
  if(this->m_listLink.size() < index)
  {
    throw std::out_of_range("Link remove failed! (index not exists).");
    return;
  }

  delete this->m_listLink[index];
  this->m_listLink.erase(this->m_listLink.begin() + index);
}

Link* Generator::GetLink(const size_t index)
{
  if(this->m_listLink.size() < index)
  {
    throw std::out_of_range("Index does not exist.");
    return 0;
  }
 
  return this->m_listLink.at(index);
}

size_t Generator::GetNLinks() const
{
  return this->m_listLink.size();
}

//
// Part around the C++ code Generation.
// This part is looking about the code to write.
//

void Generator::GenerateCodeCpp() 
{	
  /* In first time we just print it to stdout, at the end, we will use the write cpp function */

  //
  // Generate headers 
  //
  std::cout << "#include \"ns3/simulator-module.h\"" << std::endl;
  std::cout << "#include \"ns3/node-module.h\"" << std::endl;
  std::cout << "#include \"ns3/core-module.h\"" << std::endl;
  std::cout << "#include \"ns3/common-module.h\""<< std::endl;
  std::cout << "#include \"ns3/global-route-manager.h\"" << std::endl;

  std::vector<std::string> allHeaders = GenerateHeader();
  for(size_t i = 0; i < (size_t) allHeaders.size(); i++)
  {
    std::cout << "" << allHeaders.at(i) << std::endl;
  }

  std::cout << "" << std::endl;
  std::cout << "using namespace ns3;" << std::endl;
  std::cout << "" << std::endl;

  std::cout << "int main(int argc, char *argv[])" << std::endl;
  std::cout << "{" << std::endl;

  //
  // Tap/Emu variables
  //
  std::vector<std::string> allVars = GenerateVarsCpp();
  for(size_t i = 0; i < (size_t) allVars.size(); i++)
  {
    std::cout << "  " << allVars.at(i) << std::endl;
    std::cout << "" << std::endl;
  }

  //
  // Generate Command Line 
  //
  std::cout << "  CommandLine cmd;" << std::endl;

  std::vector<std::string> allCmdLine = GenerateCmdLineCpp();
  for(size_t i = 0; i < (size_t) allCmdLine.size(); i++)
  {
    std::cout << "  " << allCmdLine.at(i) << std::endl;
  } 

  std::cout << "  cmd.Parse (argc, argv);" << std::endl;

  //
  // Generate Optional configuration
  // 
  std::cout << "" << std::endl;
  std::cout << "  /* Configuration. */" << std::endl;
  std::vector<std::string> conf = GenerateConfigCpp();
  for(size_t i = 0; i < (size_t) conf.size(); i++)
  {
    std::cout << "  " << conf.at(i) << std::endl;
  }

  //
  // Generate Nodes. 
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build nodes. */" << std::endl;
  std::vector<std::string> nodeBuild = GenerateNodeCpp();
  for(size_t i = 0; i < (size_t) nodeBuild.size(); i++)
  {
    std::cout << "  " << nodeBuild.at(i) << std::endl;
  }

  //
  // Generate Link.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build link. */" << std::endl;
  std::vector<std::string> linkBuild = GenerateLinkCpp(); 
  for(size_t i = 0; i < (size_t) linkBuild.size(); i++)
  {
    std::cout << "  " << linkBuild.at(i) << std::endl;
  }

  //
  // Generate link net device container.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build link net device container. */" << std::endl;
  std::vector<std::string> linkNdcBuild = GenerateNetDeviceCpp(); 
  for(size_t i = 0; i < (size_t) linkNdcBuild.size(); i++)
  {
    std::cout << "  " << linkNdcBuild.at(i) << std::endl;
  }

  //
  // Generate Ip Stack. 
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Install the IP stack. */" << std::endl;
  std::vector<std::string> allStacks = GenerateIpStackCpp();
  for(size_t i = 0; i < (size_t) allStacks.size(); i++)
  {
    std::cout << "  " << allStacks.at(i) << std::endl;
  }

  //
  // Generate IP assignation.
  // 
  std::cout << "" << std::endl;
  std::cout << "  /* IP assign. */" << std::endl;
  std::vector<std::string> allAssign = GenerateIpAssignCpp();
  for(size_t i = 0; i < (size_t) allAssign.size(); i++)
  {
    std::cout << "  " << allAssign.at(i) << std::endl;
  } 

  //
  // Generate TapBridge if tap is used.
  //
  std::vector<std::string> allTapBridge = GenerateTapBridgeCpp();
  if(allTapBridge.size() > 0)
  {
    std::cout << "" << std::endl;
    std::cout << "  /* Tap Bridge. */" << std::endl;
  }
  for(size_t i = 0; i < (size_t) allTapBridge.size(); i++)
  {
    std::cout << "  " << allTapBridge.at(i) << std::endl;
  } 

  //
  // Generate Route.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Generate Route. */" << std::endl;
  std::vector<std::string> allRoutes = GenerateRouteCpp();
  for(size_t i = 0; i < (size_t) allRoutes.size(); i++)
  {
    std::cout << "  " << allRoutes.at(i) << std::endl;
  } 

  //
  // Generate Application.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Generate Application. */" << std::endl;
  std::vector<std::string> allApps = GenerateApplicationCpp();
  for(size_t i = 0; i < (size_t) allApps.size(); i++)
  {
    std::cout << "  " << allApps.at(i) << std::endl;
  } 

  //
  // Others
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Simulation. */" << std::endl;


  std::cout << "  /* Pcap output. */" << std::endl;
  std::vector<std::string> allTrace = GenerateTraceCpp();
  for(size_t i = 0; i < (size_t) allTrace.size(); i++)
  {
    std::cout << "  " << allTrace.at(i) << std::endl;
  } 

  /* Set stop time. */
  size_t stopTime = 0;/* default stop time. */
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
  {
    if( (this->m_listApplication.at(i))->GetEndTimeNumber() > stopTime)
    {
      stopTime = (this->m_listApplication.at(i))->GetEndTimeNumber();
    }
  }
  stopTime += 1;

  std::cout << "  /* Stop the simulation after x seconds. */" << std::endl;
  std::cout << "  uint32_t stopTime = "<< stopTime << ";" << std::endl; 
  std::cout << "  Simulator::Stop (Seconds (stopTime));" << std::endl;

  std::cout << "  /* Start and clean simulation. */" << std::endl;
  std::cout << "  Simulator::Run ();" << std::endl;
  std::cout << "  Simulator::Destroy ();" << std::endl;

  std::cout << "}" << std::endl; 
}

std::vector<std::string> Generator::GenerateHeader() 
{
  std::vector<std::string> allHeaders;
  // get all headers.
  /* from m_listNode. */
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateHeader();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }
  /* from m_listLink */
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateHeader();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }
  /* from m_listApplication */
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listApplication.at(i))->GenerateHeader();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allHeaders.push_back(trans.at(j));
    }
  }

  /* check for duplicate */
  std::vector<std::string> headersWithoutDuplicateElem;
  bool isDuplicate = false;
  /* iterate all headers string */
  for(size_t i = 0; i < (size_t) allHeaders.size(); i++)
  {
    isDuplicate = false;
    /* iterate the vector whith no duplicate */
    for(size_t j = 0; j < (size_t) headersWithoutDuplicateElem.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateVarsCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allVars.push_back(trans.at(j));
    }
  }

  /* add nsc var if used. */
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateCmdLineCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allCmdLine.push_back(trans.at(j));
    }
  }
  return allCmdLine;
}

std::vector<std::string> Generator::GenerateConfigCpp() 
{
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    if( ((this->m_listNode.at(i))->GetNodeName()).find("tap_") == 0)
    {
      this->AddConfig("GlobalValue::Bind (\"SimulatorImplementationType\", StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("GlobalValue::Bind (\"ChecksumEnabled\", BooleanValue (true));");
    }
  }

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  { 
    if( ((this->m_listLink.at(i))->GetLinkName()).find("emu_") == 0 )
    {
      this->AddConfig("GlobalValue::Bind (\"SimulatorImplementationType\", StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("GlobalValue::Bind (\"ChecksumEnabled\", BooleanValue (true));");
    }
  } 

  std::vector<std::string> allConf;
  for(size_t i = 0; i < (size_t) this->m_listConfiguration.size(); i++)
  {
    allConf.push_back(this->m_listConfiguration.at(i));
  }

  return allConf;
}

std::vector<std::string> Generator::GenerateNodeCpp() 
{
  std::vector<std::string> allNodes;
  /* get all the node code. */
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateNodeCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allNodes.push_back(trans.at(j));
    }
  }
  return allNodes;
}

std::vector<std::string> Generator::GenerateLinkCpp() 
{
  std::vector<std::string> allLink;
  /* get all the link build code. */
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateLinkCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateNetDeviceCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    nodeName = (this->m_listNode.at(i))->GetNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      std::vector<std::string> trans = (this->m_listNode.at(i)->GenerateIpStackCpp());
      for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    ipAssign.push_back("ipv4.SetBase (\"10.0." + utils::integerToString(ipRange) + ".0\", \"255.255.255.0\");");
    ipAssign.push_back("Ipv4InterfaceContainer iface_" + this->m_listLink.at(i)->GetNdcName() + " = ipv4.Assign (" + this->m_listLink.at(i)->GetNdcName() + ");");
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
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
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
      for(size_t x = 0;  x < this->m_listLink.size(); x++)
      {
        nodeNumber = 0;
        for(size_t y = 0; y < this->m_listLink.at(x)->GetInstalledNodes().size(); y++)
        {
          if(this->m_listLink.at(x)->GetInstalledNodes().at(y) == receiverName || this->m_listLink.at(x)->GetInstalledNodes().at(y) == oldReceiverName)
          {
            ndcName = (this->m_listLink.at(x))->GetNdcName();
            linkNumber = x;
            break;
          }
          if(ndcName != "")
          {
            break;
          }
        }
      }
      std::vector<std::string> linksNode = this->m_listLink.at(linkNumber)->GetInstalledNodes();
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
      for(size_t j = 0; j < (size_t) this->m_listLink.size(); j++)
      {
        nodeNumber = 0;
        linkNumber = 0;
        std::vector<std::string> nodes = (this->m_listLink.at(j))->GetInstalledNodes();
        for(size_t k = 0; k < (size_t) nodes.size(); k++)
        {
          if( nodes.at(k) == receiverName)
          {
            ndcName = (this->m_listLink.at(j))->GetNdcName();
            break;
          }
          else
          {
            for(size_t l = 0; l < (size_t) this->m_listNode.size(); l++)
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
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allApps.push_back(trans.at(j));
    }
  }

  return allApps;
}

std::vector<std::string> Generator::GenerateTapBridgeCpp()
{
  std::vector<std::string> allTapBridge;

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateTapBridgeCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allTapBridge.push_back(trans.at(j));
    }
  }

  return allTapBridge;
}

std::vector<std::string> Generator::GenerateTraceCpp()
{
  std::vector<std::string> allTrace;

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateTraceCpp();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allTrace.push_back(trans.at(j));
    }
  }

  return allTrace;
}

//
// Part around the C++ code Generation.
// This part is looking about the code to write.

void Generator::GenerateCodePython()
{
  /* In first time we just print it to stdout, at the end, we will use the write cpp function */
  
  //
  // Generate headers 
  //
  std::cout << "import ns3" << std::endl << std::endl;

  std::cout << "def main(argv):" << std::endl << std::endl;

  //
  // Tap/Emu variables
  //
  std::vector<std::string> allVars = GenerateVarsPython();
  for(size_t i = 0; i < (size_t) allVars.size(); i++)
  {
    std::cout << "    " << allVars.at(i) << std::endl;
    std::cout << "" << std::endl;
  }

  //
  // Generate Command Line 
  //
  std::cout << "    cmd = ns3.CommandLine()" << std::endl;

  std::vector<std::string> allCmdLine = GenerateCmdLinePython();
  for(size_t i = 0; i < (size_t) allCmdLine.size(); i++)
  {
    std::cout << "    " << allCmdLine.at(i) << std::endl;
  } 

  std::cout << "    cmd.Parse (argv)" << std::endl;

  //
  // Generate Optional configuration
  // 
  std::cout << "" << std::endl;
  std::cout << "    # Configuration." << std::endl;
  std::vector<std::string> conf = GenerateConfigPython();
  for(size_t i = 0; i < (size_t) conf.size(); i++)
  {
    std::cout << "    " << conf.at(i) << std::endl;
  }

  //
  // Generate Nodes. 
  //
  std::cout << "" << std::endl;
  std::cout << "    # Build nodes" << std::endl;
  std::vector<std::string> nodeBuild = GenerateNodePython();
  for(size_t i = 0; i < (size_t) nodeBuild.size(); i++)
  {
    std::cout << "    " << nodeBuild.at(i) << std::endl;
  }

  //
  // Generate Link.
  //
  std::cout << "" << std::endl;
  std::cout << "    # Build link." << std::endl;
  std::vector<std::string> linkBuild = GenerateLinkPython();
  for(size_t i = 0; i < (size_t) linkBuild.size(); i++)
  {
    std::cout << "    " << linkBuild.at(i) << std::endl;
  }

  //
  // Generate link net device container.
  //
  std::cout << "" << std::endl;
  std::cout << "    # Build link net device container." << std::endl;
  std::vector<std::string> linkNdcBuild = GenerateNetDevicePython(); 
  for(size_t i = 0; i < (size_t) linkNdcBuild.size(); i++)
  {
    std::cout << "    " << linkNdcBuild.at(i) << std::endl;
  }

  //
  // Generate IP Stack. 
  //
  std::cout << "" << std::endl;
  std::cout << "    # Install the IP stack." << std::endl;
  std::vector<std::string> allStacks = GenerateIpStackPython();
  for(size_t i = 0; i < (size_t) allStacks.size(); i++)
  {
    std::cout << "    " << allStacks.at(i) << std::endl;
  }

  //
  // Generate IP assignation.
  // 
  std::cout << "" << std::endl;
  std::cout << "    # IP assign." << std::endl;
  std::vector<std::string> allAssign = GenerateIpAssignPython();
  for(size_t i = 0; i < (size_t) allAssign.size(); i++)
  {
    std::cout << "    " << allAssign.at(i) << std::endl;
  } 

  //
  // Generate TapBridge if tap is used.
  //
  std::vector<std::string> allTapBridge = GenerateTapBridgePython();
  if(allTapBridge.size() > 0)
  {
    std::cout << "" << std::endl;
    std::cout << "    # Tap Bridge." << std::endl;
  }
  for(size_t i = 0; i < (size_t) allTapBridge.size(); i++)
  {
    std::cout << "    " << allTapBridge.at(i) << std::endl;
  } 

  //
  // Generate Route.
  //
  std::cout << "" << std::endl;
  std::cout << "    # Generate Route." << std::endl;
  std::vector<std::string> allRoutes = GenerateRoutePython();
  for(size_t i = 0; i < (size_t) allRoutes.size(); i++)
  {
    std::cout << "    " << allRoutes.at(i) << std::endl;
  } 

  //
  // Generate Application.
  //
  std::cout << "" << std::endl;
  std::cout << "    # Generate Application." << std::endl;
  std::vector<std::string> allApps = GenerateApplicationPython();
  for(size_t i = 0; i < (size_t) allApps.size(); i++)
  {
    std::cout << "    " << allApps.at(i) << std::endl;
  } 

  //
  // Others
  //
  std::cout << "" << std::endl;
  std::cout << "    # Simulation." << std::endl;


  std::cout << "    # Pcap output." << std::endl;
  std::vector<std::string> allTrace = GenerateTracePython();
  for(size_t i = 0; i < (size_t) allTrace.size(); i++)
  {
    std::cout << "    " << allTrace.at(i) << std::endl;
  } 

  /* Set stop time. */
  size_t stopTime = 0;/* default stop time. */
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
  {
    if( (this->m_listApplication.at(i))->GetEndTimeNumber() > stopTime)
    {
      stopTime = (this->m_listApplication.at(i))->GetEndTimeNumber();
    }
  }
  stopTime += 1;

  std::cout << "    # Stop the simulation after x seconds." << std::endl;
  std::cout << "    stopTime = "<< stopTime << std::endl; 
  std::cout << "    ns3.Simulator.Stop (ns3.Seconds(stopTime))" << std::endl;

  std::cout << "    # Start and clean simulation." << std::endl;
  std::cout << "    ns3.Simulator.Run()" << std::endl;
  std::cout << "    ns3.Simulator.Destroy()" << std::endl;

  std::cout << std::endl;
  std::cout << "if __name__ == '__main__':" << std::endl;;
  std::cout << "    import sys" << std::endl;
  std::cout << "    main(sys.argv)" << std::endl;
}


std::vector<std::string> Generator::GenerateVarsPython()
{
  std::vector<std::string> ret;
  return ret;
}

std::vector<std::string> Generator::GenerateCmdLinePython()
{
  std::vector<std::string> allCmdLine;

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateCmdLinePython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allCmdLine.push_back(trans.at(j));
    }
  }
  return allCmdLine;
}

std::vector<std::string> Generator::GenerateConfigPython()
{
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    if( ((this->m_listNode.at(i))->GetNodeName()).find("tap_") == 0)
    {
      this->AddConfig("ns3.GlobalValue.Bind (\"SimulatorImplementationType\", ns3.StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("ns3.GlobalValue.Bind (\"ChecksumEnabled\", ns3.BooleanValue (true));");
    }
  }

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    if( ((this->m_listLink.at(i))->GetLinkName()).find("emu_") == 0 )
    {
      this->AddConfig("ns3.GlobalValue.Bind (\"SimulatorImplementationType\", ns3.StringValue (\"ns3::RealtimeSimulatorImpl\"));");
      this->AddConfig("ns3.GlobalValue.Bind (\"ChecksumEnabled\", ns3.BooleanValue (true));");
    }
  }

  std::vector<std::string> allConf;
  for(size_t i = 0; i < (size_t) this->m_listConfiguration.size(); i++)
  {
    allConf.push_back(this->m_listConfiguration.at(i));
  }

  return allConf;
}

std::vector<std::string> Generator::GenerateNodePython()
{
  std::vector<std::string> allNodes;
  /* get all the node code. */
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listNode.at(i))->GenerateNodePython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allNodes.push_back(trans.at(j));
    }
  }
  return allNodes;
}

std::vector<std::string> Generator::GenerateLinkPython()
{
  std::vector<std::string> allLink;
  /* get all the link build code. */
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateLinkPython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateNetDevicePython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listNode.size(); i++)
  {
    nodeName = (this->m_listNode.at(i))->GetNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      std::vector<std::string> trans = (this->m_listNode.at(i)->GenerateIpStackPython());
      for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    ipAssign.push_back("ipv4.SetBase (ns3.Ipv4Address(\"10.0." + utils::integerToString(ipRange) + ".0\"), ns3.Ipv4Mask(\"255.255.255.0\"))");
    ipAssign.push_back("iface_" + this->m_listLink.at(i)->GetNdcName() + " = ipv4.Assign (" + this->m_listLink.at(i)->GetNdcName() + ")");
    ipRange += 1;
  }

  return ipAssign;
}

std::vector<std::string> Generator::GenerateTapBridgePython()
{
  std::vector<std::string> allTapBridge;

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateTapBridgePython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
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
  for(size_t i = 0; i < (size_t) this->m_listApplication.size(); i++)
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
      for(size_t x = 0;  x < this->m_listLink.size(); x++)
      {
        nodeNumber = 0;
        for(size_t y = 0; y < this->m_listLink.at(x)->GetInstalledNodes().size(); y++)
        {
          if(this->m_listLink.at(x)->GetInstalledNodes().at(y) == receiverName || this->m_listLink.at(x)->GetInstalledNodes().at(y) == oldReceiverName)
          {
            ndcName = (this->m_listLink.at(x))->GetNdcName();
            linkNumber = x;
            break;
          }
          if(ndcName != "")
          {
            break;
          }
        }
      }
      std::vector<std::string> linksNode = this->m_listLink.at(linkNumber)->GetInstalledNodes();
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
      for(size_t j = 0; j < (size_t) this->m_listLink.size(); j++)
      {
        nodeNumber = 0;
        linkNumber = 0;
        std::vector<std::string> nodes = (this->m_listLink.at(j))->GetInstalledNodes();
        for(size_t k = 0; k < (size_t) nodes.size(); k++)
        {
          if( nodes.at(k) == receiverName)
          {
            ndcName = (this->m_listLink.at(j))->GetNdcName();
            break;
          }
          else
          {
            for(size_t l = 0; l < (size_t) this->m_listNode.size(); l++)
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
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allApps.push_back(trans.at(j));
    }
  }

  return allApps;
}

std::vector<std::string> Generator::GenerateTracePython()
{
  std::vector<std::string> allTrace;

  for(size_t i = 0; i < (size_t) this->m_listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->m_listLink.at(i))->GenerateTracePython();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allTrace.push_back(trans.at(j));
    }
  }

  return allTrace;
}

//
// XML generation operation part.
//

void Generator::OpenXml() 
{
}

std::string Generator::GetXmlFileName() 
{
  return this->m_xmlFileName;
}

void Generator::WriteXml(const std::string &line) 
{
  std::cout << line << std::endl;
}

void Generator::SetXmlFileName(const std::string &xmlFileName) 
{
  this->m_xmlFileName = xmlFileName;
}

//
// Cpp generation operation part.
//

std::string Generator::GetCppFileName() 
{
  return this->m_cppFileName;
}

void Generator::SetCppFileName(const std::string &cppFileName ) 
{
  this->m_cppFileName = cppFileName;
}

void Generator::WriteCpp(const std::string &line) 
{
  std::cout << line << std::endl;
}

//
// Python generation operation part.
//

void Generator::WritePython(const std::string &line)
{
  std::cout << line << std::endl;
}

std::string Generator::GetPyFileName() 
{
  return this->m_pyFileName;
}

void Generator::SetPyFileName(const std::string &pyFileName ) 
{
  this->m_pyFileName = pyFileName;
}

