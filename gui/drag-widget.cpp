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
 * \file drag-widget.cpp
 * \brief The drag'n'drop zone file.
 * \author Pierre Weiss
 * \date 2009
 */

#include <QtWidgets>
#include <iostream>
#include <stdexcept>

#include "main-window.h"
#include "drag-widget.h"

#include "drag-object.h"
#include "drag-lines.h"

#include "emu.h"
#include "tap.h"

#include "utils.h"
#include "gui-utils.h"
#include "array-utils.h"

DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
  setMinimumSize(400, 400);
  setAcceptDrops(true);
  setMouseTracking(true);

  this->m_timer = new QTimer();

  // object used for link tracing.
  this->m_traceNetworkHardware = false;
  this->m_networkHardwareBegin = "";
  this->m_networkHardwareEnd = "";
  this->m_networkHardwareType = "";
  this->m_isDrawLine = false;

  // object used for application creation
  this->m_appsPing = false;
  this->m_appsUdpEcho = false;
  this->m_appsTcp = false;
  // the right and left application node
  this->m_appsClient = "";
  this->m_appsServer = "";
}

DragWidget::~DragWidget()
{
  delete this->m_timer;
}

void DragWidget::CreateObject(const std::string &type, const std::string &name, size_t x /*=10*/, size_t y /*=10*/)
{
  Array <std::string> ico;
  ico["Pc"]       = ":/Ico/Pc.png";
  ico["Pc-group"] = ":/Ico/Pc-group.png";
  ico["Emu"]      = ":/Ico/Emu.png";
  ico["Tap"]      = ":/Ico/Tap.png";
  ico["Ap"]       = ":/Ico/Ap-Wifi.png";
  ico["Station"]  = ":/Ico/StationWifi.png";
  ico["Hub"]      = ":/Ico/Hub.png";
  ico["Bridge"]   = ":/Ico/Switch.png";
  ico["Router"]   = ":/Ico/Router.png";

  DragObject *label = new DragObject(this);
  label->SetName(name);
  this->UpdateToolTips();
  
  label->setPixmap(QPixmap(QString((ico[type]).c_str())));
  label->move(x, y);
  label->show();
  label->setAttribute(Qt::WA_DeleteOnClose);

  this->m_timer = new QTimer();
  this->m_timer->start(100);
  connect(this->m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
  {
    if (event->source() == this) 
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } 
    else 
    {
      event->acceptProposedAction();
    }
  } 
  else 
  {
    event->ignore();
  }
}

