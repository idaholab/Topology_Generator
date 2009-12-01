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
 * \file gui-utils.cpp
 * \brief utils gui file.
 * \author Pierre Weiss
 * \date 2009
 */

#include "gui-utils.h"
#include "utils.h"

#include "ap.h"
#include "emu.h"
#include "tap.h"
#include "tcp-large-transfer.h"
#include "udp-echo.h"

namespace guiUtils
{

void saveXml(QXmlStreamWriter *writer, Generator *gen, DragWidget *dw)
{
  writer->setAutoFormatting(true);
  writer->writeStartDocument();

  writer->writeStartElement("Gen");
    
  //
  // Dump Node list
  //
  writer->writeStartElement("Nodes");
  for(size_t i = 0; i < gen->GetNNodes(); i++)
  { 
    for(size_t j = 0; j < (size_t)dw->children().size(); j++)
    {
      DragObject *child = dynamic_cast<DragObject*>(dw->children().at(j));
      if(child)
      {
        if(child->GetName() == gen->GetNode(i)->GetNodeName() && child->GetName() != "" && child->GetName() != "deleted")
        {
          writer->writeStartElement("node");
          writer->writeTextElement("name", QString((gen->GetNode(i)->GetNodeName()).c_str()));
          writer->writeTextElement("nsc", QString((gen->GetNode(i)->GetNsc()).c_str()));
          writer->writeTextElement("nodeNbr", QString((utils::integerToString(gen->GetNode(i)->GetMachinesNumber())).c_str()));
          writer->writeTextElement("x", QString((utils::integerToString(child->pos().x())).c_str()));
          writer->writeTextElement("y", QString((utils::integerToString(child->pos().y())).c_str())); 
          writer->writeEndElement();//</node>
        }
      }
    }
  }
  writer->writeEndElement();//</Nodes>

  //
  // Dump Link list
  //
  bool hidden = true;
  writer->writeStartElement("NetworkHardwares");
  for(size_t i = 0; i < gen->GetNNetworkHardwares(); i++)
  {
    hidden = true;
    writer->writeStartElement("networkHardware");
    // check if link is hidden or not.
    for(size_t j = 0; j < (size_t)dw->children().size(); j++)
    {
      DragObject *child = dynamic_cast<DragObject*>(dw->children().at(j));
      if(child)
      {
        if(child->GetName() == gen->GetNetworkHardware(i)->GetNetworkHardwareName())
        {
          hidden = false;
          break;
        }
      }
    }
    if(hidden)
    {
      writer->writeTextElement("hidden", "true");
    }
    else
    {
      writer->writeTextElement("hidden", "false");
    }
    writer->writeTextElement("name", QString((gen->GetNetworkHardware(i)->GetNetworkHardwareName()).c_str()));     
    writer->writeTextElement("dataRate", QString((gen->GetNetworkHardware(i)->GetDataRate()).c_str()));
    writer->writeTextElement("linkDelay", QString((gen->GetNetworkHardware(i)->GetNetworkHardwareDelay()).c_str()));
    if(gen->GetNetworkHardware(i)->GetTrace())
    {
      writer->writeTextElement("enableTrace", "true");
    }
    else
    {
      writer->writeTextElement("enableTrace", "false");
    }
    if(gen->GetNetworkHardware(i)->GetPromisc())
    {
      writer->writeTextElement("tracePromisc", "true");
    }
    else
    {
      writer->writeTextElement("tracePromisc", "false");
    } 
    writer->writeStartElement("connectedNodes");  
    for(size_t j = 0; j < gen->GetNetworkHardware(i)->GetInstalledNodes().size(); j++)
    {
      writer->writeTextElement("name", QString((gen->GetNetworkHardware(i)->GetInstalledNode(j)).c_str()));
    }
    writer->writeEndElement();
    
    // for each link, put his own spécial configs
    writer->writeStartElement("special");
    if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("ap_") == 0)
    {
      Ap *ap = dynamic_cast<Ap*>(gen->GetNetworkHardware(i));
      if(ap->GetMobility())
      {
        writer->writeTextElement("mobility", "true");
      }
      else
      {
        writer->writeTextElement("mobility", "false");
      }
      //delete ap;
    }
    else if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("emu_") == 0)
    {
      Emu *emu = dynamic_cast<Emu*>(gen->GetNetworkHardware(i));
      writer->writeTextElement("iface", QString((emu->GetIfaceName()).c_str()));
      //delete emu;
    }
    else if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("tap_") == 0)
    {
      Tap *tap = dynamic_cast<Tap*>(gen->GetNetworkHardware(i));
      writer->writeTextElement("iface", QString((tap->GetIfaceName()).c_str()));
      //delete tap;
    }
    writer->writeEndElement();//</special>
    writer->writeEndElement();//</networkHardware>
  }
  writer->writeEndElement();//</NetworkHardwares>
    
  //
  // Dump Application List
  //
  writer->writeStartElement("Applications");
  for(size_t i = 0; i < gen->GetNApplications(); i++)
  {
    writer->writeStartElement("application");
    
    writer->writeTextElement("name", QString((gen->GetApplication(i)->GetAppName()).c_str()));
    writer->writeTextElement("sender", QString((gen->GetApplication(i)->GetSenderNode()).c_str()));
    writer->writeTextElement("receiver", QString((gen->GetApplication(i)->GetReceiverNode()).c_str()));
    writer->writeTextElement("startTime", QString((gen->GetApplication(i)->GetStartTime()).c_str()));
    writer->writeTextElement("endTime", QString((gen->GetApplication(i)->GetEndTime()).c_str()));

    writer->writeStartElement("special");
    if(gen->GetApplication(i)->GetAppName().find("tcp_") == 0)
    {
      TcpLargeTransfer *tcp = dynamic_cast<TcpLargeTransfer*>(gen->GetApplication(i));
      writer->writeTextElement("port", QString((uint)tcp->GetPort()));
      //delete tcp;
    } 
    else if(gen->GetApplication(i)->GetAppName().find("udpEcho_") == 0)
    {
      UdpEcho *udp = dynamic_cast<UdpEcho*>(gen->GetApplication(i));
      writer->writeTextElement("port", QString((uint)udp->GetPort()));
      writer->writeTextElement("packetSize", QString((uint)udp->GetPacketSize()));
      writer->writeTextElement("maxPacketCount", QString((uint)udp->GetMaxPacketCount()));
      writer->writeTextElement("packetIntervalTime", QString((udp->GetPacketIntervalTime()).c_str()));
      //delete udp;
    }

    writer->writeEndElement();//</special>
    writer->writeEndElement();//</application>
  }
  writer->writeEndElement();//</Applications>

  writer->writeEndDocument();//</Gen>
}

} /* namespace guiUtils */
