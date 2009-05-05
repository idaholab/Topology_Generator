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
* \brief Abstract Equipement Base Class.
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
 * \brief Abstract Equipement Base Class.
 *
 * This class is the main class of the differents equipement you can choose to use.
 * It contain the Pc, Hub, Switch, Router, Tap, Wifi Ap, Wifi Station.
 */
class Equipement 
{

protected:
  /**
   * \brief attribute which represent the node number.
   * 
   * This is an attribute which represent the number of the object creation.
   */
  std::string indice;
  
  /**
   * \brief attribute which represent the node name.
   * 
   * The node name.
   */
  std::string nodeName;
  
  /**
   * \brief attribute which represent the ip.
   * 
   * The ip attributed to the node.
   */
  std::string ip;
  
  /**
   * \brief attribute which represent the mask.
   * 
   * The mask attributed to the node network.
   */
  std::string mask;
  
  /**
   * \brief attribute which represent the ip interface name. 
   * 
   * The ip interface name is used to generate the code for the applications like an udp_echo.
   */
  std::string ipInterfaceName;
  
  /**
   * \brief attribute which represent the header.
   * 
   * This attribute reprensent the differents files to be included for the node.
   */
  std::string header;
  
  /**
   * \brief attribute which represent the x position of the object.
   * 
   * The x graphical position.
   */
  int x;
  
  /**
   * \brief attribute which represent the y position of the object.
   * 
   * The y graphical position.
   */
  int y;

public:
  /**
   * \brief Constructor which set default value.
   *
   * The constructor set the default common value at all subclasses. 
   * 
   */
  Equipement();
  
  /**
   * \brief Destructor from the class Equipement.
   * 
   * Destructor from the class
   */
  virtual ~Equipement();

  /**
   * \brief Function wich return the c++ header code from node.
   *
   * This function return a string which contain the header lines from the specified object.
   * This function have to be rewritten in all subclasses.
   * 
   * \return header.
   */
  virtual std::string GenerateHeader() = 0;

  /**
   * \brief Function wich return the c++ code from node.
   *
   * This function return a string which contain the declaration and instanciation of the node.
   * This function have to be rewritten in all subclasses.
   * 
   * \return node.
   */
  virtual std::string GenerateNode() = 0;

  /**
   * \brief Function wich return the c++ code from IpStack.
   *
   * This function return a string which contain the c++ code from the Ipv4 stack declaration and instanciation.
   * This function have to be rewritten in all subclasses.
   * 
   * \return ipStack.
   */
  virtual std::string GenerateIpStack() = 0;
  
  /**
   * \brief Function wich return the c++ code from the ip asssign part.
   *
   * This function return a string wich contain the c++ code from the Ipv4 Assign part. It's about ip and mask assign.
   * This function have to be rewritten in all subclasses;
   * 
   * \return IpAssign.
   */
  virtual std::string GenerateIpAssign() = 0;
  
  /**
   * \brief Procedure used to the the c++ header code.
   * 
   * This procedure is used to set the header c++ code as a string. It's used to generate the code.
   * This procedure have to be rewritted un all subclasses.
   *
   * \param _header the header which have to be set.
   */
  virtual void setHeader(std::string _header) = 0;
  
  /**
   * \brief Procedure to set the node name.
   * 
   * The node name is use to declare and instace the node in the c++ generated code.
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
   * Sometimes this var is used in application like an UdpEcho.
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
   void setPosition(int _x, int _y);

  /**
   * \brief Function wich return the node name.
   *
   * function used to get the node name of the equipement.
   * 
   * \return node name.
   */
  std::string getNodeName();

  /**
   * \brief Function wich return the name of the Ip interface.
   * 
   * Function wich return the ip interface name of the equipement.
   *
   * \return ip interface name.
   */
  std::string getIpInterfaceName();

  /**
   * \brief Function wich return the c++ header code.
   *
   * Function which return the c++ code from the equipement
   * 
   * \return header c++ code.
   */
  std::string getHeader();
  
  /**
   * \brief Function wich return the ip address.
   *
   * Function wich return a string with the ip address.
   * 
   * \return ip.
   */
  std::string getIp();
  
  /**
   * \brief Function wich return a string with the mask.
   * 
   * Function wich return a string with the mask.
   *
   * \return mask.
   */
  std::string getMask();
  
  /**
   * \brief Function which return the x position.
   *
   * Function wich return the graphical x position of the object.
   * 
   * \return x position.
   */
  std::string getX();
  
  /**
   * \brief Function which return the y position.
   *
   * Function wich return the graphical y position of the object.
   * 
   * \return y position.
   */
  std::string getY();
  
   /**
    * \brief Function wich convert int to string.
    *
    * Function wich convert in to string.
    * 
    * \param nbr the number to convert.
    * \return nbr in type string.
    */
   std::string toString(int nbr);
   
   /**
    * \brief Function wich return the node number.
    *
    * Function wich return a string with the node number.
    * 
    * \return node number in type string.
    */
   std::string getIndice();
 
};

#endif /* EQUIPEMENT_H */