void DragWidget::dropEvent(QDropEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
  {
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;

    DragObject *child = static_cast<DragObject*>(childAt( this->m_lastPosition ));
    DragObject *label = new DragObject(this);
    if(child)
    {
      label->SetName(child->GetName());
      this->UpdateToolTips();
    }
    label->setPixmap(pixmap);
    label->move(event->pos() - offset);
    label->show();
    label->setAttribute(Qt::WA_DeleteOnClose);

    update();

    if (event->source() == this) 
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } 
    else 
    {
      event->acceptProposedAction();
    }
  } 
  else 
  {
    event->ignore();
  }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
  DragObject *child = static_cast<DragObject*>(childAt(event->pos()));
  if (!child)
  {
    // test if we are looking for a drawed line
    for(size_t i = 0; i < this->m_drawLines.size(); i++)
    {
      // equipement A(xa, ya)
      DragObject *begin = this->GetChildFromName(this->m_drawLines.at(i).GetFirst());
      double xa = begin->pos().x() + (begin->width() / 2);
      double ya = begin->pos().y() + (begin->height() / 2);
      // equipement B(xb, yb)
      DragObject *end = this->GetChildFromName(this->m_drawLines.at(i).GetSecond());
      double xb = end->pos().x() + (end->width() / 2);
      double yb = end->pos().y() + (end->height() / 2);

      double dx = xb - xa;
      double dy = yb - ya;
      if(dx >= dy)
      {
        double b = ya - (dy / dx) * xa;
        // C(xc, yc) is the mouse pointer
        // if yc = xc * (dy/dx) + b we are pointing on a line !
        if( ((double) event->y() - (double) 5) < ( (double)event->x() * ((double)(dy / dx)) + (double)b) &&
            ((double) event->y() + (double) 5) > ( (double)event->x() * ((double)(dy / dx)) + (double)b) )
        {
          // check if we are focus on the right zone
          if( (xb - xa) >= 0 )
          {
            if( event->x() > xa && event->y() < xb )
            {
              this->m_lastPosition = QPoint();
              this->m_mw->m_delAction->setDisabled(false);
              this->m_isDrawLine = true;
              this->m_lastLine = this->m_drawLines.at(i);
              return;
            }
          }
          else
          {
            if( event->x() < xa && event->y() > xb )
            {
              this->m_lastPosition = QPoint();
              this->m_mw->m_delAction->setDisabled(false);
              this->m_isDrawLine = true;
              this->m_lastLine = this->m_drawLines.at(i);
              return;
            }
          }
        }
      }
      else
      {
        double b = ya - (dx / dy) * xa;
        // C(xc, yc) is the mouse pointer
        // if yc = xc * (dx/dy) + b we are pointing on a line !
        if( ((double) event->y() - (double) 10) < ( (double)event->x() * ((double)(dx / dy)) + (double)b) &&
            ((double) event->y() + (double) 10) > ( (double)event->x() * ((double)(dx / dy)) + (double)b) )
        { 
          // check if we are focus on the right zone
          if( (xb - xa) >= 0 )
          {
            if( event->x() > xa && event->y() < xb )
            {
              this->m_lastPosition = QPoint();
              this->m_mw->m_delAction->setDisabled(false);
              this->m_isDrawLine = true;
              this->m_lastLine = this->m_drawLines.at(i);
              return;
            }
          }
          else
          {
            if( event->x() < xa && event->y() > xb )
            {
              this->m_lastPosition = QPoint();
              this->m_mw->m_delAction->setDisabled(false);
              this->m_isDrawLine = true;
              this->m_lastLine = this->m_drawLines.at(i);
              return;
            }
          }
        }
      }
    }
  }

  if(!child || child->GetName() == "deleted")
  {
    this->m_mw->m_delAction->setDisabled(true);
    return;
  }

  this->m_mw->m_delAction->setDisabled(false);
  this->m_lastPosition = event->pos();

  // used if we are currently under drawing a line.
  DragObject *child2 = NULL;
  if(this->m_traceNetworkHardware)
  {
    if(this->m_networkHardwareBegin == "")
    {
      // use this equipement as start of the drawing line
      this->m_networkHardwareBegin = child->GetName();
    }
    else if(this->m_networkHardwareEnd == "")
    {
      child2 = this->GetChildFromName(this->m_networkHardwareBegin);
      if(child2)
      {
        if( child->GetName() != child2->GetName())
        {
          // if we got the second equipement to be linked in
          this->m_networkHardwareEnd = child->GetName();
          // prepare the line object
          DragLines lig;
          lig.SetFirst(this->m_networkHardwareBegin);
          lig.SetSecond(this->m_networkHardwareEnd);
          lig.SetNetworkHardwareType(this->m_networkHardwareType);

          // add it to the vector containing all lines object
          this->m_drawLines.push_back(lig);

          // validate the traced link
          size_t linkNumber = 0;
          this->SetTraceNetworkHardware(false);
          // NetworkHardware to NetworkHardware
          if( guiUtils::isNetworkHardware(this->m_networkHardwareBegin) &&
              guiUtils::isNetworkHardware(this->m_networkHardwareEnd) )
          {
            this->m_mw->GetGenerator()->AddNetworkHardware("Hub");
            linkNumber = (this->m_mw->GetGenerator()->GetNNetworkHardwares() - 1);
            this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(), 
                                    this->m_networkHardwareBegin);
            this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(), 
                                    this->m_networkHardwareEnd);
          }
          // NetworkHardware to something
          else if( guiUtils::isNetworkHardware(this->m_networkHardwareBegin) )
          {
            this->m_mw->ConnectNode(this->m_networkHardwareBegin, this->m_networkHardwareEnd);
          }
          // something to NetworkHardware
          else if( guiUtils::isNetworkHardware(this->m_networkHardwareEnd) )
          {
            this->m_mw->ConnectNode(this->m_networkHardwareEnd, this->m_networkHardwareBegin);
          }
          // Node to Node
          else
          {
            // WiredLink type
            if( this->m_networkHardwareType == "WiredLink" )
            {
              this->m_mw->GetGenerator()->AddNetworkHardware("Hub");
              linkNumber = (this->m_mw->GetGenerator()->GetNNetworkHardwares() - 1);
              this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(),
                                      this->m_networkHardwareBegin);
              this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(), 
                                      this->m_networkHardwareEnd);
            }
            // Point to point type
            else if( this->m_networkHardwareType == "P2pLink")
            {
              this->m_mw->GetGenerator()->AddNetworkHardware("PointToPoint");
              linkNumber = (this->m_mw->GetGenerator()->GetNNetworkHardwares() - 1);
              this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(),
                                      this->m_networkHardwareBegin);
              this->m_mw->ConnectNode(this->m_mw->GetGenerator()->GetNetworkHardware(linkNumber)->GetNetworkHardwareName(),
                                      this->m_networkHardwareEnd);
            }
          }

          // draw and clean
          this->DrawLines();
          this->ResetSelected();
        }
      }
    }
  }

  QPixmap pixmap = *child->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->pos() - child->pos());

  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->pos() - child->pos());

  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  child->setPixmap(tempPixmap);

  if (drag->start(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction)
  {
    child->close();
  }
  else 
  {
    child->show();
    child->setPixmap(pixmap);
  }

  /* application. */
  if(this->m_appsPing || this->m_appsUdpEcho || this->m_appsTcp)
  {
    if(this->m_appsServer == "")
    {
      // choose left node
      this->m_appsServer = child->GetName();
      if(this->m_appsPing)
      {
        this->m_mw->m_appsDialog->m_ping->m_leftNode = child->GetName();
      }
      if(this->m_appsUdpEcho)
      {
        this->m_mw->m_appsDialog->m_udpEcho->m_leftNode = child->GetName();
      }
      if(this->m_appsTcp)
      {
        this->m_mw->m_appsDialog->m_tcp->m_leftNode = child->GetName();
      }

    }
    else
    {
      if(this->m_appsClient == "" && child->GetName() != this->m_appsServer)
      {
        // choose right node
        this->m_appsClient = child->GetName();
        if(this->m_appsPing)
        {
          this->m_mw->m_appsDialog->m_ping->m_rightNode = child->GetName();
        }
        if(this->m_appsUdpEcho)
        {
          this->m_mw->m_appsDialog->m_udpEcho->m_rightNode = child->GetName();
        }
        if(this->m_appsTcp)
        {
          this->m_mw->m_appsDialog->m_tcp->m_rightNode = child->GetName();
        }
      }
    }
    //show back application gui
    this->m_mw->m_appsDialog->show();
    if(this->m_appsPing)
    {
      this->m_mw->m_appsDialog->m_ping->Refresh();
    }
    if(this->m_appsUdpEcho)
    {
      this->m_mw->m_appsDialog->m_udpEcho->Refresh();
    }
    if(this->m_appsTcp)
    {
      this->m_mw->m_appsDialog->m_tcp->Refresh();
    }

  }
}

