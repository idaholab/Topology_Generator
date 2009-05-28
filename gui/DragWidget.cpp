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
   
    this->traceLink = false;
    
    this->linkBegin = "";
    this->linkEnd = "";

}

DragWidget::~DragWidget()
{
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
    MainWindow::delAction->setDisabled(true);
    return;
  }
  if((child->getName()).compare("deleted") == 0)
  {
    /* the child has been deleted ... */
    return;
  }
  MainWindow::delAction->setDisabled(false);

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
      std::cout << "Define linkBegin !" << std::endl;
    }
    else if(this->linkEnd == "")
    {
      /* we got the last equipement. */
      DragObject *child2 = this->getChildFromName(this->linkBegin);
      if(child2)
      {
        if( (child->getName()).compare(child2->getName()) != 0)
        {
          std::cout << "Define linkEnd !" << std::endl;
          linkEnd = child->getName();
          lines lig;
          lig.begin = this->linkBegin;
          lig.end = this->linkEnd;
          this->drawLines.push_back(lig);
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

void DragWidget::deleteSelected()
{
  DragObject *child = static_cast<DragObject*>(childAt(this->lastPosition));
  if (!child)
  {
    MainWindow::delAction->setDisabled(true);
    return;
  }

  size_t indic = -1;
  /* Generator part */
  /* delete equipement. */
  for(size_t i = 0; i < (size_t) MainWindow::gen->listEquipement.size(); i++)
  {
    if(MainWindow::gen->listEquipement.at(i)->getNodeName().compare(child->getName()) == 0)
    {
      indic = i;
    }
  }
  if(indic != (size_t) -1 )
  {
    MainWindow::gen->RemoveEquipement(indic);
  }
  
  /* delete link. */
  indic = -1;
  for(size_t i = 0; i < (size_t) MainWindow::gen->listLink.size(); i++)
  {
    if(MainWindow::gen->listLink.at(i)->getLinkName().compare(child->getName()) == 0)
    {
      indic = i;
      if((child->getName()).find("emu_") == 0)
      {
        for(size_t j = 0; j < (size_t) MainWindow::gen->listEquipement.size(); j++)
        {
          if( (MainWindow::gen->listEquipement.at(j)->getNodeName()).compare(MainWindow::gen->listLink.at(i)->getNodes().at(0)) == 0)
          {
            MainWindow::gen->RemoveEquipement(j);
            break;
          }
        }
      }
    }
  }
  if(indic != (size_t) -1 )
  {
    MainWindow::gen->RemoveLink(indic);
  }
  
  /* delete connections */
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < (size_t) MainWindow::gen->listLink.size(); i++)
  {
    std::vector<std::string> nodes = MainWindow::gen->listLink.at(i)->getNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      /* if the child to be deleted is connected ... we must remove it. */
      if((child->getName()).compare(nodes.at(j)) == 0)
      {
        objDelLink.push_back(MainWindow::gen->listLink.at(i)->getLinkName());
        MainWindow::gen->listLink.at(i)->nodes.erase(MainWindow::gen->listLink.at(i)->nodes.begin() + j);
      }
    }
  }
  
  /* delete hide create hub for hard link from pc to pc for example. */
  bool isHide = true;
  for(size_t i = 0; i < (size_t) objDelLink.size(); i++)
  {
    for(size_t j = 0; j < (size_t) MainWindow::gen->listLink.size(); j++)
    {
      if( (objDelLink.at(i)).compare(MainWindow::gen->listLink.at(j)->getLinkName()) == 0 )
      {
        if(MainWindow::gen->listLink.at(j)->getNodes().size() <= 1)
        {
          /* the link where the deleted object */
          /* check if the link is hide. */
          isHide = true;
          for(size_t k = 0; k < (size_t) this->children().size(); k++)
          {
            if( (static_cast<DragObject*>((this->children().at(k)))->getName()).compare(MainWindow::gen->listLink.at(j)->getLinkName()) == 0)
            {
              isHide = false;
            }
          }
          if(isHide)
          {
            MainWindow::gen->RemoveLink(j);
          }
        }
      }
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
  
  MainWindow::delAction->setDisabled(true);
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
  
  return res;
}

void DragWidget::DrawLine()
{
  
}

void DragWidget::ResetSelected()
{
  this->lastPosition = QPoint(-1, -1);
}

void DragWidget::paintEvent(QPaintEvent * event)
{
  QPainter paint(this);
  
  for(size_t i = 0; i < (size_t) this->drawLines.size(); i++)
  {
    paint.drawLine( this->getChildFromName(this->drawLines.at(i).begin)->pos(), this->getChildFromName(this->drawLines.at(i).end)->pos());
  }
  if(this->traceLink)
  {
    if(this->linkBegin != "" && this->linkEnd == "")
    {
      std::cout << "Single Paint (" << this->getChildFromName(this->linkBegin)->pos().x() << " - " << this->getChildFromName(this->linkBegin)->pos().y() << ")" << std::endl;
      paint.drawLine((this->getChildFromName(this->linkBegin))->pos(), QCursor::pos());
    }
  }
  paint.setPen(Qt::black);
  update();
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


