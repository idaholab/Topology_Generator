/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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
* \file Application.cpp
* \brief Application Base Class.
* \author Pierre Weiss
* \date 2009
*/

#include "Application.h"
#include "Generator.h"

Application::Application(size_t _indice, std::string _senderNode, std::string _receiverNode, size_t _startTime, size_t _endTime)
{
  this->indice = _indice;
  //this->appName = "";//into child
  this->senderNode = _senderNode;
  this->receiverNode= _receiverNode;
  this->startTime = _startTime;
  this->endTime = _endTime;
  
}

Application::~Application()
{
}

std::string Application::getIndice()
{
  return Generator::toString(this->indice);
}
  
void Application::setIndice(size_t _indice)
{
  this->indice = _indice;
}
  
std::string Application::getAppName()
{
  return this->appName;
}
  
void Application::setAppName(std::string _appName)
{
  this->appName = _appName;
}
  
std::string Application::getSenderNode()
{
  return this->senderNode;
}
  
void Application::setSenderNode(std::string _senderNode)
{
  this->senderNode = _senderNode;
}
  
std::string Application::getReceiverNode()
{
  return this->receiverNode;
}
  
void Application::setReceiverNode(std::string _receiverNode)
{
  this->receiverNode = _receiverNode;
}
 
std::string Application::getStartTime()
{
  return Generator::toString(this->startTime);
}
 
void Application::setStartTime(size_t _startTime)
{
  this->startTime = _startTime;
}
  
std::string Application::getEndTime()
{
  return Generator::toString(this->endTime);
}

size_t Application::getEndTimeNumber()
{
  return this->endTime;
}
 
void Application::setEndTime(size_t _endTime)
{
  this->endTime = _endTime;
}