void DragWidget::mouseMoveEvent(QMouseEvent * /*event*/)
{
  update();
}

void DragWidget::ResetSelected()
{
  this->m_networkHardwareBegin = "";
  this->m_networkHardwareEnd = "";
  this->m_networkHardwareType = "";
}

DragObject* DragWidget::GetChildFromName(const std::string &name)
{
  for(size_t i = 0; i < (size_t)this->children().size(); i++)
  {
    DragObject *child = dynamic_cast<DragObject*>(this->children().at(i));
    if(child)
    {
      if( child->GetName() == name)
      {
        return child;
      }
    }
  }
  return new DragObject(this);
}

void DragWidget::AddDrawLine(const DragLines &dl)
{
  this->m_drawLines.push_back(dl);
}

DragLines DragWidget::GetDrawLine(const size_t &index)
{
  return this->m_drawLines.at(index);
}

std::vector<DragLines> DragWidget::GetDrawLines()
{
  return this->m_drawLines;
}

void DragWidget::EraseDrawLine(const size_t &index)
{
  this->m_drawLines.erase(this->m_drawLines.begin() + index);
}

std::vector<std::string> DragWidget::GetLastSelected()
{
  std::vector<std::string> res;
  DragObject *child = this->GetChildFromName(this->m_networkHardwareBegin);
  DragObject *child2 = this->GetChildFromName(this->m_networkHardwareEnd);
  if (child)
  {
    res.push_back(child->GetName());
  }
  else
  {
    res.push_back("");
  }

  if (child2)
  {
    res.push_back(child2->GetName());
  }
  else
  {
    res.push_back("");
  }

  res.push_back(this->m_networkHardwareType);

  return res;
}

