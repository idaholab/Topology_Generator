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

#ifndef PC_H
#define PC_H

#include "Equipement.h"

using namespace std;
#include <iostream>
#include <string>
#include <vector>


/**
 * \ingroup generator
 * \brief Subclasse from Equipement.
 *
 * This class is a subclass from main class Equipement.
 * It reprensent a simple pc.
 * 
 */
class Pc : public Equipement
{
public:
  /**
   * \fn Pc();
   * \brief Constructor used for a Pc.
   * 
   * This is the constructor of the Pc class.
   * This object rewrite the virtual method from main class.
   * It also contain the c++ code specific from a Pc.
   * 
   */
  Pc();
  virtual ~Pc();
  
  /**
   * \fn string GenerateHeader();
   * \brief Function witch return the header c++ code.
   *
   * Function wich return a string with the header c++ code from a Pc.
   * 
   * \return header.
   */
  virtual string GenerateHeader();
  
  /**
   * \fn string GenerateNode();
   * \brief Function witch return the node c++ code.
   *
   * Function wich return a string with the node c++ code from a Pc.
   * 
   * \return node.
   */
  virtual string GenerateNode();
  
  /**
   * \fn string GenerateIpStack();
   * \brief Function witch return the ip stack c++ code.
   *
   * Function wich return a string with the ip stack c++ code from a Pc.
   * 
   * \return ip stack.
   */
  virtual string GenerateIpStack();
  
  /**
   * \fn string GenerateIpAssign();
   * \brief Function witch return the ip assign c++ code.
   *
   * Function wich return a string with the ip assign c++ code from a Pc.
   * 
   * \return ip assign.
   */
  virtual string GenerateIpAssign();
  
  /**
   * \fn void setHeader(string _header);
   * \brief Function witch set the header c++ code.
   *
   * Function wich set the c++ code from the Pc.
   * 
   * \param _header, the new header string.
   */
  virtual void setHeader(string _header);

};

#endif 
