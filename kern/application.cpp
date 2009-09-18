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
 * \brief Application base class.
 * \author Pierre Weiss
 * \date 2009
 */

#include "application.h"
#include "generator.h"

#include "utils.h"

Application::Application(const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime)
{
  this->setIndice(indice);
  this->setSenderNode(senderNode);
  this->setReceiverNode(receiverNode);
  this->setStartTime(startTime);
  this->setEndTime(endTime);
}

Application::~Application()
{
}

std::string Application::getIndice()
{
  return utils::toString(this->m_indice);
}

void Application::setIndice(const size_t &indice)
{
  this->m_indice = indice;
}

std::string Application::getAppName()
{
  return this->m_appName;
}

void Application::setAppName(const std::string &appName)
{
  this->m_appName = appName;
}

std::string Application::getSenderNode()
{
  return this->m_senderNode;
}

void Application::setSenderNode(const std::string &senderNode)
{
  this->m_senderNode = senderNode;
}

std::string Application::getReceiverNode()
{
  return this->m_receiverNode;
}

void Application::setReceiverNode(const std::string &receiverNode)
{
  this->m_receiverNode = receiverNode;
}

std::string Application::getStartTime()
{
  return utils::toString(this->m_startTime);
}

void Application::setStartTime(const size_t &startTime)
{
  this->m_startTime = startTime;
}

std::string Application::getEndTime()
{
  return utils::toString(this->m_endTime);
}

size_t Application::getEndTimeNumber()
{
  return this->m_endTime;
}

void Application::setEndTime(const size_t &endTime)
{
  this->m_endTime = endTime;
}