void DragWidget::DrawLines()
{
  update();
}

void DragWidget::paintEvent(QPaintEvent * /*event*/)
{
  QPainter paint(this);

  QPen pen(Qt::black);
  pen.setWidth(2);
  pen.setCapStyle(Qt::RoundCap);

  QPen point(Qt::black);
  point.setWidth(2);
  point.setStyle(Qt::DotLine);
  point.setCapStyle(Qt::RoundCap);

  QPen p2p(Qt::green);
  p2p.setWidth(2);
  p2p.setCapStyle(Qt::RoundCap);


  for(size_t i = 0; i < this->m_drawLines.size(); i++)
  {
    if(this->GetChildFromName(this->m_drawLines.at(i).GetFirst())->GetName() != "" && 
       this->GetChildFromName(this->m_drawLines.at(i).GetSecond())->GetName() != "")
    {
      std::string type = this->m_drawLines.at(i).GetNetworkHardwareType();

      if(type == "WiredLink")
      {
        paint.setPen(pen);
      }
      else if(type == "WifiLink")
      {
        paint.setPen(point);
      }
      else if(type == "P2pLink")
      {
        paint.setPen(p2p);
      }
      DragObject *begin = this->GetChildFromName(this->m_drawLines.at(i).GetFirst());
      DragObject *end = this->GetChildFromName(this->m_drawLines.at(i).GetSecond());
      paint.drawLine((begin->pos().x() + (begin->width() / 2)), (begin->pos().y() + (begin->height() / 2)),
                     (end->pos().x() + (end->width() / 2)), (end->pos().y() + (end->height() / 2)));
    }
  }
  // to show the drawing line when we are selecting the second equipement from interconnection
  if(this->m_traceNetworkHardware)
  {
    if(this->m_networkHardwareBegin != "" && this->m_networkHardwareEnd == "")
    {
      if(this->m_networkHardwareType == "WiredLink")
      {
        paint.setPen(pen);
      }
      else if(this->m_networkHardwareType == "WifiLink")
      {
        paint.setPen(point);
      }
      else if(this->m_networkHardwareType == "P2pLink")
      {
        paint.setPen(p2p);
      }
      paint.drawLine((this->GetChildFromName(this->m_networkHardwareBegin))->pos().x() + 
          ((this->GetChildFromName(this->m_networkHardwareBegin))->width() / 2),
          (this->GetChildFromName(this->m_networkHardwareBegin))->pos().y() + 
          ((this->GetChildFromName(this->m_networkHardwareBegin))->height() / 2),
          mapFromGlobal(QCursor::pos()).x(),  mapFromGlobal(QCursor::pos()).y());
    }
  }
  paint.setPen(pen);
}

