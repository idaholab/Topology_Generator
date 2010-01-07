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

Application::Application(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime)
{
  this->m_applicationType = type;
  this->m_indice = indice;
  this->m_senderNode = senderNode;
  this->m_receiverNode = receiverNode;
  this->m_startTime = startTime;
  this->m_endTime = endTime;
}

Application::~Application()
{
}

std::string Application::GetIndice()
{
  return utils::integerToString(this->m_indice);
}

void Application::SetIndice(const size_t &indice)
{
  this->m_indice = indice;
}

std::string Application::GetAppName()
{
  return this->m_appName;
}

void Application::SetAppName(const std::string &appName)
{
  this->m_appName = appName;
}

std::string Application::GetSenderNode()
{
  return this->m_senderNode;
}

void Application::SetSenderNode(const std::string &senderNode)
{
  this->m_senderNode = senderNode;
}

std::string Application::GetReceiverNode()
{
  return this->m_receiverNode;
}

void Application::SetReceiverNode(const std::string &receiverNode)
{
  this->m_receiverNode = receiverNode;
}

std::string Application::GetStartTime()
{
  return utils::integerToString(this->m_startTime);
}

void Application::SetStartTime(const size_t &startTime)
{
  this->m_startTime = startTime;
}

std::string Application::GetEndTime()
{
  return utils::integerToString(this->m_endTime);
}

size_t Application::GetEndTimeNumber()
{
  return this->m_endTime;
}

void Application::SetEndTime(const size_t &endTime)
{
  this->m_endTime = endTime;
}

std::string Application::GetApplicationType()
{
  return this->m_applicationType;
}

