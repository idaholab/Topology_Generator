/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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
 */
/**
* \file Generator.cpp
* \brief The main class of the Generator.
* \author Pierre Weiss
* \date 2009
*/

#include <sstream>

#include "Generator.h"
#include "Equipement.h"
#include "Hub.h"
#include "PointToPoint.h"
#include "Bridge.h"
#include "Wifi.h"
#include "Link.h"
#include "Ping.h"

Generator::Generator()
{
 
  /* Equipement. */
  this->indiceEquipementPc = 0;
  this->indiceEquipementRouter = 0;
  this->indiceEquipementAp = 0;
  this->indiceEquipementStation = 0;
  this->indiceEquipementBridge = 0;
  this->indiceEquipementTap = 0;

  /* Link */
  this->indiceLinkWifi = 0;
  this->indiceLinkEmu = 0;
  this->indiceLinkPointToPoint = 0;
  this->indiceLinkTap = 0;
  this->indiceLinkHub = 0;
  this->indiceLinkBridge = 0;

  /* Application */
  this->indiceApplicationPing = 0; 
  this->indiceApplicationTcpLargeTransfert = 0;
  this->indiceApplicationUdp_Echo = 0;

}

Generator::~Generator()
{
  /* Equipement */
  for(size_t i = 0; i < (size_t) this->listEquipement.size(); i++)
  {
    delete this->listEquipement.at(i);
  }
  
  /* Link */
  for(size_t i = 0; i < (size_t) this->listLink.size(); i++)
  {
    delete this->listLink.at(i);
  }
  
  /* Application */
  for(size_t i = 0; i < (size_t) this->listApplication.size(); i++)
  {
    delete this->listApplication.at(i);
  }
}

//
// Part of Equipement.
//
void Generator::AddEquipement(std::string type) 
{
  Equipement *equi = NULL;
  
  // call to the right type constructor. 
  if(type.compare("Pc") == 0)
  {
  	equi = new Equipement(this->indiceEquipementPc, "node_");
  	this->indiceEquipementPc += 1;
  } 
  else if(type.compare("Router") == 0)
  {
  	equi = new Equipement(this->indiceEquipementRouter, "router_");
  	this->indiceEquipementRouter += 1;
  } 
  else if(type.compare("Ap") == 0)
  {
  	equi = new Equipement(this->indiceEquipementAp, "ap_");
  	this->indiceEquipementAp += 1;
  } 
  else if(type.compare("Station") == 0)
  {
    equi = new Equipement(this->indiceEquipementStation, "station_");
  	this->indiceEquipementStation += 1;
  } 
  else if(type.compare("Bridge") == 0)
  {
    equi = new Equipement(this->indiceEquipementBridge, "bridge_");
  	this->indiceEquipementBridge += 1;
  } 
  else if(type.compare("Tap") == 0)
  {
  	equi = new Equipement(this->indiceEquipementTap, "tap_");
  	this->indiceEquipementTap += 1;
  } 
  
  if(equi)//!= NULL
  {
    this->listEquipement.push_back(equi);
  }
  
}

//
// Part of Application.
//
void Generator::AddApplication(std::string type, std::string senderNode, std::string receiverNode, size_t startTime, size_t endTime) 
{
  if(type.compare("Ping") == 0)
  {
      Ping *app = new Ping(this->indiceApplicationPing, senderNode, receiverNode, startTime, endTime);
      this->indiceApplicationPing += 1;
      this->listApplication.push_back(app);
  }
  
}

//
// Part of Link.
//
void Generator::AddLink(std::string type, std::string linkNode) 
{
  // call to the right type constructor. 
  if(type.compare("Hub") == 0)
  {
  	Hub *link = new Hub(this->indiceLinkHub);
  	this->indiceLinkHub += 1;
    this->listLink.push_back(link);
  } 
  else if(type.compare("PointToPoint") == 0)
  {
  	PointToPoint *link = new PointToPoint(this->indiceLinkPointToPoint);
  	this->indiceLinkPointToPoint += 1;
    this->listLink.push_back(link);
  } 
  else if(type.compare("Bridge") == 0)
  {
  	Bridge *link = new Bridge(this->indiceLinkBridge, linkNode);
  	this->indiceLinkBridge += 1;
    this->listLink.push_back(link);
  } 
  else if(type.compare("Wifi") == 0)
  {
  	Wifi *link = new Wifi(this->indiceLinkWifi, linkNode);
  	this->indiceLinkWifi += 1;
    this->listLink.push_back(link);
  }  
  else if(type.compare("Emu") == 0)
  {
  	//~ *link = new Link(this->indiceLinkEmu);
  	this->indiceLinkEmu += 1;
  } 
  else if(type.compare("Tap") == 0)
  {
  	//~ *link = new Link(this->indiceLinkTap);
  	this->indiceLinkTap += 1;
  } 
  
}


