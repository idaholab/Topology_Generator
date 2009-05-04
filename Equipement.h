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

#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

using namespace std;
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
  string indice;
  string nodeName;
  string ip;
  string mask;
  string ipInterfaceName;
  string header;
  int x;
  int y;

public:
  /**
   * \fn Equipement();
   * \brief Constructor which set default value.
   *
   * The constructor set the default common value at all subclasses. 
   * 
   */
  Equipement();
  virtual ~Equipement();

  /**
   * \fn virtual string GenerateHeader(){};
   * \brief Function wich return the c++ header code from node.
   *
   * This function return a string which contain the header lines from the specified object.
   * This function have to be rewritten in all subclasses.
   * 
   * \return header.
   */
  virtual string GenerateHeader(){};

  /**
   * \fn virtual string GenerateNode(){};
   * \brief Function wich return the c++ code from node.
   *
   * This function return a string which contain the declaration and instanciation of the node.
   * This function have to be rewritten in all subclasses.
   * 
   * \return node.
   */
  virtual string GenerateNode(){};

  /**
   * \fn virtual string GenerateIpStack(){};
   * \brief Function wich return the c++ code from IpStack.
   *
   * This function return a string which contain the c++ code from the Ipv4 stack declaration and instanciation.
   * This function have to be rewritten in all subclasses.
   * 
   * \return ipStack.
   */
  virtual string GenerateIpStack(){};
  
  /**
   * \fn virtual string GenerateIpAssign(){};
   * \brief Function wich return the c++ code from the ip asssign part.
   *
   * This function return a string wich contain the c++ code from the Ipv4 Assign part. It's about ip and mask assign.
   * This function have to be rewritten in all subclasses;
   * 
   * \return IpAssign.
   */
  virtual string GenerateIpAssign(){};
  
  /**
   * \fn virtual void setHeader(string _header){};
   * \brief Procedure used to the the c++ header code.
   * 
   * This procedure is used to set the header c++ code as a string. It's used to generate the code.
   * This procedure have to be rewritted un all subclasses.
   *
   * \param _header the header which have to be set.
   */
  virtual void setHeader(string _header){};
  
  /**
   * \fn void setNodeName(string _nodeName);
   * \brief Procedure to set the node name.
   * 
   * The node name is use to declare and instace the node in the c++ generated code.
   *
   * \param _nodename the string which containe the node name.
   */
  void setNodeName(string _nodeName);

  /**
   * \fn void setIpv4Address(string _ip, string _mask);
   * \brief Procedure to set the ip and mask.
   *
   * The ip have to be inserted as an ipv4 address. Example :10.0.0.1
   * Mask example : 255.255.255.0
   * 
   * \param _ip the ip.
   * \param _mask the mask.
   */
  void setIpv4Address(string _ip, string _mask);

  /**
   * \fn void setIpInterfaceName(string _ipInterfaceName);
   * \brief Procedure to set the Ip interface name.
   * 
   * This procedure is used to the the ipInterfaceName. 
   * Sometimes this var is used in application like an UdpEcho.
   *
   * \param _ipInterfaceName
   */
  void setIpInterfaceName(string _ipInterfaceName);
  
  /**
   * \fn void setPosition(int _x, int _y);
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
   * \fn string getNodeName();
   * \brief Function wich return the node name.
   *
   * function used to get the node name of the equipement.
   * 
   * \return node name.
   */
  string getNodeName();

  /**
   * \fn string getIpInterfaceName();
   * \brief Function wich return the name of the Ip interface.
   * 
   * Function wich return the ip interface name of the equipement.
   *
   * \return ip interface name.
   */
  string getIpInterfaceName();

  /**
   * \fn string getHeader();
   * \brief Function wich return the c++ header code.
   *
   * Function which return the c++ code from the equipement
   * 
   * \return header c++ code.
   */
  string getHeader();
  
  /**
   * \fn string getIp();
   * \brief Function wich return the ip address.
   *
   * Function wich return a string with the ip address.
   * 
   * \return ip.
   */
  string getIp();
  
  /**
   * \fn string getMask();
   * \brief Function wich return a string with the mask.
   * 
   * Function wich return a string with the mask.
   *
   * \return mask.
   */
  string getMask();
  
  /**
   * \fn string getX();
   * \brief Function which return the x position.
   *
   * Function wich return the graphical x position of the object.
   * 
   * \return x position.
   */
  string getX();
  
  /**
   * \fn string getY();
   * \brief Function which return the y position.
   *
   * Function wich return the graphical y position of the object.
   * 
   * \return y position.
   */
  string getY();
  
   /**
    * \fn string toString(int nbr);
    * \brief Function wich convert int to string.
    *
    * Function wich convert in to string.
    * 
    * \param nbr the number to convert.
    * \return nbr in type string.
    */
   string toString(int nbr);
   
   /**
    * \fn string getIndice();
    * \brief Function wich return the node number.
    *
    * Function wich return a string with the node number.
    * 
    * \return node number in type string.
    */
   string getIndice();
 
};

#endif 