void DragWidget::DeleteSelected()
{
  DragObject *child = static_cast<DragObject*>(childAt(this->m_lastPosition));
  if(!child)
  {
    // test if we are under deleting a line !
    if(this->m_isDrawLine)
    {
      size_t linkToRemove = 0;
      bool isLinkToRemove = false;
      for(size_t i = 0; i < this->m_mw->GetGenerator()->GetNNetworkHardwares() || !isLinkToRemove; i++)
      {
        std::vector<std::string> nodes = this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetInstalledNodes();
        for(size_t j = 0; j < nodes.size(); j++)
        {
          if(this->m_lastLine.GetFirst() == nodes.at(j) ||
            this->m_lastLine.GetSecond() == nodes.at(j)  )
          {
            isLinkToRemove = true;
            linkToRemove = i;
          }
        }
      }
      if(isLinkToRemove)
      {
        if( (guiUtils::isNetworkHardware(this->m_lastLine.GetFirst()) &&
             guiUtils::isNetworkHardware(this->m_lastLine.GetSecond()) ) ||
            (!guiUtils::isNetworkHardware(this->m_lastLine.GetFirst()) &&
             !guiUtils::isNetworkHardware(this->m_lastLine.GetSecond()) )  )
        {
          this->m_mw->GetGenerator()->RemoveNetworkHardware(this->m_mw->GetGenerator()->GetNetworkHardware(linkToRemove)->GetNetworkHardwareName());
        }
        else if( guiUtils::isNetworkHardware(this->m_lastLine.GetFirst()) )
        {
          std::vector<std::string> nodes = this->m_mw->GetGenerator()->GetNetworkHardware(linkToRemove)->GetInstalledNodes();
          for(size_t i = 0; i < nodes.size(); i++)
          {
            if(nodes.at(i) == this->m_lastLine.GetSecond())
            {
              this->m_mw->GetGenerator()->GetNetworkHardware(linkToRemove)->removeInstalledNode(i);
              break;
            }
          }
        }
        else if( guiUtils::isNetworkHardware(this->m_lastLine.GetSecond()) )
        {
          std::vector<std::string> nodes = this->m_mw->GetGenerator()->GetNetworkHardware(linkToRemove)->GetInstalledNodes();
          for(size_t i = 0; i < nodes.size(); i++)
          {
            if(nodes.at(i) == this->m_lastLine.GetFirst())
            {
              this->m_mw->GetGenerator()->GetNetworkHardware(linkToRemove)->removeInstalledNode(i);
              break;
            }
          }
        }
        for(size_t i = 0; i < this->m_drawLines.size(); i++)
        {
          if(this->m_drawLines.at(i).GetFirst() == this->m_lastLine.GetFirst() &&
             this->m_drawLines.at(i).GetSecond() == this->m_lastLine.GetSecond())
          {
            this->EraseDrawLine(i);
            break;
          }
        }
      }
      this->UpdateToolTips();
    }
    this->m_isDrawLine = false;
  }
  
  if (!child)
  {
    this->m_mw->m_delAction->setDisabled(true);
    return;
  }

  // delete equipement
  try
  {
    this->m_mw->GetGenerator()->RemoveNode(child->GetName());
  }
  catch(const std::exception)
  {}

  // delete network hardware
  try
  {
    this->m_mw->GetGenerator()->RemoveNetworkHardware(child->GetName());
  }
  catch(const std::exception)
  {}

  // delete connections
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < this->m_mw->GetGenerator()->GetNNetworkHardwares(); i++)
  {
    std::vector<std::string> nodes = this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetInstalledNodes();
    for(size_t j = 0; j < nodes.size(); j++)
    {
      // if the child to be deleted is connected ... we must remove it.
      if(child->GetName() == nodes.at(j))
      {
        objDelLink.push_back(this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetNetworkHardwareName());
        try
        {
          this->m_mw->GetGenerator()->GetNetworkHardware(i)->removeInstalledNode(j);
        }
        catch(const std::out_of_range &e)
        {
          this->m_mw->m_delAction->setDisabled(true);
        }
      }
    }
  }

  // delete hide hub
  bool isHide = true;
  for(size_t i = 0; i < objDelLink.size(); i++)
  {
    for(size_t j = 0; j < this->m_mw->GetGenerator()->GetNNetworkHardwares(); j++)
    {
      if( objDelLink.at(i) == this->m_mw->GetGenerator()->GetNetworkHardware(j)->GetNetworkHardwareName() )
      {
        if(this->m_mw->GetGenerator()->GetNetworkHardware(j)->GetInstalledNodes().size() <= 1)
        {
          // the link where the deleted object 
          // check if the link is hide. 
          isHide = true;
          for(size_t k = 0; k < (size_t)this->children().size(); k++)
          {
            if(dynamic_cast<DragObject*>((this->children().at(k))))
            {
              if( dynamic_cast<DragObject*>((this->children().at(k)))->GetName() == this->m_mw->GetGenerator()->GetNetworkHardware(j)->GetNetworkHardwareName())
              {
                isHide = false;
              }
            }
          }
          if(isHide)
          {
            this->m_mw->GetGenerator()->RemoveNetworkHardware(this->m_mw->GetGenerator()->GetNetworkHardware(j)->GetNetworkHardwareName());
          }
        }
      }
    }
  }

  // remove from link part ...
  if(child->GetName() == this->GetChildFromName(this->m_networkHardwareBegin)->GetName())
  {
    this->m_networkHardwareBegin = "";
  }
  if(child->GetName() == this->GetChildFromName(this->m_networkHardwareEnd)->GetName())
  {
    this->m_networkHardwareEnd = "";
  }
  for(size_t i = 0; i < this->m_drawLines.size(); i++)
  {
    if(child->GetName() == this->GetChildFromName(this->m_drawLines.at(i).GetFirst())->GetName() || 
       child->GetName() == this->GetChildFromName(this->m_drawLines.at(i).GetSecond())->GetName())
    {
      try
      {
        this->m_drawLines.erase(this->m_drawLines.begin() + i);
      }
      catch(const std::out_of_range &e)
      {
        this->m_mw->m_delAction->setDisabled(true);
      }
    }
  }

  // remove application. 
  std::string sender("");
  std::string receiver("");
  for(size_t i = 0; i < this->m_mw->GetGenerator()->GetNApplications(); i++)
  {
    if((child->GetName()).find("nodesGroup_") == 0)
    {
      sender = this->m_mw->GetGenerator()->GetApplication(i)->GetSenderNode();
      receiver = this->m_mw->GetGenerator()->GetApplication(i)->GetReceiverNode();

      if(sender.find("NodeContainer") == 0)
      {
        sender = sender.substr((sender.find_first_of("(") + 1), (sender.find_first_of(".") - sender.find_first_of("(") - 1));
      }
      if(receiver.find("NodeContainer") == 0)
      {
        receiver = receiver.substr(receiver.find_first_of("(") + 1, (receiver.find_first_of(".") - receiver.find_first_of("(") - 1));
      }
    }
    else
    {
      sender = this->m_mw->GetGenerator()->GetApplication(i)->GetSenderNode();
      receiver = this->m_mw->GetGenerator()->GetApplication(i)->GetReceiverNode(); 
    }

    if(child->GetName() == sender || child->GetName() == receiver )
    {
      this->m_mw->GetGenerator()->RemoveApplication(this->m_mw->GetGenerator()->GetApplication(i)->GetAppName());
    }
  }

  // clean gui
  this->UpdateToolTips();
  child->clear();
  child->Destroy();

  this->m_mw->m_delAction->setDisabled(true);
}

