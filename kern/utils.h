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

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <stdexcept>

/**
 * \namespace utils
 * \brief Utils functions.
 */
namespace utils
{

/**
 * \brief Split function as boost::split(...)
 * \param res the vector wich contain the splitted vector
 * \param str the string to split
 * \param separator the split separator
 * \return res vector size
 */
size_t split(std::vector<std::string> &res, std::string str, char separator);

/**
 * \brief Convert size_t to string.
 * \param nb the number to convert
 * \return number in string format
 */
std::string integerToString(const size_t nb);

/**
 * \brief Convert strint to size_t (integer).
 * \param str string to convert
 * \return 0 if success, -1 otherwise
 * \throw std::runtime_exception is thrown if cannot convert
 */
int stringToInteger(const std::string& str) throw (std::runtime_error);

} /* namespace utils */

#endif /* UTILS_H */