//
// Part around the code Generation.
// This part is looking about the code to write.
//


void Generator::GenerateCode() 
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
  std::cout << "" << std::endl;
              
  //
  // Generate Command Line 
  //
  std::cout << "  CommandLine cmd;" << std::endl;
           
  //~ GenerateCmdLine() 
  
  std::cout << "  cmd.Parse (argc, argv);" << std::endl;
  
  //
  // Generate Optional configuration
  // 
  //~ GenerateConfig() 
  
  //
  // Generate Nodes. 
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build nodes. */" << std::endl;
  std::vector<std::string> nodeBuild = GenerateNode();
  for(size_t i = 0; i < (size_t) nodeBuild.size(); i++)
  {
  	std::cout << "  " << nodeBuild.at(i) << std::endl;
  }
  
  //
  // Generate Link.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build link. */" << std::endl;
  std::vector<std::string> linkBuild = GenerateLink(); 
  for(size_t i = 0; i < (size_t) linkBuild.size(); i++)
  {
  	std::cout << "  " << linkBuild.at(i) << std::endl;
  }
  
  //
  // Generate link net device container.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Build link net device container. */" << std::endl;
  std::vector<std::string> linkNdcBuild = GenerateNetDevice(); 
  for(size_t i = 0; i < (size_t) linkNdcBuild.size(); i++)
  {
  	std::cout << "  " << linkNdcBuild.at(i) << std::endl;
  }

  //
  // Generate Ip Stack. 
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Install the IP stack */" << std::endl;
  std::vector<std::string> allStacks = GenerateIpStack();
  for(size_t i = 0; i < (size_t) allStacks.size(); i++)
  {
  	std::cout << "  " << allStacks.at(i) << std::endl;
  }
  
  //
  // Generate Ip Assign.
  // 
  std::cout << "" << std::endl;
  std::cout << "  /* IP assign */" << std::endl;
  std::vector<std::string> allAssign = GenerateIpAssign();
  for(size_t i = 0; i < (size_t) allAssign.size(); i++)
  {
  	std::cout << "  " << allAssign.at(i) << std::endl;
  } 
  
  //
  // Generate Route.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Generate Route. */" << std::endl;
  std::vector<std::string> allRoutes = GenerateRoute();
  for(size_t i = 0; i < (size_t) allRoutes.size(); i++)
  {
  	std::cout << "  " << allRoutes.at(i) << std::endl;
  } 
  
  //
  // Generate Application.
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Generate Application. */" << std::endl;
  std::vector<std::string> allApps = GenerateApplication();
  for(size_t i = 0; i < (size_t) allApps.size(); i++)
  {
  	std::cout << "  " << allApps.at(i) << std::endl;
  } 
  
  //
  // Other
  //
  std::cout << "" << std::endl;
  std::cout << "  /* Simulation. */" << std::endl;
  std::cout << "  CsmaHelper::EnablePcapAll (\"test\", false);" << std::endl;
  std::cout << "  Simulator::Run ();" << std::endl;
  std::cout << "  Simulator::Destroy ();" << std::endl;
  
  std::cout << "}" << std::endl; 
}

std::vector<std::string> Generator::GenerateHeader() 
{
  /* still in developpement, must be add the link and the applications headers! */
  std::vector<std::string> allHeaders;
  /* get all headers. */
  /* from listEquipement. */
  for(size_t i = 0; i < (size_t) this->listEquipement.size(); i++)
  {
    std::vector<std::string> trans = (this->listEquipement.at(i))->GenerateHeader();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
  	  allHeaders.push_back(trans.at(j));
    }
  }
  /* from listLink */
  for(size_t i = 0; i < (size_t) this->listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->listLink.at(i))->GenerateHeader();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
  	  allHeaders.push_back(trans.at(j));
    }
  }
  /* from listApplication */
  for(size_t i = 0; i < (size_t) this->listApplication.size(); i++)
  {
    std::vector<std::string> trans = (this->listApplication.at(i))->GenerateHeader();
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
  	  if( allHeaders.at(i).compare(headersWithoutDuplicateElem.at(j)) == 0 )
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

std::string Generator::GenerateCmdLine() 
{
  return "";
}

std::string Generator::GenerateConfig() 
{
  return "";
}

std::vector<std::string> Generator::GenerateNode() 
{
  std::vector<std::string> allNodes;
  /* get all the node code. */
  for(size_t i = 0; i < (size_t) this->listEquipement.size(); i++)
  {
    std::vector<std::string> trans = (this->listEquipement.at(i))->GenerateNode();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allNodes.push_back(trans.at(j));
    }
  }
  return allNodes;
}

