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
  /*
  if(gen->GetNNodes() > 0)
  {
    writer->writeDTD("<!ELEMENT Nodes (ANY)>");
  }
  else
  {
    writer->writeDTD("<!ELEMENT Nodes (EMPTY)>");
  }
  */
  writer->writeStartElement("Nodes");//<Nodes>
  for(size_t i = 0; i < gen->GetNNodes(); i++)
  { 
    for(size_t j = 0; j < (size_t)dw->children().size(); j++)
    {
      DragObject *child = dynamic_cast<DragObject*>(dw->children().at(j));
      if(child)
      {
        if(child->GetName() == gen->GetNode(i)->GetNodeName() && child->GetName() != "" && child->GetName() != "deleted")
        {
          writer->writeStartElement("node");//<node>
          writer->writeTextElement("type", QString((gen->GetNode(i)->GetNodeType()).c_str()));
          writer->writeTextElement("nodeNbr", QString((utils::integerToString(gen->GetNode(i)->GetMachinesNumber())).c_str()));
          writer->writeTextElement("name", QString((gen->GetNode(i)->GetNodeName()).c_str()));
          writer->writeTextElement("nsc", QString((gen->GetNode(i)->GetNsc()).c_str()));
          writer->writeTextElement("x", QString((utils::integerToString(child->pos().x())).c_str()));
          writer->writeTextElement("y", QString((utils::integerToString(child->pos().y())).c_str())); 
          writer->writeEndElement();//</node>
        }
      }
    }
  }
  writer->writeEndElement();//<Nodes>

  //
  // Dump Link list
  //
  /*
  if(gen->GetNNetworkHardwares() > 0)
  {
    writer->writeDTD("<!ELEMENT NetworkHardwares (ANY)>"); 
  }
  else
  {
    writer->writeDTD("<!ELEMENT NetworkHardwares (EMPTY)>");
  }
  */
  bool hidden = true;
  writer->writeStartElement("NetworkHardwares");//<NetworkHardwares>
  for(size_t i = 0; i < gen->GetNNetworkHardwares(); i++)
  {
    hidden = true;
    writer->writeStartElement("networkHardware");//<networkHardware>
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
    writer->writeTextElement("type", QString((gen->GetNetworkHardware(i)->GetLinkType()).c_str()));     
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
    // for each link, put his own spécial configs
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
    }
    else if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("emu_") == 0)
    {
      Emu *emu = dynamic_cast<Emu*>(gen->GetNetworkHardware(i));
      writer->writeTextElement("iface", QString((emu->GetIfaceName()).c_str()));
    }
    else if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("tap_") == 0)
    {
      Tap *tap = dynamic_cast<Tap*>(gen->GetNetworkHardware(i));
      writer->writeTextElement("iface", QString((tap->GetIfaceName()).c_str()));
    }
    else if(gen->GetNetworkHardware(i)->GetNetworkHardwareName().find("hub_") == 0 && !hidden)
    {
      for(size_t j = 0; j < (size_t)dw->children().size(); j++)
      {
        DragObject *child = dynamic_cast<DragObject*>(dw->children().at(j));
        if(child)
        {
          if(child->GetName() == gen->GetNetworkHardware(i)->GetNetworkHardwareName())
          {
            writer->writeTextElement("hubPos", QString( ( utils::integerToString(child->pos().x()) + "-" + 
                                                          utils::integerToString(child->pos().y())).c_str()));
            break;
          }
        }
      }
    }
    else
    {
      writer->writeTextElement("none", "");
    }

    writer->writeStartElement("connectedNodes");  
    for(size_t j = 0; j < gen->GetNetworkHardware(i)->GetInstalledNodes().size(); j++)
    {
      writer->writeTextElement("name", QString((gen->GetNetworkHardware(i)->GetInstalledNode(j)).c_str()));
    }
    writer->writeEndElement();//</networkHardwares>
    writer->writeEndElement();//</networkHardware>
  }
  writer->writeEndElement();//</NetworkHardwares>
    
  //
  // Dump Application List
  //
  /*
  if(gen->GetNApplications() > 0)
  {
    writer->writeDTD("<!ELEMENT Applications (ANY)>");
  }
  else
  {
    writer->writeDTD("<!ELEMENT Applications (EMPTY)>");
  }
  */
  //<Applications>
  writer->writeStartElement("Applications");
  for(size_t i = 0; i < gen->GetNApplications(); i++)
  {
    writer->writeStartElement("application");
    
    writer->writeTextElement("type", QString((gen->GetApplication(i)->GetApplicationType()).c_str()));
    writer->writeTextElement("name", QString((gen->GetApplication(i)->GetAppName()).c_str()));
    writer->writeTextElement("sender", QString((gen->GetApplication(i)->GetSenderNode()).c_str()));
    writer->writeTextElement("receiver", QString((gen->GetApplication(i)->GetReceiverNode()).c_str()));
    writer->writeTextElement("startTime", QString((gen->GetApplication(i)->GetStartTime()).c_str()));
    writer->writeTextElement("endTime", QString((gen->GetApplication(i)->GetEndTime()).c_str()));

    writer->writeStartElement("special");
    if(gen->GetApplication(i)->GetAppName().find("tcp_") == 0)
    {
      TcpLargeTransfer *tcp = dynamic_cast<TcpLargeTransfer*>(gen->GetApplication(i));
      writer->writeTextElement("port", QString(utils::integerToString(tcp->GetPort()).c_str()));
    } 
    else if(gen->GetApplication(i)->GetAppName().find("udpEcho_") == 0)
    {
      UdpEcho *udp = dynamic_cast<UdpEcho*>(gen->GetApplication(i));
      writer->writeTextElement("port", QString(utils::integerToString(udp->GetPort()).c_str()));
      writer->writeTextElement("packetSize", QString(utils::integerToString(udp->GetPacketSize()).c_str()));
      writer->writeTextElement("maxPacketCount", QString(utils::integerToString(udp->GetMaxPacketCount()).c_str()));
      writer->writeTextElement("packetIntervalTime", QString((udp->GetPacketIntervalTime()).c_str()));
    }
    writer->writeEndElement();//</special>
    writer->writeEndElement();//</application>
  }
  writer->writeEndElement();//</Applications>
  
  //<Lines>
  writer->writeStartElement("Lines");
  for(size_t i = 0; i < dw->GetDrawLines().size(); i++)
  {
    writer->writeStartElement("line");
    
    writer->writeTextElement("first", QString((dw->GetDrawLine(i).GetFirst()).c_str()));
    writer->writeTextElement("second", QString((dw->GetDrawLine(i).GetSecond()).c_str()));
    writer->writeTextElement("linkType", QString((dw->GetDrawLine(i).GetNetworkHardwareType()).c_str()));

    writer->writeEndElement();//</line>
  }
  writer->writeEndElement();//</Lines>

  writer->writeEndDocument();//</Gen>
}

