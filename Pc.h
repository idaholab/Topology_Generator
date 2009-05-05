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
* \file Pc.h
* \brief Subclasse from Equipement.
* \author Pierre Weiss
* \date 2009
*/

#ifndef PC_H
#define PC_H

#include "Equipement.h"

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
   * \brief Constructor used for a Pc.
   * 
   * This is the constructor of the Pc class.
   * This object rewrite the virtual method from main class.
   * It also contain the c++ code specific from a Pc.
   * 
   */
  Pc();
  
  /**
   * \brief the destructor of the class.
   * 
   * The class destructor.
   */
  virtual ~Pc();
  
  /**
   * \brief Function witch return the header c++ code.
   *
   * Function wich return a string with the header c++ code from a Pc.
   * 
   * \return header.
   */
  virtual std::vector<std::string> GenerateHeader();
  
  /**
   * \brief Function witch return the node c++ code.
   *
   * Function wich return a string with the node c++ code from a Pc.
   * 
   * \return node.
   */
  virtual std::vector<std::string> GenerateNode();
  
  /**
   * \brief Function witch return the ip stack c++ code.
   *
   * Function wich return a string with the ip stack c++ code from a Pc.
   * 
   * \return ip stack.
   */
  virtual std::vector<std::string> GenerateIpStack();
  
  /**
   * \brief Function witch return the ip assign c++ code.
   *
   * Function wich return a string with the ip assign c++ code from a Pc.
   * 
   * \return ip assign.
   */
  virtual std::vector<std::string> GenerateIpAssign();
  
};

#endif /* PC_H */

