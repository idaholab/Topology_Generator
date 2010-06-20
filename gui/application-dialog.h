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
 * \file application-dialog.h
 * \brief Application dialog window
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef APPLICATION_DIALOG_H
#define APPLICATION_DIALOG_H

#include <QDialog>
#include "drag-widget.h"
#include "application-pages.h"

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

/**
 * \brief Application dialog window class
 */
class ApplicationDialog : public QDialog
{
  Q_OBJECT

  public:
    /**
     * \brief Application dialog constructor
     * \param dw
     */
    ApplicationDialog(DragWidget *dw);
    
    /**
     * \brief drag widget object
     */
    DragWidget *m_dw;
    
    /**
     * \brief ping page object
     */
    PingPage *m_ping;
    
    /**
     * \brief udp echo page object
     */
    UdpEchoPage *m_udpEcho;

    /**
     * \brief tcp large transfer page object
     */
    TcpPage *m_tcp;

  public slots:
    /**
     * \brief switch to another application
     * \param current
     * \param previous
     */
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    
    /**
     * \brief clean application and quit
     */
    void quit();

  private:
    /**
     * \brief call gui applications
     */
    void createApplications();
    
    /**
     * \brief the content widget list
     */
    QListWidget *contentsWidget;
    
    /**
     * \brief the page widget list
     */
    QStackedWidget *pagesWidget;
};

#endif /* APPLICATION_DIALOG_H */