void loadXml(QXmlStreamReader *reader, Generator *gen, DragWidget *dw)
{
  reader->readNext();
  while(!reader->atEnd())
  {
    if(reader->isStartElement()) 
    {
      if(reader->name() == "Nodes") 
      {
        guiUtils::jumpToNextStartElement(reader);
        while(reader->name() == "node")
        {
          guiUtils::jumpToNextStartElement(reader);
          std::string type = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          size_t nodeNbr = utils::stringToInteger(reader->readElementText().toStdString());

          gen->AddNode(type, nodeNbr);
          
          guiUtils::jumpToNextStartElement(reader);
          gen->GetNode(gen->GetNNodes() - 1)->SetNodeName( (reader->readElementText()).toStdString() );

          guiUtils::jumpToNextStartElement(reader);
          gen->GetNode(gen->GetNNodes() - 1)->SetNsc( (reader->readElementText()).toStdString() );
          
          guiUtils::jumpToNextStartElement(reader);
          size_t x = utils::stringToInteger((reader->readElementText()).toStdString());

          guiUtils::jumpToNextStartElement(reader);
          size_t y = utils::stringToInteger((reader->readElementText()).toStdString());

          dw->CreateObject(type, gen->GetNode(gen->GetNNodes() - 1)->GetNodeName(), x, y);

          guiUtils::jumpToNextStartElement(reader);
        }
      }
      if(reader->name() == "NetworkHardwares")
      {
        guiUtils::jumpToNextStartElement(reader);
        while(reader->name() == "networkHardware")
        {
          guiUtils::jumpToNextStartElement(reader);
          std::string hiddenState = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string type = reader->readElementText().toStdString();
        
          guiUtils::jumpToNextStartElement(reader);
          std::string name = reader->readElementText().toStdString();
          
          guiUtils::jumpToNextStartElement(reader);
          std::string dataRate = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string linkDelay = reader->readElementText().toStdString();
        
          guiUtils::jumpToNextStartElement(reader);
          std::string enableTrace = reader->readElementText().toStdString();
          
          guiUtils::jumpToNextStartElement(reader);
          std::string tracePromisc = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string special = reader->readElementText().toStdString();
          
          std::vector<std::string> connectedNodes;
          guiUtils::jumpToNextStartElement(reader);
          if(reader->name() == "connectedNodes")
          {
            guiUtils::jumpToNextStartElement(reader);
            while(reader->name() == "name")
            {
              connectedNodes.push_back(reader->readElementText().toStdString());
              guiUtils::jumpToNextStartElement(reader);
            }
          }
          
          if(type == "Hub" || type == "PointToPoint")
          {
            gen->AddNetworkHardware(type);
          }
          else if(type == "Bridge" || type == "Ap")
          {
            gen->AddNetworkHardware(type, name);
          } 
          else // Emu, Tap
          {
            gen->AddNetworkHardware(type, name, special);
          }
        
          gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->SetNetworkHardwareName(name);
          gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->SetDataRate(dataRate);
          gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->SetNetworkHardwareDelay(linkDelay);
        
          if(enableTrace == "true")
          {
            gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->SetTrace(true);
          }
          if(tracePromisc == "true")
          {
            gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->SetPromisc(true);
          }

          for(size_t i = 0; i < connectedNodes.size(); i++)
          {
            gen->GetNetworkHardware(gen->GetNNetworkHardwares() - 1)->Install(connectedNodes.at(i));
          }
        
          if(hiddenState == "false" && type != "Emu" && type != "Tap" && type != "Ap" && type != "Bridge")
          {
            if(type == "Hub")
            {
              std::vector<std::string> vec;
              utils::split(vec, special, '-');
              dw->CreateObject(type, name, utils::stringToInteger(vec.at(0)), utils::stringToInteger(vec.at(1)));
            }
            else
            {
              dw->CreateObject(type, name);
            }
          }
          
          //guiUtils::jumpToNextStartElement(reader);
        }
      }
      if(reader->name() == "Applications")
      {
        guiUtils::jumpToNextStartElement(reader);
        while(reader->name() == "application")
        {
          guiUtils::jumpToNextStartElement(reader);
          std::string type = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string name = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string sender = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          std::string receiver = reader->readElementText().toStdString();

          guiUtils::jumpToNextStartElement(reader);
          size_t startTime = utils::stringToInteger(reader->readElementText().toStdString());
          
          guiUtils::jumpToNextStartElement(reader);
          size_t endTime = utils::stringToInteger(reader->readElementText().toStdString());

          guiUtils::jumpToNextStartElement(reader);
          size_t port = 0;
          size_t packetSize = 0;
          size_t maxPacketCount = 0;
          std::string packetIntervalTime = "";
          if(reader->name() == "special")
          {
            guiUtils::jumpToNextStartElement(reader);
            if(type == "TcpLargeTransfer")
            {
              port = utils::stringToInteger(reader->readElementText().toStdString());
            }
            else if(type == "UdpEcho")
            {
              port = utils::stringToInteger(reader->readElementText().toStdString());
              
              guiUtils::jumpToNextStartElement(reader);
              packetSize = utils::stringToInteger(reader->readElementText().toStdString());

              guiUtils::jumpToNextStartElement(reader);
              maxPacketCount = utils::stringToInteger(reader->readElementText().toStdString());
              
              guiUtils::jumpToNextStartElement(reader);
              packetIntervalTime = reader->readElementText().toStdString();
            }
          }
  
          if(type == "Ping")
          {
            gen->AddApplication(type, sender, receiver, startTime, endTime);
          }
          else if(type == "UdpEcho")
          {
            gen->AddApplication(type, sender, receiver, startTime, endTime, port);
            UdpEcho *udp = dynamic_cast<UdpEcho*>(gen->GetApplication(gen->GetNApplications() - 1));
            udp->SetPacketSize(packetSize);
            udp->SetMaxPacketCount(maxPacketCount);
            udp->SetPacketIntervalTime(packetIntervalTime);
          }
          else if(type == "TcpLargeTransfer")
          {
            gen->AddApplication(type, sender, receiver, startTime, endTime, port);
          }


          if(type != "Ping")
          {
            guiUtils::jumpToNextStartElement(reader);
          }
        }
      }
      if(reader->name() == "Lines")
      {
        guiUtils::jumpToNextStartElement(reader);
        while(reader->name() == "line")
        {
          DragLines dg;

          guiUtils::jumpToNextStartElement(reader);
          dg.SetFirst(reader->readElementText().toStdString());

          guiUtils::jumpToNextStartElement(reader);
          dg.SetSecond(reader->readElementText().toStdString());

          guiUtils::jumpToNextStartElement(reader);
          dg.SetNetworkHardwareType(reader->readElementText().toStdString());

          dw->AddDrawLine(dg);

          guiUtils::jumpToNextStartElement(reader);
        }
      }
    }
    reader->readNext();
  }

}

void jumpToNextStartElement(QXmlStreamReader *reader)
{
  reader->readNext();
  while(!reader->isStartElement() && !reader->atEnd())
  {
    reader->readNext();
  }
}

} /* namespace guiUtils */
