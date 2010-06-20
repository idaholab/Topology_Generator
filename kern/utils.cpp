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
 */

/**
 * \file utils.cpp
 * \brief Utils functions.
 */

#include <stdint.h>
#include <sstream>

#include "utils.h"

namespace utils
{

size_t split(std::vector<std::string> &res, std::string str, char separator)
{
  res.clear();

  std::string::size_type stTemp = str.find(separator);

  while(stTemp != std::string::npos)
  {
    res.push_back(str.substr(0, stTemp));
    str = str.substr(stTemp + 1);
    stTemp = str.find(separator);
  }

  res.push_back(str);

  return res.size();
}

std::string integerToString(const size_t nb)
{
  std::ostringstream out;
  out << nb;

  return out.str();
}

int stringToInteger(const std::string& str) throw(std::runtime_error)
{
  uint64_t ret = 0;
  std::istringstream in(str);

  if(!(in >> ret))
  {
    throw std::runtime_error("Cannot convert string to uint64_t");
    return -1;
  }
  return ret;
}

} /* namespace utils */

