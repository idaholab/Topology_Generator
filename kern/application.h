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
 * \file application.h
 * \brief application base class.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The main class of applications.
 *
 *  The applications class is the main class of all applications.
 *  
 *  Usage : (Call a subclass)
 *    - ping
 *    - tcp-large-transfert
 *    - udp-echo
 *
 *  To add a new application, please see the subclasse for example.
 *  example of .h file :
 *
 *    include "application.h"
 *    class new-class : public Application
 *    {
 *      new-class(...);
 *      ~new-class();
 *      
 *      virtual std::vector<std::string> GenerateHeader();
 *      virtual std::vector<std::string> GenerateApplication(std::string, size_t);
 *    }
 */
class Application
{
  private:
    /**
     * \brief application number.
     */
    size_t indice;

    /**
     * \brief application name.
     */
    std::string appName;

    /**
     * \brief pinger sender node.
     */
    std::string senderNode;

    /**
     * \brief pinger receiver node.
     */
    std::string receiverNode;

    /**
     * \brief application start time.
     */
    size_t startTime;

    /**
     * \brief application end time.
     */
    size_t endTime;

  public:
    /**
     * \brief constructor.
     * \param m_indice application number
     * \param m_senderNode sender node
     * \param m_receiverNode receiver node
     * \param m_startTime application start time
     * \param m_endTime application end time
     */
    Application(const size_t &m_indice, const std::string &m_senderNode, const std::string &m_receiverNode, const size_t &m_startTime, const size_t &m_endTime);

    /**
     * \brief destructor.
     */
    virtual ~Application();

    /**
     * \brief generate the headers.
     * \return headers.
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief generate the application code.
     * \param netDeviceContainer is the ns3 net device containe
     * \param numberIntoNetDevice is the place from the sender node in the assigned ip network.
     * \param numberIntoNetDevice example sender node is 192.168.0.5, then the number is 5.
     * \return code from the application.
     */
    virtual std::vector<std::string> GenerateApplication(std::string netDeviceContainer, size_t numberIntoNetDevice) = 0;

    /**
     * \brief get application number.
     * \return application number.
     */
    std::string getIndice();

    /**
     * \brief set application number.
     * \param m_indice new indice.
     */
    void setIndice(const size_t &m_indice);

    /**
     * \brief get application node name.
     * \return application node name.
     */
    std::string getAppName();

    /**
     * \brief set application name.
     * \param m_appName new application name.
     */
    void setAppName(const std::string &m_appName);

    /**
     * \brief get sender node name.
     * \return sender node name.
     */
    std::string getSenderNode();

    /**
     * \brief set sender node name.
     * \param m_senderNode new sender node name.
     */
    void setSenderNode(const std::string &m_senderNode);

    /**
     * \brief get receiver node name.
     * \return receiver node name.
     */
    std::string getReceiverNode();

    /**
     * \brief set receiver node name.
     * \param m_receiverNode new receiver node name.
     */
    void setReceiverNode(const std::string &m_receiverNode);

    /**
     * \brief get application start time.
     * \return application start time.
     */
    std::string getStartTime();

    /**
     * \brief set application start time.
     * \param m_startTime application start time.
     */
    void setStartTime(const size_t &m_startTime);

    /**
     * \brief get application end time.
     * \return application end time.
     */
    std::string getEndTime();

    /**
     * \brief get application end time.
     * \return end time formatted into number.
     */
    size_t getEndTimeNumber();

    /**
     * \brief set application end time.
     * \param m_endTime application end time.
     */
    void setEndTime(const size_t &m_endTime);

};

#endif /* APPLICATION_H */

