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
 * \brief Application base class.
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
 *    class NewApplication : public Application
 *    {
 *      NewApplication(...);
 *      ~NewApplication();
 *      
 *      virtual std::vector<std::string> GenerateHeader();
 *      virtual std::vector<std::string> GenerateApplicationCpp(std::string, size_t);
 *      virtual std::vector<std::string> GenerateApplicationPython(std::string, size_t);
 *    }
 */
class Application
{
  private:
    /**
     * \brief Application number.
     */
    size_t m_indice;

    /**
     * \brief Application name.
     */
    std::string m_appName;

    /**
     * \brief Pinger sender node.
     */
    std::string m_senderNode;

    /**
     * \brief Pinger receiver node.
     */
    std::string m_receiverNode;

    /**
     * \brief Application start time.
     */
    size_t m_startTime;

    /**
     * \brief Application end time.
     */
    size_t m_endTime;

    /**
     * \brief Application type.
     */
    std::string m_applicationType;

  public:
    /**
     * \brief Constructor.
     * \param type application type
     * \param indice application number
     * \param senderNode sender node
     * \param receiverNode receiver node
     * \param startTime application start time
     * \param endTime application end time
     */
    Application(const std::string &type, const size_t &indice, const std::string &senderNode, const std::string &receiverNode, const size_t &startTime, const size_t &endTime);

    /**
     * \brief Destructor.
     */
    virtual ~Application();

    /**
     * \brief Generate the headers.
     * \return headers
     */
    virtual std::vector<std::string> GenerateHeader() = 0;

    /**
     * \brief Generate the application C++ code.
     * \param netDeviceContainer is the ns3 net device containe
     * \param numberIntoNetDevice is the place from the sender node in the assigned ip network
     * \param numberIntoNetDevice example sender node is 192.168.0.5, then the number is 5
     * \return code from the application
     */
    virtual std::vector<std::string> GenerateApplicationCpp(std::string netDeviceContainer, size_t numberIntoNetDevice) = 0;

    /**
     * \brief Generate the application python code.
     * \param netDeviceContainer is the ns3 net device containe
     * \param numberIntoNetDevice is the place from the sender node in the assigned ip network
     * \param numberIntoNetDevice example sender node is 192.168.0.5, then the number is 5
     * \return code from the application
     */
    virtual std::vector<std::string> GenerateApplicationPython(std::string netDeviceContainer, size_t numberIntoNetDevice) = 0;

    /**
     * \brief Get application number.
     * \return application number
     */
    std::string GetIndice();

    /**
     * \brief Get application number.
     * \param indice new indice
     */
    void SetIndice(const size_t &indice);

    /**
     * \brief Get application node name.
     * \return application node name
     */
    std::string GetAppName();

    /**
     * \brief Set application name.
     * \param appName new application name
     */
    void SetAppName(const std::string &appName);

    /**
     * \brief Get sender node name.
     * \return sender node name
     */
    std::string GetSenderNode();

    /**
     * \brief Set sender node name.
     * \param senderNode new sender node name
     */
    void SetSenderNode(const std::string &senderNode);

    /**
     * \brief Get receiver node name.
     * \return receiver node name
     */
    std::string GetReceiverNode();

    /**
     * \brief Set receiver node name.
     * \param receiverNode new receiver node name
     */
    void SetReceiverNode(const std::string &receiverNode);

    /**
     * \brief Get application start time.
     * \return application start time
     */
    std::string GetStartTime();

    /**
     * \brief Set application start time.
     * \param startTime application start time
     */
    void SetStartTime(const size_t &startTime);

    /**
     * \brief Get application end time.
     * \return application end time
     */
    std::string GetEndTime();

    /**
     * \brief Get application end time.
     * \return end time formatted into number
     */
    size_t GetEndTimeNumber();

    /**
     * \brief Set application end time.
     * \param m_endTime application end time
     */
    void SetEndTime(const size_t &m_endTime);

    /**
     * \brief Get application type.
     * \return application type
     */
    std::string GetApplicationType();
};

#endif /* APPLICATION_H */

