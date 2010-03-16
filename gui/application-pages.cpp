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
 * \file application-pages.cpp
 * \brief Application pages
 * \author Pierre Weiss
 * \date 2009
 */

#include <QtGui>

#include "application-pages.h"
#include "main-window.h"

PingPage::PingPage(QWidget *parent, DragWidget *dw) : QWidget(parent)
{
  this->m_dw = dw;
  this->m_parent = parent;
  this->Refresh();
 }

void PingPage::Refresh()
{
  for(size_t i = 0; i < (size_t)this->children().size(); i++)
  {
    delete this->children().at(i);
  }
  delete this->layout();

  QGroupBox *appsGroup = new QGroupBox(tr("Ping Application"));
 
  QGridLayout *layout = new QGridLayout;
 
  /* SENDER */
  std::string senderLabelText("");
  if(this->m_leftNode != "")
  {
    senderLabelText = "Sender : " + this->m_leftNode;
  }
  else
  {
    senderLabelText = "Sender : ___________";
  }
  QLabel *senderLabel = new QLabel(QString(senderLabelText.c_str()));
  QPushButton *senderButton = new QPushButton("Choose");
  connect(senderButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );
  
  layout->addWidget(senderLabel, 2, 0);
  layout->addWidget(senderButton, 2, 1);

  /* TARGET */
  std::string targetLabelText("");
  if(this->m_rightNode != "")
  {
    targetLabelText = "Target : " + this->m_rightNode;
  }
  else
  {
    targetLabelText = "Target : ___________";
  }
  QLabel *targetLabel = new QLabel(QString(targetLabelText.c_str()));
  QPushButton *targetButton = new QPushButton("Choose");
  connect(targetButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );

  layout->addWidget(targetLabel, 3, 0);
  layout->addWidget(targetButton, 3, 1);

  /* TIME */
  // Start
  QLabel *lstartTime = new QLabel("Start time (s):");
  m_startTime = new QLineEdit();
 
  layout->addWidget(lstartTime, 5, 0);
  layout->addWidget(m_startTime, 5, 1);

  // End
  QLabel *lendTime = new QLabel("End time (s):");
  m_endTime = new QLineEdit();
 
  layout->addWidget(lendTime, 6, 0);
  layout->addWidget(m_endTime, 6, 1);
 
  /* Add apps Button*/
  QPushButton *addButton = new QPushButton(tr("Add application"));
  connect(addButton, SIGNAL( clicked() ), this, SLOT( Add() ) );
  
  /* layout ... */
  appsGroup->setLayout(layout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(appsGroup);
  mainLayout->addWidget(addButton);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void PingPage::Choose()
{
  this->m_parent->hide();
  this->m_dw->m_appsPing = true;
}

void PingPage::Add()
{
  size_t startTime = m_startTime->text().toInt();
  size_t endTime = m_endTime->text().toInt();

  if( (this->m_leftNode != "" && this->m_rightNode != "") &&
      startTime < endTime)
  {
    // Application form seems to be valid
    this->m_dw->m_mw->GetGenerator()->AddApplication("Ping", this->m_leftNode, this->m_rightNode, startTime, endTime);
    QMessageBox::about(this, "Ping", "Ping successfull installed.");

    // close the application window
    this->m_parent->close();
    this->m_dw->m_appsPing = false;
  }
  else
  {
    // There is an error !
    if(this->m_leftNode == "" || this->m_rightNode == "")
    {
      QMessageBox::about(this, "ping", "Please choose the sender and target machines.");
    }
    else if(startTime >= endTime)
    {
      QMessageBox::about(this, "Ping", "Start time can't be greather than end time.");
    }
    else
    {
      QMessageBox::about(this, "Ping", "An error occured, please verify your params.");
    }
  }

}

//
// Udp Echo
//
UdpEchoPage::UdpEchoPage(QWidget *parent, DragWidget *dw) : QWidget(parent)
{ 
  this->m_dw = dw;
  this->m_parent = parent;
  this->Refresh();
}

void UdpEchoPage::Refresh()
{
  for(size_t i = 0; i < (size_t)this->children().size(); i++)
  {
    delete this->children().at(i);
  }
  delete this->layout();

  QGroupBox *appsGroup = new QGroupBox(tr("Udp Echo Application"));
 
  QGridLayout *layout = new QGridLayout;
 
  /* SENDER */
  std::string senderLabelText("");
  if(this->m_leftNode != "")
  {
    senderLabelText = "Sender : " + this->m_leftNode;
  }
  else
  {
    senderLabelText = "Sender : ___________";
  }
  QLabel *senderLabel = new QLabel(QString(senderLabelText.c_str()));
  QPushButton *senderButton = new QPushButton("Choose");
  connect(senderButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );
  
  layout->addWidget(senderLabel, 2, 0);
  layout->addWidget(senderButton, 2, 1);

  /* TARGET */
  std::string targetLabelText("");
  if(this->m_rightNode != "")
  {
    targetLabelText = "Target : " + this->m_rightNode;
  }
  else
  {
    targetLabelText = "Target : ___________";
  }
  QLabel *targetLabel = new QLabel(QString(targetLabelText.c_str()));
  QPushButton *targetButton = new QPushButton("Choose");
  connect(targetButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );

  layout->addWidget(targetLabel, 3, 0);
  layout->addWidget(targetButton, 3, 1);

  /* TIME */
  // Start
  QLabel *lstartTime = new QLabel("Start time (s):");
  m_startTime = new QLineEdit();
 
  layout->addWidget(lstartTime, 5, 0);
  layout->addWidget(m_startTime, 5, 1);

  // End
  QLabel *lendTime = new QLabel("End time (s):");
  m_endTime = new QLineEdit();
 
  layout->addWidget(lendTime, 6, 0);
  layout->addWidget(m_endTime, 6, 1);

  /* Port */
  QLabel *lport = new QLabel("Port number:");
  m_port = new QLineEdit();

  layout->addWidget(lport, 7, 0);
  layout->addWidget(m_port, 7, 1);
 
  /* Add apps Button*/
  QPushButton *addButton = new QPushButton(tr("Add application"));
  connect(addButton, SIGNAL( clicked() ), this, SLOT( Add() ) );
  
  /* layout ... */
  appsGroup->setLayout(layout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(appsGroup);
  mainLayout->addWidget(addButton);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void UdpEchoPage::Choose()
{
  this->m_parent->hide();
  this->m_dw->m_appsUdpEcho = true;
}

void UdpEchoPage::Add()
{
  size_t startTime = m_startTime->text().toInt();
  size_t endTime = m_endTime->text().toInt();
  size_t port = m_port->text().toInt();

  if( (this->m_leftNode != "" && this->m_rightNode != "") &&
      startTime < endTime && port != 0 && port > 0)
  {
    // Application form seems to be valid
    this->m_dw->m_mw->GetGenerator()->AddApplication("UdpEcho", this->m_leftNode, this->m_rightNode, startTime, endTime, port);
    QMessageBox::about(this, "Udp Echo", "Udp Echo successfull installed.");

    // close the application window
    this->m_parent->close();
    this->m_dw->m_appsUdpEcho = false;
  }
  else
  {
    // There is an error !
    if(this->m_leftNode == "" || this->m_rightNode == "")
    {
      QMessageBox::about(this, "Udp Echo", "Please choose the sender and target machines.");
    }
    else if(startTime >= endTime)
    {
      QMessageBox::about(this, "Udp Echo", "Start time can't be greather than end time.");
    }
    else
    {
      QMessageBox::about(this, "Udp Echo", "An error occured, please verify your params.");
    }
  }
}

//
// Tcp Large Transfer
//

TcpPage::TcpPage(QWidget *parent, DragWidget *dw) : QWidget(parent)
{
  this->m_dw = dw;
  this->m_parent = parent;
  this->Refresh();
 }

void TcpPage::Refresh()
{
  for(size_t i = 0; i < (size_t)this->children().size(); i++)
  {
    delete this->children().at(i);
  }
  delete this->layout();

  QGroupBox *appsGroup = new QGroupBox(tr("Tcp Large Transfer Application"));
 
  QGridLayout *layout = new QGridLayout;
 
  /* SENDER */
  std::string senderLabelText("");
  if(this->m_leftNode != "")
  {
    senderLabelText = "Sender : " + this->m_leftNode;
  }
  else
  {
    senderLabelText = "Sender : ___________";
  }
  QLabel *senderLabel = new QLabel(QString(senderLabelText.c_str()));
  QPushButton *senderButton = new QPushButton("Choose");
  connect(senderButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );
  
  layout->addWidget(senderLabel, 2, 0);
  layout->addWidget(senderButton, 2, 1);

  /* TARGET */
  std::string targetLabelText("");
  if(this->m_rightNode != "")
  {
    targetLabelText = "Target : " + this->m_rightNode;
  }
  else
  {
    targetLabelText = "Target : ___________";
  }
  QLabel *targetLabel = new QLabel(QString(targetLabelText.c_str()));
  QPushButton *targetButton = new QPushButton("Choose");
  connect(targetButton, SIGNAL( clicked() ), this, SLOT( Choose() ) );

  layout->addWidget(targetLabel, 3, 0);
  layout->addWidget(targetButton, 3, 1);

  /* TIME */
  // Start
  QLabel *lstartTime = new QLabel("Start time (s):");
  m_startTime = new QLineEdit();
 
  layout->addWidget(lstartTime, 5, 0);
  layout->addWidget(m_startTime, 5, 1);

  // End
  QLabel *lendTime = new QLabel("End time (s):");
  m_endTime = new QLineEdit();
 
  layout->addWidget(lendTime, 6, 0);
  layout->addWidget(m_endTime, 6, 1);

  /* Port */
  QLabel *lport = new QLabel("Port number:");
  m_port = new QLineEdit();

  layout->addWidget(lport, 7, 0);
  layout->addWidget(m_port, 7, 1);
 
  /* Add apps Button*/
  QPushButton *addButton = new QPushButton(tr("Add application"));
  connect(addButton, SIGNAL( clicked() ), this, SLOT( Add() ) );
  
  /* layout ... */
  appsGroup->setLayout(layout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(appsGroup);
  mainLayout->addWidget(addButton);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void TcpPage::Choose()
{
  this->m_parent->hide();
  this->m_dw->m_appsTcp = true;
}

void TcpPage::Add()
{
  size_t startTime = m_startTime->text().toInt();
  size_t endTime = m_endTime->text().toInt();
  size_t port = m_port->text().toInt();

  if( (this->m_leftNode != "" && this->m_rightNode != "") &&
      startTime < endTime && port != 0 && port > 0)
  {
    // Application form seems to be valid
    this->m_dw->m_mw->GetGenerator()->AddApplication("TcpLargeTransfer", this->m_leftNode, this->m_rightNode, startTime, endTime, port);
    QMessageBox::about(this, "Tcp Large Transfer", "Tcp large transfer successfull installed.");

    // close the application window
    this->m_parent->close();
    this->m_dw->m_appsTcp = false;
  }
  else
  {
    // There is an error !
    if(this->m_leftNode == "" || this->m_rightNode == "")
    {
      QMessageBox::about(this, "Tcp Large Transfer", "Please choose the sender and target machines.");
    }
    else if(startTime >= endTime)
    {
      QMessageBox::about(this, "Tcp Large Transfer", "Start time can't be greather than end time.");
    }
    else
    {
      QMessageBox::about(this, "Tcp Large Transfer", "An error occured, please verify your params.");
    }
  }
}



