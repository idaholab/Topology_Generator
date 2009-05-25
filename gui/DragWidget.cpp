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

#include "DragWidget.h"
#include "DragObject.h"


DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setAcceptDrops(true);
}

DragWidget::~DragWidget()
{
  //delete last;
}

void DragWidget::CreateObject(const std::string &type, const std::string &_name)
{
	DragObject *label = new DragObject(this);
	label->setName(_name);
	if(type.compare("Pc") == 0)
	{
    label->setPixmap(QPixmap(":/Ico/PC.png"));
  } 
  else if(type.compare("Emu") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/PC-Emu.png"));
  } 
  else if(type.compare("Tap") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/PC-Tap.png"));
  } 
  else if(type.compare("Ap") == 0)
  {
    label->setPixmap(QPixmap(":/Ico/AP-Wifi.png"));
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
    DragObject *child = static_cast<DragObject*>(childAt(this->lastPosition));
    DragObject *label = new DragObject(this);
    /* avoid seg fault ... */
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
     if (!child){
         return;
     }
     this->lastPosition = event->pos();
     //~ std::cout << "Object to move : " << child->getName() << std::endl;

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
         child->close();
     else {
         child->show();
         child->setPixmap(pixmap);
     }
}
