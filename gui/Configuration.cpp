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
  ipv4L3Protocol = new QLabel("Ipv4L3Protocol CalcCheckSum (bool)", dialog);
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
  icmpv4L4Protocol = new QLabel("Icmpv4L4Protocol CalcCheckSum (bool)", dialog);
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
  tcpL4Protocol = new QLabel("TcpL4Protocol CalcCheckSum (bool)", dialog);
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
  udpL4Protocol = new QLabel("UdpL4Protocol CalcCheckSum (bool)", dialog);
  layout->addWidget(udpL4Protocol, 3, 0);
  
  QCheckBox *box_udpL4Protocol;
  box_udpL4Protocol = new QCheckBox(dialog);
  layout->addWidget(box_udpL4Protocol, 3, 1);
  
  if(SearchConfig("Config::SetDefault (\"ns3::UdpL4Protocol::CalcChecksum") != "")
  {
    box_udpL4Protocol->setChecked(true);
  }
  
  /* choose */
  QLabel *ipv4RawSocketImpl;
  ipv4RawSocketImpl = new QLabel("Ipv4RawSocketImpl (int)", dialog);
  layout->addWidget(ipv4RawSocketImpl, 4, 0);
  
  QLineEdit *line_ipv4RawSocketImpl;
  line_ipv4RawSocketImpl = new QLineEdit(dialog);
  layout->addWidget(line_ipv4RawSocketImpl, 4, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::Ipv4RawSocketImpl::Protocol")) != "")
  {
    line_ipv4RawSocketImpl->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *onOff_packetSize;
  onOff_packetSize = new QLabel("OnOffApplication Packet Size (int)", dialog);
  layout->addWidget(onOff_packetSize, 5, 0);
  
  QLineEdit *line_onOff_packetSize;
  line_onOff_packetSize = new QLineEdit(dialog);
  layout->addWidget(line_onOff_packetSize, 5, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::OnOffApplication::PacketSize")) != "")
  {
    line_onOff_packetSize->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *onOff_dataRate;
  onOff_dataRate = new QLabel("OnOffApplication Data Rate (Mbps)", dialog);
  layout->addWidget(onOff_dataRate, 6, 0);
  
  QLineEdit *line_onOff_dataRate;
  line_onOff_dataRate = new QLineEdit(dialog);
  layout->addWidget(line_onOff_dataRate, 6, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::OnOffApplication::DataRate")) != "")
  {
    line_onOff_dataRate->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *rateError;
  rateError = new QLabel("RateErrorModel ErrorRate (double)", dialog);
  layout->addWidget(rateError, 7, 0);
  
  QLineEdit *line_rateError;
  line_rateError = new QLineEdit(dialog);
  layout->addWidget(line_rateError, 7, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::RateErrorModel::ErrorRate")) != "")
  {
    line_rateError->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *errorUnit;
  errorUnit = new QLabel("RateErrorModel ErrorUnit (string)", dialog);
  layout->addWidget(errorUnit, 8, 0);
  
  QLineEdit *line_errorUnit;
  line_errorUnit = new QLineEdit(dialog);
  layout->addWidget(line_errorUnit, 8, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::RateErrorModel::ErrorUnit")) != "")
  {
    line_errorUnit->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *csma_EncapsulationMode;
  csma_EncapsulationMode = new QLabel("CsmaNetDevice EncapsulationMode (string)", dialog);
  layout->addWidget(csma_EncapsulationMode, 9, 0);
  
  QLineEdit *line_csma_EncapsulationMode;
  line_csma_EncapsulationMode = new QLineEdit(dialog);
  layout->addWidget(line_csma_EncapsulationMode, 9, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::CsmaNetDevice::EncapsulationMode")) != "")
  {
    line_csma_EncapsulationMode->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *wifi_frag;
  wifi_frag = new QLabel("WifiRemoteStationManager FragmentationThreshold (int)", dialog);
  layout->addWidget(wifi_frag, 10, 0);
  
  QLineEdit *line_wifi_frag;
  line_wifi_frag = new QLineEdit(dialog);
  layout->addWidget(line_wifi_frag, 10, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::WifiRemoteStationManager::FragmentationThreshold")) != "")
  {
    line_wifi_frag->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *wifi_rts;
  wifi_rts = new QLabel("WifiRemoteStationManager RtsCtsThreshold (int)", dialog);
  layout->addWidget(wifi_rts, 11, 0);
  
  QLineEdit *line_wifi_rts;
  line_wifi_rts = new QLineEdit(dialog);
  layout->addWidget(line_wifi_rts, 11, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::WifiRemoteStationManager::RtsCtsThreshold")) != "")
  {
    line_wifi_rts->insert(QString(trans.c_str()));
  }
  
  /* choose */
  QLabel *wifi_standard;
  wifi_standard = new QLabel("YansWifiPhy Standard (string)", dialog);
  layout->addWidget(wifi_standard, 12, 0);
  
  QLineEdit *line_wifi_standard;
  line_wifi_standard = new QLineEdit(dialog);
  layout->addWidget(line_wifi_standard, 12, 1);
  
  if( (trans = SearchConfig("Config::SetDefault (\"ns3::YansWifiPhy::Standard")) != "")
  {
    line_wifi_standard->insert(QString(trans.c_str()));
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
    
    if(line_ipv4RawSocketImpl->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::Ipv4RawSocketImpl::Protocol\", StringValue (\""+(line_ipv4RawSocketImpl->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::Ipv4RawSocketImpl::Protocol");
    }
    
    if(line_onOff_packetSize->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::OnOffApplication::PacketSize\", UintegerValue ("+(line_onOff_packetSize->text()).toStdString()+"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::OnOffApplication::PacketSize");
    }
    
    if(line_onOff_dataRate->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::OnOffApplication::DataRate\", StringValue (\""+(line_onOff_dataRate->text()).toStdString()+"\"Mbps\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::OnOffApplication::DataRate");
    }
    
    if(line_rateError->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::RateErrorModel::ErrorRate\", DoubleValue ((\""+(line_rateError->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::RateErrorModel::ErrorRate");
    }
    
    if(line_errorUnit->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::RateErrorModel::ErrorUnit\", StringValue (\""+(line_errorUnit->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::RateErrorModel::ErrorUnit");
    }
    
    if(line_csma_EncapsulationMode->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::CsmaNetDevice::EncapsulationMode\", StringValue (\""+(line_csma_EncapsulationMode->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::CsmaNetDevice::EncapsulationMode");
    }
    
    if(line_wifi_frag->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::WifiRemoteStationManager::FragmentationThreshold\", StringValue (\""+(line_wifi_frag->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::WifiRemoteStationManager::FragmentationThreshold");
    }
    
    if(line_wifi_rts->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::WifiRemoteStationManager::RtsCtsThreshold\", StringValue (\""+(line_wifi_rts->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::WifiRemoteStationManager::RtsCtsThreshold");
    }
    
    if(line_wifi_standard->text() != "")
    {
      this->mw->gen->AddConfig("Config::SetDefault (\"ns3::YansWifiPhy::Standard\", StringValue (\""+(line_wifi_standard->text()).toStdString()+"\"));");
    }
    else
    {
      RemoveConfiguration("Config::SetDefault (\"ns3::YansWifiPhy::Standard");
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
  
  if(res.find("\"") == 0)
  {
    for(size_t i = 0; i < (size_t) res.size(); i++)
    {
      if(res.substr(i,1) == "\"")
      {
        res.erase(i, 1);
      }
    }
  }
  
  if((res.find("Mbps")) != std::string::npos)
  {
    res.erase(res.end() - 4, res.end());
  }

  return res;
}

