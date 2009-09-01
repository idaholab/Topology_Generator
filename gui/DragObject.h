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
 * \file DragObject.h
 * \brief The dragged object file.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef DRAGOBJECT_H
#define DRAGOBJECT_H

#include <vector>
#include <QtGui>

#include "DragWidget.h"

/**
 * \ingroup generator
 * \brief The dragged object.
 *
 * This class represent the dragged object.
 */
class DragObject : public QLabel
{
  public:
    /**
     * \brief Constructor
     * \param parent the qwidget parent.
     */
    DragObject(QWidget *parent);

    /**
     * \brief destructor
     */
    ~DragObject();

    /**
     * \brief procedure to set the name from the dragged object.
     * \param _name the new name.
     */
    void setName(const std::string &_name);

    /**
     * \brief function to get the dragged object name.
     * \return name
     */
    std::string getName();

    /**
     * \brief destroy object from qwidget.
     */
    void Destroy();

  private:
    /**
     * \brief attribute which reprensent the name. 
     */
    std::string name;

};

#endif /* END DRAGOBJECT_H */
