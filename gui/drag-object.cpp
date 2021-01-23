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

#include <QtWidgets>
#include <iostream>

#include "drag-object.h"
#include "drag-widget.h"

DragObject::DragObject(QWidget *parent) : QLabel(parent)
{
  this->m_name = "";
  this->m_tooltip = "";
}

DragObject::~DragObject()
{
}

void DragObject::SetName(const std::string &name)
{
  this->m_name = name;
}

std::string DragObject::GetName()
{
  return this->m_name;
}

void DragObject::Destroy()
{
  this->m_name = "deleted";
  this->destroy();
}

void DragObject::SetToolTipText(const QString &str)
{
  this->m_tooltip = str;
}

QString DragObject::GetToolTipText()
{
  return this->m_tooltip;
}

