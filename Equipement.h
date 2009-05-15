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
* \file Equipement.h
* \brief Equipement Base Class.
* \author Pierre Weiss
* \date 2009
*/

#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <iostream>
#include <string>
#include <vector>


/**
 * \ingroup generator
 * \brief Equipement Base Class.
 *
 * This class is the main class of the differents equipement you can choose to use.
 * It contain the Pc Switch, Router, Tap, Wifi Ap, Wifi Station.
 */
class Equipement 
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
   * \brief attribute which represent the ip.
   */
  std::string ip;
  
  /**
   * \brief attribute which represent the mask.
   */
  std::string mask;
  
  /**
   * \brief attribute which represent the ip interface name. 
   */
  std::string ipInterfaceName;
  
  /**
   * \brief attribute which represent the x position of the object.
   */
  size_t x;
  
  /**
   * \brief attribute which represent the y position of the object.
   */
  size_t y;
  
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
   * \brief Constructor which set default value.
   * \param _indice
   * \param _type
   */
  Equipement(size_t _indice, std::string _type);
  
  /**
   * \brief Constructor which set default value.
   * \param _indice
   * \param _type
   * \param _machinesNumber
   */
  Equipement(size_t _indice, std::string _type, size_t _machinesNumber);
  
  /**
   * \brief Destructor from the class Equipement.
   */
  ~Equipement();

  /**
   * \brief Function wich return the c++ header code from node.
   *
   * This function return a string which contain the header lines from the specified object.
   * 
   * \return header.
   */
  std::vector<std::string> GenerateHeader();

  /**
   * \brief Function wich return the c++ code from node.
   *
   * This function return a string which contain the declaration and instanciation of the node.
   * 
   * \return node.
   */
  std::vector<std::string> GenerateNode();

  /**
   * \brief Function wich return the c++ code from IpStack.
   *
   * This function return a string which contain the c++ code from the Ipv4 stack declaration and instanciation.
   * 
   * \return ipStack.
   */
  std::vector<std::string> GenerateIpStack();
  
  /**
   * \brief Procedure to set the node name.
   * 
   * \param _nodeName the string which containe the node name.
   */
  void setNodeName(std::string _nodeName);

  /**
   * \brief Procedure to set the ip and mask.
   *
   * The ip have to be inserted as an ipv4 address. Example :10.0.0.1
   * Mask example : 255.255.255.0
   * 
   * \param _ip the ip.
   * \param _mask the mask.
   */
  void setIpv4Address(std::string _ip, std::string _mask);

  /**
   * \brief Procedure to set the Ip interface name.
   * 
   * This procedure is used to the the ipInterfaceName. 
   * Sometimes this var is used in application like as UdpEcho.
   *
   * \param _ipInterfaceName
   */
  void setIpInterfaceName(std::string _ipInterfaceName);
  
  /**
   * \brief Procedure to set the graphical position of the equipement.
   *
   * This procedure is used to change the position of an equipement.
   * Like after a drag n drop.
   * 
   * \param _x the x position.
   * \param _y the y position.
   */
   void setPosition(size_t _x, size_t _y);

  /**
   * \brief Function wich return the node name.
   *
   * \return node name.
   */
  std::string getNodeName();
  
  /**
   * \brief Function wich return the node name.
   * \param number
   * \return node name.
   */
  std::string getNodeName(size_t number);

  /**
   * \brief Function wich return the name of the Ip interface.
   * 
   * \return ip interface name.
   */
  std::string getIpInterfaceName();

  /**
   * \brief Function wich return the ip address.
   *
   * \return ip.
   */
  std::string getIp();
  
  /**
   * \brief Function wich return a string with the mask.
   *
   * \return mask.
   */
  std::string getMask();
  
  /**
   * \brief Function which return the x position.
   * 
   * \return x position.
   */
  std::string getX();
  
  /**
   * \brief Function which return the y position.
   * 
   * \return y position.
   */
  std::string getY();
  
  /**
  * \brief Function wich return the node number.
  *
  * \return node number in type string.
  */
  std::string getIndice();
  
  /**
   * \brief Function to get the nsc use.
   * \return string
   */
  std::string getNsc();
  
  /**
   * \brief Procedure to set the nsc use.
   * \param _nsc
   */
  void setNsc(std::string _nsc);
 
};

#endif /* EQUIPEMENT_H */

