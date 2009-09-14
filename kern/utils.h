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
 * \file utils.h
 * \brief Utils functions.
 */

#include <vector>
#include <string>

/**
 * \namespace utils
 * \brief Utils functions.
 */
namespace utils
{

/**
 * \brief split function as boost::split(...)
 * \param res the vector wich contain the splitted vector.
 * \param str the string to split
 * \param separator the split separator
 * \return size_t the res vector size.
 */
size_t split(std::vector<std::string> &res, std::string str, char separator);

/**
 * \brief Function to convert size_t to string.
 * \param nb the number to convert.
 * \return the string of the number.
 */
std::string toString(const size_t nb);

} /* namespace utils */

