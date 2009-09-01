/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
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
 * \brief Hub link subclass.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef HUB_H
#define HUB_H

#include "Link.h"

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief Hub link subclass.
 *
 * This class is a subclass from Link, it create a hub link as a Csma network.
 * 
 */
class Hub : public Link
{
  public:
    /**
     * \brief Constructor.
     * \param _indice the hub number
     */
    Hub(const size_t &_indice);

    /**
     * \brief Destructor.
     */
    virtual ~Hub();

  private:
    /**
     * \brief Function which return the generated headers.
     * \return headers.
     */
    virtual std::vector<std::string> GenerateHeader();

    /**
     * \brief Function which generate the build link code.
     * \return build link code.
     */
    virtual std::vector<std::string> GenerateLink();

    /**
     * \brief Function which return the build of the net device container.
     * \return the net device container.
     */
    virtual std::vector<std::string> GenerateNetDevice();

    /**
     * \brief Function to generate the trace line.
     * \return trace line.
     */
    virtual std::vector<std::string> GenerateTrace();
};

#endif /* HUB_H */

