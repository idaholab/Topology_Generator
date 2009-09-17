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
 * \file application.cpp
 * \brief application base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "application.h"
#include "generator.h"

#include "utils.h"

Application::Application(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime)
{
  this->setIndice(m_indice);
  this->setSenderNode(m_senderNode);
  this->setReceiverNode(m_receiverNode);
  this->setStartTime(m_startTime);
  this->setEndTime(m_endTime);
}

Application::~Application()
{
}

std::string Application::getIndice()
{
  return utils::toString(this->indice);
}

void Application::setIndice(const size_t &m_indice)
{
  this->indice = m_indice;
}

std::string Application::getAppName()
{
  return this->appName;
}

void Application::setAppName(const std::string &m_appName)
{
  this->appName = m_appName;
}

std::string Application::getSenderNode()
{
  return this->senderNode;
}

void Application::setSenderNode(const std::string &m_senderNode)
{
  this->senderNode = m_senderNode;
}

std::string Application::getReceiverNode()
{
  return this->receiverNode;
}

void Application::setReceiverNode(const std::string &m_receiverNode)
{
  this->receiverNode = m_receiverNode;
}

std::string Application::getStartTime()
{
  return utils::toString(this->startTime);
}

void Application::setStartTime(const size_t &m_startTime)
{
  this->startTime = m_startTime;
}

std::string Application::getEndTime()
{
  return utils::toString(this->endTime);
}

size_t Application::getEndTimeNumber()
{
  return this->endTime;
}

void Application::setEndTime(const size_t &m_endTime)
{
  this->endTime = m_endTime;
}

