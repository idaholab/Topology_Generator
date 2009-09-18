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
 * \file point-to-point.h
 * \brief Point-to-point link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef POINT_TO_POINT_H
#define POINT_TO_POINT_H

#include "link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Point-to-point link subclass.
 *
 *  The point-to-point class is a subclass of link.
 *
 *  This class represent an point-to-point link between two networks equipement.
 *  It re-writte some methods which are called to generate the ns3 code.
 *
 *  Usage:
 *    - Create an hub with generator object.
 *    - Install nodes with install method.
 */
class PointToPoint : public Link
{
  public:
    /**
     * \brief Constructor.
     * \param indice point-to-point number into the link generator vector
     */
    PointToPoint(const size_t &indice);

    /**
     * \brief Destructor.
     */
    virtual ~PointToPoint();

  private:
    /**
     * \brief Generated headers code.
     * \return headers code
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Generate link code.
     * \return link code
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief Generate net device container.
     * \return net device container code
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief Generate trace line code.
     * \return trace line code
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* POINT_TO_POINT_H */

