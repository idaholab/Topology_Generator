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
* \file DragWidget.cpp
* \brief The drag n drop zone file.
* \author Pierre Weiss
* \date 2009
*/

#include <QtGui>
#include <iostream>

#include "MainWindow.h"
#include "DragWidget.h"

#include "DragObject.h"


DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setAcceptDrops(true);
    setMouseTracking(true);
   
    this->traceLink = false;
    
    this->linkBegin = "";
    this->linkEnd = "";
    this->linkType = "";
}

DragWidget::~DragWidget()
{
}

void DragWidget::setMainWindow(MainWindow *_mw)
{
  this->mw = _mw;
}

void DragWidget::CreateObject(const std::string &type, const std::string &_name)
{
	DragObject *label = new DragObject(this);
	label->setName(_name);
	if(type.compare("Pc") == 0)
	{
    label->setPixmap(QPixmap(":/Ico/Pc.png"));
  } 
  if(type.compare("Pc-group") == 0)
	{
    label->setPixmap(QPixmap(":/Ico/Pc-group.png"));
  } 
  else if(type.compare("Emu") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Emu.png"));
  } 
  else if(type.compare("Tap") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Tap.png"));
  } 
  else if(type.compare("Ap") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Ap-Wifi.png"));
  } 
  else if(type.compare("Station") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/StationWifi.png"));
  } 
  else if(type.compare("Hub") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Hub.png"));
  } 
  else if(type.compare("Switch") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Switch.png"));
  } 
  else if(type.compare("Router") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/Router.png"));
  }
  label->move(10, 10);
  label->show();
  label->setAttribute(Qt::WA_DeleteOnClose);
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
   
    /* get the name from the last draged label */
    /* change the at number ... we are already on drag an elem. */
    DragObject *child = static_cast<DragObject*>(childAt( this->lastPosition ));
    DragObject *label = new DragObject(this);
    if(child)
    {
      label->setName(child->getName());
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
    this->mw->delAction->setDisabled(true);
    return;
  }
  if((child->getName()).compare("deleted") == 0)
  {
    /* the child has been deleted ... */
    return;
  }
  this->mw->delAction->setDisabled(false);

  this->lastPosition = event->pos();
  
  /* trace link ... */
  if(this->traceLink)
  {
    /* update if we drag an existant object. */
    
    /*il faut utiliser les noms des objects et non pas les positions ... les positions changent quand on drag et du coup après ont peut
    plus cast pour recup le child 
    ....*/
    
    /* set the attribute. */
    if(this->linkBegin == "")
    {
      /* begin is not used. */
      linkBegin = child->getName();
    }
    else if(this->linkEnd == "")
    {
      /* we got the last equipement. */
      DragObject *child2 = this->getChildFromName(this->linkBegin);
      if(child2)
      {
        if( (child->getName()).compare(child2->getName()) != 0)
        {
          linkEnd = child->getName();
          lines lig;
          lig.begin = this->linkBegin;
          lig.end = this->linkEnd;
          lig.type = this->linkType;
          this->drawLines.push_back(lig);
          
          this->mw->ValidLink();
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
}

void DragWidget::mouseMoveEvent(QMouseEvent * /*event*/)
{
  update();
}
    
void DragWidget::deleteSelected()
{
  DragObject *child = static_cast<DragObject*>(childAt(this->lastPosition));
  if (!child)
  {
    this->mw->delAction->setDisabled(true);
    return;
  }

  size_t indic = -1;
  /* Generator part */
  /* delete equipement. */
  for(size_t i = 0; i < (size_t) this->mw->gen->listEquipement.size(); i++)
  {
    if(this->mw->gen->listEquipement.at(i)->getNodeName().compare(child->getName()) == 0)
    {
      indic = i;
      break;
    }
  }
  if(indic != (size_t) -1 )
  {
    this->mw->gen->RemoveEquipement(indic);
  }
  
  /* delete link. */
  indic = -1;
  for(size_t i = 0; i < (size_t) this->mw->gen->listLink.size(); i++)
  {
    if((this->mw->gen->listLink.at(i)->getLinkName()).compare(child->getName()) == 0)
    {
      indic = i;
      if((child->getName()).find("emu_") == 0 || (child->getName()).find("wifi_") == 0 ||
         (child->getName()).find("bridge_") == 0 || (child->getName()).find("tap_") == 0  || (child->getName()).find("hub_") == 0)
      {
        for(size_t j = 0; j < (size_t) this->mw->gen->listEquipement.size(); j++)
        {
          if( (this->mw->gen->listEquipement.at(j)->getNodeName()).compare(this->mw->gen->listLink.at(i)->getNodes().at(0)) == 0)
          {
            this->mw->gen->RemoveEquipement(j);
          }
        }
      }
    }
  }
  if(indic != (size_t) -1 )
  {
    this->mw->gen->RemoveLink(indic);
  }
  
  /* delete connections */
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < (size_t) this->mw->gen->listLink.size(); i++)
  {
    std::vector<std::string> nodes = this->mw->gen->listLink.at(i)->getNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      /* if the child to be deleted is connected ... we must remove it. */
      if((child->getName()).compare(nodes.at(j)) == 0)
      {
        objDelLink.push_back(this->mw->gen->listLink.at(i)->getLinkName());
        this->mw->gen->listLink.at(i)->nodes.erase(this->mw->gen->listLink.at(i)->nodes.begin() + j);
      }
    }
  }
  
  /* delete hide create hub for until two Pc for example. */
  bool isHide = true;
  for(size_t i = 0; i < (size_t) objDelLink.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->mw->gen->listLink.size(); j++)
    {
      if( (objDelLink.at(i)).compare(this->mw->gen->listLink.at(j)->getLinkName()) == 0 )
      {
        if(this->mw->gen->listLink.at(j)->getNodes().size() <= 1)
        {
          /* the link where the deleted object */
          /* check if the link is hide. */
          isHide = true;
          for(size_t k = 0; k < (size_t) this->children().size(); k++)
          {
            if( (static_cast<DragObject*>((this->children().at(k)))->getName()).compare(this->mw->gen->listLink.at(j)->getLinkName()) == 0)
            {
              isHide = false;
            }
          }
          if(isHide)
          {
            this->mw->gen->RemoveLink(j);
          }
        }
      }
    }
  }
  
  /* remove pc which are connected and don't exist ... */
  bool exists = false;
  size_t nbrConnex = 0;
  for(size_t i = 0; i < (size_t) this->mw->gen->listLink.size(); i++)
  {
    std::vector<std::string> nodes = this->mw->gen->listLink.at(i)->getNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      exists = false;
      /* check if exist ... */
      for(size_t k = 0; k < (size_t) this->mw->gen->listEquipement.size(); k++)
      {
        if(this->mw->gen->listEquipement.at(k)->getNodeName() == nodes.at(j))
        {
          exists = true;
        }
      }
      if(!exists)
      {
        this->mw->gen->listLink.at(i)->nodes.erase(this->mw->gen->listLink.at(i)->nodes.begin() + j);
      }
      else
      {
        /* check if the existant node is hide and just connected to this link. */
        isHide = true;
        for(size_t k = 0; k < (size_t) this->children().size(); k++)
        {
          if( (static_cast<DragObject*>((this->children().at(k)))->getName()).compare(nodes.at(j)) == 0)
          {
            isHide = false;
          }
        }
        if(isHide)
        {
          /* check the number of connection .. */
          nbrConnex = 0;
          for(size_t z = 0; z < (size_t) this->mw->gen->listLink.size(); z++)
          {
            std::vector<std::string> tnodes = this->mw->gen->listLink.at(z)->getNodes();
            for(size_t zz = 0; zz < (size_t) tnodes.size(); zz++)
            {
              if(tnodes.at(zz) == nodes.at(j))
              {
                nbrConnex += 1;
              }
            }
          }
          if(nbrConnex <= 1)
          {
            this->mw->gen->listLink.at(i)->nodes.erase(this->mw->gen->listLink.at(i)->nodes.begin() + j);
          }
        }
      }
    }
  }
  
  /* remove hide pc which don't are connected. */
  for(size_t i = 0; i < (size_t) this->mw->gen->listEquipement.size(); i++)
  {
    isHide = true;
    for(size_t k = 0; k < (size_t) this->children().size(); k++)
    {
      if( (static_cast<DragObject*>((this->children().at(k)))->getName()).compare(this->mw->gen->listEquipement.at(i)->getNodeName()) == 0)
      {
        isHide = false;
      }
    }
    if(isHide)
    {
      this->mw->gen->RemoveEquipement(i);
    }
  }
  
  
  /* remove from link part ... */
  if(child->getName() == this->getChildFromName(this->linkBegin)->getName())
  {
    this->linkBegin = "";
  }
  if(child->getName() == this->getChildFromName(this->linkEnd)->getName())
  {
    this->linkEnd = "";
  }
  for(size_t i = 0; i < (size_t) this->drawLines.size(); i++)
  {
    if(child->getName() == this->getChildFromName(this->drawLines.at(i).begin)->getName() || child->getName() == this->getChildFromName(this->drawLines.at(i).end)->getName())
    {
      this->drawLines.erase(this->drawLines.begin() + i);
    }
  }

  /* Gui part */
  child->clear();
  child->Destroy();
  
  this->mw->delAction->setDisabled(true);
 
}