std::vector<std::string> Generator::GenerateLink() 
{
  std::vector<std::string> allLink;
  /* get all the link build code. */
  for(size_t i = 0; i < (size_t) this->listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->listLink.at(i))->GenerateLink();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allLink.push_back(trans.at(j));
    }
  }
  return allLink;
}
std::vector<std::string> Generator::GenerateNetDevice() 
{
  std::vector<std::string> allNdc;
  /* get all the link build code. */
  for(size_t i = 0; i < (size_t) this->listLink.size(); i++)
  {
    std::vector<std::string> trans = (this->listLink.at(i))->GenerateNetDevice();
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allNdc.push_back(trans.at(j));
    }
  }
  return allNdc;
}

std::vector<std::string> Generator::GenerateIpStack() 
{
  std::vector<std::string> allStack;
  std::string nodeName = "";
  /* get all the node code. */
  for(size_t i = 0; i < (size_t) this->listEquipement.size(); i++)
  {
    nodeName = (this->listEquipement.at(i))->getNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      std::vector<std::string> trans = (this->listEquipement.at(i)->GenerateIpStack());
      for(size_t j = 0; j < (size_t) trans.size(); j++)
      {
       allStack.push_back(trans.at(j));
      }
    }
    
  }

  return allStack;
}

std::vector<std::string> Generator::GenerateIpAssign() 
{
  std::vector<std::string> ipAssign;
  
  ipAssign.push_back("Ipv4AddressHelper ipv4;");
  
  size_t ipRange = 0;
  for(size_t i = 0; i < (size_t) this->listLink.size(); i++)
  {
    ipAssign.push_back("ipv4.SetBase (\"10.0."+Generator::toString(ipRange)+".0\", \"255.255.255.0\");");
    ipAssign.push_back("Ipv4InterfaceContainer iface_"+this->listLink.at(i)->getNdcName()+" = ipv4.Assign("+this->listLink.at(i)->getNdcName()+");");
    ipRange += 1;
  }
  
  return ipAssign;
}

std::vector<std::string> Generator::GenerateRoute() 
{
  std::vector<std::string> allRoutes;
  std::string nodeName = "";
  allRoutes.push_back("NodeContainer allRoutes;");
  for(size_t i = 0; i < (size_t) this->listEquipement.size(); i++)
  {
    nodeName = (this->listEquipement.at(i))->getNodeName();
    /* if it is not a bridge you can add it. */
    if(nodeName.find("bridge_") != 0)
    {
      allRoutes.push_back("allRoutes.Add("+nodeName+");");
    }
  }
  allRoutes.push_back("GlobalRouteManager::PopulateRoutingTables (allRoutes);");
  
  return allRoutes;
}

std::vector<std::string> Generator::GenerateApplication() 
{
  size_t nodeNumber = 0;
  std::string ndcName = "";
  
  std::vector<std::string> allApps;
  /* get all the ip assign code. */
  for(size_t i = 0; i < (size_t) this->listApplication.size(); i++)
  {
    /* get NetDeviceContainer and number from the receiver. */
    
    std::string receiverName = this->listApplication.at(i)->getReceiverNode();
    for(size_t j = 0; j < (size_t) this->listLink.size(); j++)
    {
      std::vector<std::string> nodes = (this->listLink.at(j))->getNodes();
      for(size_t k = 0; k < (size_t) nodes.size(); k++)
      {
        if( (nodes.at(k)).compare(receiverName) == 0)
        {
          /* this means that the node is in this link.*/
          ndcName = (this->listLink.at(j))->getNdcName();
          nodeNumber = k;
          break; 
        }
      }
    }
    
    /* get the application code with param. */
    std::vector<std::string> trans = (this->listApplication.at(i)->GenerateApplication(ndcName, nodeNumber));
    for(size_t j = 0; j < (size_t) trans.size(); j++)
    {
      allApps.push_back(trans.at(j));
    }
  }

  return allApps;
}


//
// XML generation operation part.
//

void Generator::OpenXml() 
{
}

std::string Generator::getXmlFileName() 
{
  return this->xmlFileName;
}

void Generator::WriteXml(std::string _line) 
{
  std::cout << _line << std::endl;
}

void Generator::setXmlFileName(std::string _xmlFileName) 
{
  this->xmlFileName = _xmlFileName;
}

//
// Cpp generation operation part.
//

std::string Generator::getCppFileName() 
{
  return this->cppFileName;
}

void Generator::setCppFileName(std::string _cppFileName ) 
{
  this->cppFileName = _cppFileName;
}

void Generator::WriteCpp(std::string _line) 
{
  std::cout << _line << std::endl;
}

//
// Python generation operation part.
//
  
void Generator::WritePython(std::string _line)
{
   std::cout << _line << std::endl;
}

std::string Generator::getPyFileName() 
{
  return this->pyFileName;
}

void Generator::setPyFileName(std::string _pyFileName ) 
{
  this->pyFileName = _pyFileName;
}

//
//
//

std::string Generator::toString(size_t nbr)
{
  std::ostringstream out;
  out << nbr;
  
  return out.str();
}

