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
 * \file node.cpp
 * \brief Node base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "node.h"
#include "generator.h"

#include "utils.h"

Node::Node(const size_t &indice, const std::string &type, const std::string &namePrefix, const size_t &machinesNumber)
{
  this->m_indice = indice;
  this->m_type = type;
  this->m_nodeName = std::string(namePrefix + utils::integerToString(indice));
  this->m_ipInterfaceName = std::string("iface_" + this->m_nodeName);
  this->m_nsc = std::string("");	
  this->m_machinesNumber = machinesNumber;
}

Node::~Node()
{
}

void Node::SetNodeName(const std::string &nodeName)
{
  this->m_nodeName = nodeName;
}

void Node::SetIpInterfaceName(const std::string &ipInterfaceName)
{
  this->m_ipInterfaceName = ipInterfaceName;
}

std::string Node::GetNodeName()
{
  return this->m_nodeName;
}

std::string Node::GetNodeName(const size_t &number)
{
  return std::string("NodeContainer(" + this->m_nodeName + ".Get(" + utils::integerToString(number) + "))");
}

std::string Node::GetIpInterfaceName()
{
  return this->m_ipInterfaceName;
}

std::string Node::GetIndice()
{
  return utils::integerToString(this->m_indice);
}

void Node::SetIndice(const size_t &indice)
{
  this->m_indice = indice;
}

std::string Node::GetNsc()
{
  return this->m_nsc;
}

void Node::SetNsc(const std::string &nsc)
{
  this->m_nsc = nsc;
}

size_t Node::GetMachinesNumber()
{
  return this->m_machinesNumber;
}

void Node::SetMachinesNumber(const size_t machinesNumber)
{
  this->m_machinesNumber = machinesNumber;
}

std::vector<std::string> Node::GenerateHeader()
{
  std::vector<std::string> headers;

  return headers; 
}

std::vector<std::string> Node::GenerateNodeCpp()
{
  std::vector<std::string> nodes;
  nodes.push_back("NodeContainer " + this->m_nodeName + ";");
  nodes.push_back(this->m_nodeName + ".Create (" + utils::integerToString(this->m_machinesNumber) + ");");

  return nodes; 
}

std::vector<std::string> Node::GenerateIpStackCpp()
{
  std::vector<std::string> stack;
  
  if(this->m_nsc != "")
  {
    stack.push_back("internetStackH.SetTcp (\"ns3::NscTcpL4Protocol\",\"Library\",StringValue(nscStack));");
  }
  stack.push_back("internetStackH.Install (" + this->m_nodeName + ");");

  return stack; 
}

std::vector<std::string> Node::GenerateNodePython()
{
  std::vector<std::string> nodes;
  
  nodes.push_back(this->m_nodeName + " = ns3.NodeContainer()");
  nodes.push_back(this->m_nodeName + ".Create (" + utils::integerToString(this->m_machinesNumber) + ")");
  return nodes; 
}

std::vector<std::string> Node::GenerateIpStackPython()
{
  std::vector<std::string> stack;
  
  if(this->m_nsc != "")
  {
    stack.push_back("internetStackH.SetTcp (\"ns3::NscTcpL4Protocol\",\"Library\",StringValue(nscStack))");
  }
  stack.push_back("internetStackH.Install (" + this->m_nodeName + ")");

  return stack; 
}

std::string Node::GetNodeType()
{
  return this->m_type;
}
