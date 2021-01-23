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
 * \file application-dialog.cpp
 * \brief Application dialog window
 * \author Pierre Weiss
 * \date 2009
 */

#include <QtWidgets>

#include "application-dialog.h"
#include "application-pages.h"

ApplicationDialog::ApplicationDialog(DragWidget *dw)
{
  this->m_dw = dw;
  contentsWidget = new QListWidget;
  contentsWidget->setViewMode(QListView::IconMode);
  contentsWidget->setMovement(QListView::Static);
  contentsWidget->setMaximumWidth(128);
  contentsWidget->setSpacing(12);

  pagesWidget = new QStackedWidget;

  this->m_ping = new PingPage(this, this->m_dw);
  pagesWidget->addWidget(this->m_ping);
  
  this->m_udpEcho = new UdpEchoPage(this, this->m_dw);
  pagesWidget->addWidget(this->m_udpEcho);
  
  this->m_tcp = new TcpPage(this, this->m_dw);
  pagesWidget->addWidget(this->m_tcp);

  QPushButton *closeButton = new QPushButton(tr("Close"));

  createApplications();
  contentsWidget->setCurrentRow(0);

  connect(closeButton, SIGNAL(clicked()), this, SLOT(quit()));

  QHBoxLayout *horizontalLayout = new QHBoxLayout;
  horizontalLayout->addWidget(contentsWidget);
  horizontalLayout->addWidget(pagesWidget, 1);

  QHBoxLayout *buttonsLayout = new QHBoxLayout;
  buttonsLayout->addStretch(1);
  buttonsLayout->addWidget(closeButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(horizontalLayout);
  mainLayout->addStretch(1);
  mainLayout->addSpacing(12);
  mainLayout->addLayout(buttonsLayout);
  setLayout(mainLayout);

  setWindowTitle(tr("Application Dialog"));
}

void ApplicationDialog::quit()
{
  this->m_dw->m_appsPing = false;
  this->m_dw->m_appsUdpEcho = false;
  this->m_dw->m_appsTcp = false;
  this->m_dw->m_appsClient = "";
  this->m_dw->m_appsServer = "";
  emit close();
}

void ApplicationDialog::createApplications()
{
   QListWidgetItem *pingButton = new QListWidgetItem(contentsWidget);
   pingButton->setText(tr("Ping"));
   pingButton->setTextAlignment(Qt::AlignHCenter);
   pingButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

   QListWidgetItem *udpEchoButton = new QListWidgetItem(contentsWidget);
   udpEchoButton->setText(tr("Udp Echo"));
   udpEchoButton->setTextAlignment(Qt::AlignHCenter);
   udpEchoButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

   QListWidgetItem *tcpButton = new QListWidgetItem(contentsWidget);
   tcpButton->setText(tr("Tcp Transfer"));
   tcpButton->setTextAlignment(Qt::AlignHCenter);
   tcpButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  
   connect(contentsWidget,
           SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
           this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ApplicationDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
  if (!current)
  {
    current = previous;
  }

  pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
