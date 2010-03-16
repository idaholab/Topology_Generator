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
 * \file application-pages.h
 * \brief Application pages
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef APPLICATION_PAGES_H
#define APPLICATION_PAGES_H

#include <QWidget>
#include "drag-widget.h"

/**
 * \brief Ping application page
 */
class PingPage : public QWidget
{
  Q_OBJECT

  private:
    /**
     * \brief parent qwidget object
     */
    QWidget *m_parent;

    /**
     * \brief drag widget object
     */
    DragWidget *m_dw;
    
    /**
     * \brief ping application start time
     */
    QLineEdit *m_startTime;
    
    /**
     * \brief ping application end time
     */
    QLineEdit *m_endTime;
   
  public:
    /**
     * \brief Constructor of application gui
     * \param parent
     * \param dw
     */
    PingPage(QWidget *parent = 0, DragWidget *dw = 0);

    /**
     * \brief clean and rebuild gui
     */
    void Refresh();
    
    /**
     * \brief application client node
     */
    std::string m_leftNode;

    /**
     * \brief application server node
     */
    std::string m_rightNode;

  public slots:
    /**
     * \brief proc to choose nodes
     */
    void Choose();

    /**
     * \brief add the application
     */
    void Add();
};

/**
 * \brief Udp Echo application page
 */
class UdpEchoPage : public QWidget
{
  Q_OBJECT

  private:
    /**
     * \brief parent qwidget object
     */
    QWidget *m_parent;

    /**
     * \brief drag widget object
     */
    DragWidget *m_dw;
    
    /**
     * \brief application start time
     */
    QLineEdit *m_startTime;

    /**
     * \brief application end time
     */
    QLineEdit *m_endTime;

    /**
     * \brief application port
     */
    QLineEdit *m_port;

  public:
    /**
     * \brief Constructor of application gui
     * \param parent
     * \param dw
     */
    UdpEchoPage(QWidget *parent = 0, DragWidget *dw = 0);

    /**
     * \brief clean and rebuild gui
     */
    void Refresh();
    
    /**
     * \brief application client node
     */
    std::string m_leftNode;

    /**
     * \brief application server node
     */
    std::string m_rightNode;

  public slots:
    /**
     * \brief proc to choose nodes
     */
    void Choose();

    /**
     * \brief add the application
     */
    void Add();
};

/**
 * \brief Tcp large transfer application page
 */
class TcpPage : public QWidget
{
  Q_OBJECT

  private:
    /**
     * \brief parent qwidget object
     */
    QWidget *m_parent;

    /**
     * \brief drag widget object
     */
    DragWidget *m_dw;
    
    /**
     * \brief application start time
     */
    QLineEdit *m_startTime;

    /**
     * \brief application end time
     */
    QLineEdit *m_endTime;

    /**
     * \brief application port
     */
    QLineEdit *m_port;

  public:
    /**
     * \brief Constructor of application gui
     * \param parent
     * \param dw
     */
    TcpPage(QWidget *parent = 0, DragWidget *dw = 0);

    /**
     * \brief clean and rebuild gui
     */
    void Refresh();

    /**
     * \brief application client node
     */
    std::string m_leftNode;

    /**
     * \brief application server node
     */
    std::string m_rightNode;

  public slots:
    /**
     * \brief proc to choose nodes
     */
    void Choose();

    /**
     * \brief add the application
     */
    void Add();
};

#endif /* APPLICATION_PAGES_H */
