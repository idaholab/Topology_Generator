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
 * \file gui-utils.h
 * \brief gui utils file.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QtWidgets>

#include "generator.h"
#include "drag-widget.h"

/**
 * \namespace gui utils
 * \brief gui utils functions.
 */
namespace guiUtils
{

/**
 * \brief Generate and write xml into save file.
 * \param writer the xml writter
 * \param gen the generator object
 * \param dw the drag widget object
 */
void saveXml(QXmlStreamWriter *writer, Generator *gen, DragWidget *dw);

/**
 * \brief Load an xml file into the generator.
 * \param reader the xml reader
 * \param gen the generator object
 * \param dw the drag widget object
 */
void loadXml(QXmlStreamReader *reader, Generator *gen, DragWidget *dw);

/**
 * \brief Procedure used to parse xml file.
 * \param reader the qt xml reader object
 */
void jumpToNextStartElement(QXmlStreamReader *reader);

/**
 * \brief Function used to test if an equipement is an NetworkHardware member.
 * \param equipement the equipement to test
 */
bool isNetworkHardware(const std::string &equipement);

} /* namespace guiUtils */

#endif /* GUIUTILS_H */


