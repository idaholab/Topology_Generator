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
 * \file drag-object.h
 * \brief The dragged object file.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef DRAG_OBJECT_H
#define DRAG_OBJECT_H

#include <vector>
#include <QtGui>

#include "drag-widget.h"

/**
 * \ingroup generator
 * \brief Dragged object.
 *
 * This class represents a dragged object.
 */
class DragObject : public QLabel
{
  public:
    /**
     * \brief Constructor.
     * \param parent the qwidget parent.
     */
    DragObject(QWidget *parent);

    /**
     * \brief Dstructor.
     */
    ~DragObject();

    /**
     * \brief Set the name for the dragged object.
     * \param name the new name
     */
    void setName(const std::string &name);

    /**
     * \brief Get the dragged object name.
     * \return name
     */
    std::string getName();

    /**
     * \brief Destroy object from qwidget.
     */
    void Destroy();

  private:
    /**
     * \brief Name of the dragged object. 
     */
    std::string name;
};

#endif /* DRAG_OBJECT_H */

