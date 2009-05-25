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
* \file Configuration.h
* \brief The GUI configuration file.
* \author Pierre Weiss
* \date 2009
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtGui>

/**
 * \ingroup generator
 * \brief The configuration gui file.
 *
 * This class create the GUI pop up configuration.
 * You can choose on it the differents options like checksum calc or not, ...
 */
class Configuration : public QWidget
{
	public:
	  /**
	   * \brief Configuration constructor.
	   * this constructor create the configuration "pop up"
	   */
		Configuration();
		
	private slots:
	  /**
	   * \brief Procedure called on OK button.
	   */
		void accept();
		
		/**
		 * \brief Procedure called on Cancel button.
		 */
		void reject();
    
};


#endif /* CONFIGURATION_H */
