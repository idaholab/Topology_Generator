/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
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
* \file Configuration.cpp
* \brief The GUI configuration file.
* \author Pierre Weiss
* \date 2009
*/

#include <iostream>

#include "Configuration.h"


Configuration::Configuration(MainWindow *_mw)
{
  this->mw = _mw;
	dialog = new QDialog(this);
	dialog->setWindowTitle("Configuration");

	/* Layout*/
	QGridLayout *layout = new QGridLayout;

	/* button ok and close */
  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    
  std::string trans("");
  /* choose */
  QLabel *ipv4L3Protocol;
  ipv4L3Protocol = new QLabel("IP checksum", dialog);
  layout->addWidget(ipv4L3Protocol, 0, 0);
    
  QCheckBox *box_ipv4L3Protocol;
  box_ipv4L3Protocol = new QCheckBox(dialog);
  layout->addWidget(box_ipv4L3Protocol, 0, 1);
    
  if(SearchConfig("Config::SetDefault (\"ns3::Ipv4L3Protocol::CalcChecksum") != "")
  {
    box_ipv4L3Protocol->setChecked(true);
  }
  
  /* choose */
  QLabel *icmpv4L4Protocol;
  icmpv4L4Protocol = new QLabel("ICMP checksum", dialog);
  layout->addWidget(icmpv4L4Protocol, 1, 0);
    
  QCheckBox *box_icmpv4L4Protocol;
  box_icmpv4L4Protocol = new QCheckBox(dialog);
  layout->addWidget(box_icmpv4L4Protocol, 1, 1);
  
  if(SearchConfig("Config::SetDefault (\"ns3::Icmpv4L4Protocol::CalcChecksum") != "")
  {
    box_icmpv4L4Protocol->setChecked(true);
  }
  
  /* choose */
  QLabel *tcpL4Protocol;
  tcpL4Protocol = new QLabel("TCP checksum", dialog);
  layout->addWidget(tcpL4Protocol, 2, 0);
  
  QCheckBox *box_tcpL4Protocol;
  box_tcpL4Protocol = new QCheckBox(dialog);
  layout->addWidget(box_tcpL4Protocol, 2, 1);
  
  if(SearchConfig("Config::SetDefault (\"ns3::TcpL4Protocol::CalcChecksum") != "")
  {
    box_tcpL4Protocol->setChecked(true);
  }
  
  /* choose */
  QLabel *udpL4Protocol;
  udpL4Protocol = new QLabel("UDP checksum", dialog);
  layout->addWidget(udpL4Protocol, 3, 0);
  
  QCheckBox *box_udpL4Protocol;
  box_udpL4Protocol = new QCheckBox(dialog);
  layout->addWidget(box_udpL4Protocol, 3, 1);
  
  if(SearchConfig("Config::SetDefault (\"ns3::UdpL4Protocol::CalcChecksum") != "")
  {
    box_udpL4Protocol->setChecked(true);
  }
  
	/* add button ok and close to the bottom */
	layout->addWidget(buttonBox, 14, 2);
    
  dialog->setLayout(layout);
  dialog->exec();
  
  if(dialog->result() == 1)
  {
    /* choose */
    if(box_ipv4L3Protocol->isChecked())
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::Ipv4L3Protocol::CalcChecksum\", BooleanValue (true));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::Ipv4L3Protocol::CalcChecksum");
    }
    
    if(box_icmpv4L4Protocol->isChecked())
    {
       this->mw->gen->AddConfig("Config::SetDefault (\"ns3::Icmpv4L4Protocol::CalcChecksum\", BooleanValue (true));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::Icmpv4L4Protocol::CalcChecksum");
    }
    
    if(box_tcpL4Protocol->isChecked())
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::TcpL4Protocol::CalcChecksum\", BooleanValue (true));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::TcpL4Protocol::CalcChecksum");
    }
    
    if(box_udpL4Protocol->isChecked())
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::UdpL4Protocol::CalcChecksum\", BooleanValue (true));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::UdpL4Protocol::CalcChecksum");
    }
    
  }
  
}

void Configuration::RemoveConfiguration(const std::string &motif)
{
  for(size_t i = 0; i < (size_t) this->mw->gen->listConfiguration.size(); i++)
  {
    if( (this->mw->gen->listConfiguration.at(i)).find(motif) == 0)
    {
      this->mw->gen->listConfiguration.erase(this->mw->gen->listConfiguration.begin() + i);
    }
  }
}

std::string Configuration::SearchConfig(const std::string &motif)
{
  std::string res("");
  for(size_t i = 0; i < (size_t) this->mw->gen->listConfiguration.size(); i++)
  {
    std::string trans = this->mw->gen->listConfiguration.at(i);
    if( (this->mw->gen->listConfiguration.at(i)).find(motif) == 0)
    {
      res = trans.substr(trans.find_last_of("(") + 1, (trans.find_last_of(")") - trans.find_last_of("(")) - 2);
    }
  }

  return res;
}

