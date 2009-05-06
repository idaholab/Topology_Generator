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
* \file Hub.h
* \brief Hub link subclasse.
* \author Pierre Weiss
* \date 2009
*/

#ifndef HUB_H
#define HUB_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

class Hub : public Link
{
public:
  Hub(size_t _indice);
  virtual ~Hub();
  
private:
  virtual std::vector<std::string> GenerateHeader();
  virtual std::vector<std::string> GenerateLink();
  virtual std::vector<std::string> GenerateNetDevice();
  
};

#endif /* HUB_H */