std::vector<std::string> DragWidget::getLastSelected()
{
  std::vector<std::string> res;
  DragObject *child = this->getChildFromName(this->linkBegin);
  DragObject *child2 = this->getChildFromName(this->linkEnd);
  if (child)
  {
    res.push_back(child->getName());
  }
  else
  {
    res.push_back("");
  }
  
  if (child2)
  {
    res.push_back(child2->getName());
  }
  else
  {
    res.push_back("");
  }
  
  res.push_back(this->linkType);
  
  return res;
}

void DragWidget::DrawLine()
{
  update();
}

void DragWidget::ResetSelected()
{
  this->linkBegin = "";
  this->linkEnd = "";
  this->linkType = "";
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

    
    QPen p2p(Qt::red);
    p2p.setWidth(2);
    p2p.setCapStyle(Qt::RoundCap);

    
    for(size_t i = 0; i < (size_t) this->drawLines.size(); i++)
    {
      if(this->getChildFromName(this->drawLines.at(i).begin)->getName() != "" && this->getChildFromName(this->drawLines.at(i).end)->getName() != "")
      {
        if(this->drawLines.at(i).type == "HardLink")
        {
          paint.setPen(pen);
        }
        else if(this->drawLines.at(i).type == "WifiLink")
        {
          paint.setPen(point);
        }
        else if(this->drawLines.at(i).type == "P2pLink")
        {
          paint.setPen(p2p);
        }
        
        paint.drawLine( (this->getChildFromName(this->drawLines.at(i).begin)->pos().x()+((this->getChildFromName(this->drawLines.at(i).begin))->width()/2)), 
                        (this->getChildFromName(this->drawLines.at(i).begin)->pos().y()+((this->getChildFromName(this->drawLines.at(i).begin))->height()/2)),
                      (this->getChildFromName(this->drawLines.at(i).end)->pos().x()+((this->getChildFromName(this->drawLines.at(i).end))->width()/2)),
                        (this->getChildFromName(this->drawLines.at(i).end)->pos().y()+((this->getChildFromName(this->drawLines.at(i).end))->height()/2))
                    );
      }
    }
    if(this->traceLink)
    {
      if(this->linkBegin != "" && this->linkEnd == "")
      {
        paint.drawLine((this->getChildFromName(this->linkBegin))->pos().x()+((this->getChildFromName(this->linkBegin))->width()/2),
                       (this->getChildFromName(this->linkBegin))->pos().y()+((this->getChildFromName(this->linkBegin))->height()/2),
                        mapFromGlobal(QCursor::pos()).x(),  mapFromGlobal(QCursor::pos()).y());
      }
    }
    paint.setPen(pen);
}

DragObject* DragWidget::getChildFromName(const std::string &name)
{
  for(size_t i = 0; i < (size_t) this->children().size(); i++)
  {
    DragObject *child = dynamic_cast<DragObject*>(this->children().at(i));
    if(child)
    {
      if( (child->getName()).compare(name) == 0)
      {
        /* we got the right child ... */
        return child;
      }
    }
  }
  return new DragObject(this);
}