void DragWidget::UpdateToolTips()
{
  // Get all equipements on the drag n drop zone
  for(size_t i = 0; i < (size_t)this->children().size(); i++)
  {
    DragObject *child = dynamic_cast<DragObject*>(this->children().at(i));
    if(child)
    {
      if(child->GetName() != "deleted")
      {
        // start build new tool tip text !
        std::string new_tooltip = child->GetName();
        std::vector<std::string> connectedTo;
        bool isConnected = false;
        for(size_t i = 0; i < this->m_mw->GetGenerator()->GetNNetworkHardwares(); i++)
        {
          for(size_t j = 0; j < this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetInstalledNodes().size(); j++)
          {
            if( this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetInstalledNodes().at(j) == child->GetName() )
            {
              std::string iface("");
              isConnected = true;
              if(this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetNetworkHardwareName().find("emu_") == 0) 
              {
                iface = " (" + dynamic_cast<Emu*>(this->m_mw->GetGenerator()->GetNetworkHardware(i))->GetIfaceName() + ")";
              }
              else if( this->m_mw->GetGenerator()->GetNetworkHardware(i)->GetNetworkHardwareName().find("tap_") == 0)
              {
                iface = " (" + dynamic_cast<Tap*>(this->m_mw->GetGenerator()->GetNetworkHardware(i))->GetIfaceName() + ")";
              }
              
              connectedTo.push_back("10.0." + utils::integerToString(i) + "." + utils::integerToString(j + 1) + iface);
            }
          }
        }
        if(isConnected)
        {
          for(size_t i = 0; i < connectedTo.size(); i++)
          {
            new_tooltip += "<br />"+connectedTo.at(i);
          }
        }

        for(size_t i = 0;  i < this->m_mw->GetGenerator()->GetNApplications(); i++)
        {
          if(this->m_mw->GetGenerator()->GetApplication(i)->GetSenderNode() == child->GetName())
          {
            new_tooltip += "<br />Sender on " + this->m_mw->GetGenerator()->GetApplication(i)->GetAppName();
          }
          else if(this->m_mw->GetGenerator()->GetApplication(i)->GetReceiverNode() == child->GetName())
          {
            new_tooltip += "<br />Receiver on " + this->m_mw->GetGenerator()->GetApplication(i)->GetAppName();
          }
        }

        child->SetToolTipText(QString(new_tooltip.c_str()));
        child->setToolTip(QString(new_tooltip.c_str()));
      }
    }
  }
}


//
// Set/Get *
//
void DragWidget::SetMainWindow(MainWindow *mw)
{
  this->m_mw = mw;
}

bool DragWidget::GetTraceNetworkHardware()
{
  return this->m_traceNetworkHardware;
}

void DragWidget::SetTraceNetworkHardware(const bool &state)
{
  this->m_traceNetworkHardware = state;
}

void DragWidget::SetNetworkHardwareBegin(const std::string &linkBegin)
{
  this->m_networkHardwareBegin = linkBegin;
}

std::string DragWidget::GetNetworkHardwareBegin()
{
  return this->m_networkHardwareBegin;
}

void DragWidget::SetNetworkHardwareEnd(const std::string &link)
{
  this->m_networkHardwareEnd = link;
}

std::string DragWidget::GetNetworkHardwareEnd()
{
  return this->m_networkHardwareEnd;
}

void DragWidget::SetNetworkHardwareType(const std::string& linkType)
{
  this->m_networkHardwareType = linkType;
}

std::string DragWidget::GetNetworkHardwareType() const
{
  return this->m_networkHardwareType;
}

