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
 * \file DragWidget.cpp
 * \brief The drag'n'drop zone file.
 * \author Pierre Weiss
 * \date 2009
 */

#include <QtGui>
#include <iostream>
#include <stdexcept>

#include "MainWindow.h"
#include "DragWidget.h"

#include "DragObject.h"
#include "DragLines.h"

DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
  setMinimumSize(400, 400);
  setAcceptDrops(true);
  setMouseTracking(true);

  this->traceLink = false;

  this->linkBegin = "";
  this->linkEnd = "";
  this->linkType = "";

  this->appsEnable = false;
  this->appsPing = false;
  this->appsUdpEcho = false;
  this->appsTcp = false;
  this->appsServer = "";
  this->appsClient = "";
  this->startTime = -1;
  this->endTime = -1;
  this->port = -1;
}

DragWidget::~DragWidget()
{
  delete this->timer;
}

void DragWidget::setMainWindow(MainWindow *_mw)
{
  this->mw = _mw;
}

void DragWidget::CreateObject(const std::string &type, const std::string &_name)
{
  DragObject *label = new DragObject(this);
  label->setName(_name);
  if(type == "Pc")
  {
    label->setPixmap(QPixmap(":/Ico/Pc.png"));
  } 
  if(type == "Pc-group")
  {
    label->setPixmap(QPixmap(":/Ico/Pc-group.png"));
  } 
  else if(type == "Emu")
  {
    label->setPixmap(QPixmap(":/Ico/Emu.png"));
  } 
  else if(type == "Tap")
  {
    label->setPixmap(QPixmap(":/Ico/Tap.png"));
  } 
  else if(type == "Ap")
  {
    label->setPixmap(QPixmap(":/Ico/Ap-Wifi.png"));
  } 
  else if(type == "Station")
  {
    label->setPixmap(QPixmap(":/Ico/StationWifi.png"));
  } 
  else if(type == "Hub")
  {
    label->setPixmap(QPixmap(":/Ico/Hub.png"));
  } 
  else if(type == "Switch")
  {
    label->setPixmap(QPixmap(":/Ico/Switch.png"));
  } 
  else if(type == "Router")
  {
    label->setPixmap(QPixmap(":/Ico/Router.png"));
  }
  label->move(10, 10);
  label->show();
  label->setAttribute(Qt::WA_DeleteOnClose);

  this->timer = new QTimer();
  this->timer->start(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));

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
  if(child->getName() == "deleted")
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
        if( child->getName() != child2->getName())
        {
          linkEnd = child->getName();
          DragLines lig;
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

  /* application. */
  if(this->appsEnable)
  {
    if(this->appsServer == "")
    {
      this->appsServer = child->getName();
    }
    else
    {
      if(this->appsClient == "" && child->getName() != this->appsServer)
      {
        this->appsClient = child->getName();
      }
    }
  }

  if(this->appsPing)
  {
    ShowGuiPing();
  }

  if(this->appsUdpEcho)
  {
    ShowGuiUdpEcho();
  }

  if(this->appsTcp)
  {
    ShowGuiTcp();
  }

  //~ this->appsEnable = false;
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

  /* Generator part */
  /* delete equipement. */
  try
  {
    this->mw->gen->RemoveNode(child->getName());
  }
  catch(const std::exception)
  {}

  /* delete link. */
  /* Attention, if you delete a Link wich need a Node, you must delete it ! */
  try
  {
    this->mw->gen->RemoveLink(child->getName());
  }
  catch(const std::exception)
  {}

  /* delete connections */
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < (size_t) this->mw->gen->listLink.size(); i++)
  {
    std::vector<std::string> nodes = this->mw->gen->listLink.at(i)->getNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      /* if the child to be deleted is connected ... we must remove it. */
      if(child->getName() == nodes.at(j))
      {
        objDelLink.push_back(this->mw->gen->listLink.at(i)->getLinkName());
        try
        {
          this->mw->gen->listLink.at(i)->nodes.erase(this->mw->gen->listLink.at(i)->nodes.begin() + j);
        }
        catch(const std::out_of_range &e)
        {
          this->mw->delAction->setDisabled(true);
        }
      }
    }
  }

  /* delete hide create hub for until two Pc for example. */
  bool isHide = true;
  for(size_t i = 0; i < (size_t) objDelLink.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->mw->gen->listLink.size(); j++)
    {
      if( objDelLink.at(i) == this->mw->gen->listLink.at(j)->getLinkName() )
      {
        if(this->mw->gen->listLink.at(j)->getNodes().size() <= 1)
        {
          // the link where the deleted object 
          // check if the link is hide. 
          isHide = true;
          for(size_t k = 0; k < (size_t) this->children().size(); k++)
          {
            if(dynamic_cast<DragObject*>((this->children().at(k))))
            {
              if( dynamic_cast<DragObject*>((this->children().at(k)))->getName() == this->mw->gen->listLink.at(j)->getLinkName())
              {
                isHide = false;
              }
            }
          }
          if(isHide)
          {
            this->mw->gen->RemoveLink(this->mw->gen->listLink.at(j)->getLinkName());
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
      try
      {
        this->drawLines.erase(this->drawLines.begin() + i);
      }
      catch(const std::out_of_range &e)
      {
        this->mw->delAction->setDisabled(true);
      }
    }
  }

  /* remove application. */
  std::string sender("");
  std::string receiver("");
  for(size_t i = 0; i < (size_t) this->mw->gen->listApplication.size(); i++)
  {
    if((child->getName()).find("nodesGroup_") == 0)
    {
      sender = this->mw->gen->listApplication.at(i)->getSenderNode();
      receiver = this->mw->gen->listApplication.at(i)->getReceiverNode();

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
      sender = this->mw->gen->listApplication.at(i)->getSenderNode();
      receiver = this->mw->gen->listApplication.at(i)->getReceiverNode(); 
    }

    if(child->getName() == sender ||
        child->getName() == receiver )
    {
      this->mw->gen->RemoveApplication(this->mw->gen->listApplication.at(i)->getAppName());
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


  QPen p2p(Qt::green);
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
      DragObject *begin = this->getChildFromName(this->drawLines.at(i).begin);
      DragObject *end = this->getChildFromName(this->drawLines.at(i).end);
      paint.drawLine( (begin->pos().x() + (begin->width() / 2)), (begin->pos().y() + (begin->height() / 2)),
          (end->pos().x() + (end->width() / 2)), (end->pos().y() + (end->height() / 2))
          );
    }
  }
  if(this->traceLink)
  {

    if(this->linkBegin != "" && this->linkEnd == "")
    {
      if(this->linkType == "HardLink")
      {
        paint.setPen(pen);
      }
      else if(this->linkType == "WifiLink")
      {
        paint.setPen(point);
      }
      else if(this->linkType == "P2pLink")
      {
        paint.setPen(p2p);
      }
      paint.drawLine((this->getChildFromName(this->linkBegin))->pos().x() + ((this->getChildFromName(this->linkBegin))->width() / 2),
          (this->getChildFromName(this->linkBegin))->pos().y() + ((this->getChildFromName(this->linkBegin))->height() / 2),
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
      if( child->getName() == name)
      {
        /* we got the right child ... */
        return child;
      }
    }
  }
  return new DragObject(this);
}


void DragWidget::ShowGuiPing()
{
  this->appsEnable = false;

  dialog = new QDialog(this);
  dialog->setWindowTitle("Ping");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);//QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->appsServer != "")
  {
    label_machineLeft = "Sender : "+this->appsServer;
  }
  else
  {
    label_machineLeft = "Sender : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->appsClient != "")
  {
    label_machineRight = "Target : "+this->appsClient;
  }
  else
  {
    label_machineRight = "Target : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_startTime = new QLabel("Start time (s):", dialog);
  layout->addWidget(lab_startTime, 5, 0);

  QLineEdit *line_startTime = new QLineEdit(dialog);
  if(this->startTime != (size_t) -1)
  {
    line_startTime->insert(Generator::toString(this->startTime).c_str());
  }
  layout->addWidget(line_startTime, 5, 1);

  QLabel *lab_endTime = new QLabel("End time (s):", dialog);
  layout->addWidget(lab_endTime, 6, 0);

  QLineEdit *line_endTime = new QLineEdit(dialog);
  if(this->endTime != (size_t) -1)
  {
    line_endTime->insert(Generator::toString(this->endTime).c_str());
  }
  layout->addWidget(line_endTime, 6, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    this->startTime = line_startTime->text().toInt();
    this->endTime = line_endTime->text().toInt();

    if(this->appsServer != "" && this->appsClient != "" && this->startTime != (size_t) -1 && this->startTime != (size_t) -1)
    {
      if((this->startTime < this->endTime))
      {
        this->mw->ValidApps();
        this->appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Ping", "Start time can't be greather than end time.");
        this->ShowGuiPing();
      }
    }
    else
    {
      if(this->appsServer == "" || this->appsClient == "")
      {
        QMessageBox::about(this, "ping", "Sorry, you must choose all machines.");
        this->ShowGuiPing();
      }
      else
      {
        if(this->startTime == (size_t) -1 || this->endTime == (size_t) -1)
        {
          QMessageBox::about(this, "Ping", "Sorry, start time and end time can't be null.");
          this->ShowGuiPing();
        }
      }
    }
  }

}

void DragWidget::ChooseServer()
{
  this->appsEnable = true;
  dialog->hide();
  this->appsServer = "";
}

void DragWidget::ChooseClient()
{
  this->appsEnable = true; 
  dialog->hide();
  this->appsClient = "";
}

void DragWidget::Cancel()
{
  dialog->hide();
  this->appsServer = "";
  this->appsClient = "";

  this->appsEnable = false;
  this->appsPing = false;
  this->appsUdpEcho = false;
  this->appsTcp = false;
}

void DragWidget::ShowGuiUdpEcho()
{
  this->appsEnable = false;

  dialog = new QDialog(this);
  dialog->setWindowTitle("Udp Echo");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->appsServer != "")
  {
    label_machineLeft = "Server : "+this->appsServer;
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->appsClient != "")
  {
    label_machineRight = "Client : "+this->appsClient;
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_startTime = new QLabel("Start time (s):", dialog);
  layout->addWidget(lab_startTime, 5, 0);

  QLineEdit *line_startTime = new QLineEdit(dialog);
  if(this->startTime != (size_t) -1)
  {
    line_startTime->insert(Generator::toString(this->startTime).c_str());
  }
  layout->addWidget(line_startTime, 5, 1);

  QLabel *lab_endTime = new QLabel("End time (s):", dialog);
  layout->addWidget(lab_endTime, 6, 0);

  QLineEdit *line_endTime = new QLineEdit(dialog);
  if(this->endTime != (size_t) -1)
  {
    line_endTime->insert(Generator::toString(this->endTime).c_str());
  }
  layout->addWidget(line_endTime, 6, 1);

  QLabel *lab_port = new QLabel("Port :", dialog);
  layout->addWidget(lab_port, 7, 0);

  QLineEdit *line_port = new QLineEdit(dialog);
  if(this->port != (size_t) -1)
  {
    line_port->insert(Generator::toString(this->port).c_str());
  }
  layout->addWidget(line_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    this->startTime = line_startTime->text().toInt();
    this->endTime = line_endTime->text().toInt();
    this->port = line_port->text().toInt();

    if(this->appsServer != "" && this->appsClient != "" && this->startTime != (size_t) -1 && this->startTime != (size_t) -1 && this->port != (size_t) -1)
    {
      if((this->startTime < this->endTime))
      {
        this->mw->ValidApps();
        this->appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Udp Echo", "Start time can't be greather than end time.");
        this->ShowGuiUdpEcho();
      }
    }
    else
    {
      if(this->appsServer == "" || this->appsClient == "")
      {
        QMessageBox::about(this, "Udp Echo", "Sorry, you must choose all machines.");
        this->ShowGuiUdpEcho();
      }
      else
      {
        if(this->startTime == (size_t) -1 || this->endTime == (size_t) -1)
        {
          QMessageBox::about(this, "Udp Echo", "Sorry, start time and end time can't be null.");
          this->ShowGuiUdpEcho();
        }
        else
        {
          if(this->port == (size_t) -1)
          {
            QMessageBox::about(this, "Udp Echo", "Sorry, port field can't be null.");
            this->ShowGuiUdpEcho();
          }
        }
      }
    }
  }

}

void DragWidget::ShowGuiTcp()
{
  this->appsEnable = false;

  dialog = new QDialog(this);
  dialog->setWindowTitle("Tcp Large Transfer");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->appsServer != "")
  {
    label_machineLeft = "Server : "+this->appsServer;
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->appsClient != "")
  {
    label_machineRight = "Client : "+this->appsClient;
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_startTime = new QLabel("Start time (s):", dialog);
  layout->addWidget(lab_startTime, 5, 0);

  QLineEdit *line_startTime = new QLineEdit(dialog);
  if(this->startTime != (size_t) -1)
  {
    line_startTime->insert(Generator::toString(this->startTime).c_str());
  }
  layout->addWidget(line_startTime, 5, 1);

  QLabel *lab_endTime = new QLabel("End time (s):", dialog);
  layout->addWidget(lab_endTime, 6, 0);

  QLineEdit *line_endTime = new QLineEdit(dialog);
  if(this->endTime != (size_t) -1)
  {
    line_endTime->insert(Generator::toString(this->endTime).c_str());
  }
  layout->addWidget(line_endTime, 6, 1);

  QLabel *lab_port = new QLabel("Port :", dialog);
  layout->addWidget(lab_port, 7, 0);

  QLineEdit *line_port = new QLineEdit(dialog);
  if(this->port != (size_t) -1)
  {
    line_port->insert(Generator::toString(this->port).c_str());
  }
  layout->addWidget(line_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  dialog->setLayout(layout);
  dialog->exec();

  if(dialog->result() == 1)
  {
    this->startTime = line_startTime->text().toInt();
    this->endTime = line_endTime->text().toInt();
    this->port = line_port->text().toInt();

    if(this->appsServer != "" && this->appsClient != "" && this->startTime != (size_t) -1 && this->startTime != (size_t) -1 && this->port != (size_t) -1)
    {
      if((this->startTime < this->endTime))
      {
        this->mw->ValidApps();
        this->appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Start time can't be greather than end time.");
        this->ShowGuiTcp();
      }
    }
    else
    {
      if(this->appsServer == "" || this->appsClient == "")
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Sorry, you must choose all machines.");
        this->ShowGuiTcp();
      }
      else
      {
        if(this->startTime == (size_t) -1 || this->endTime == (size_t) -1)
        {
          QMessageBox::about(this, "Tcp Large Transfer", "Sorry, start time and end time can't be null.");
          this->ShowGuiTcp();
        }
        else
        {
          if(this->port == (size_t) -1)
          {
            QMessageBox::about(this, "Tcp Large Transfer", "Sorry, port field can't be null.");
            this->ShowGuiTcp();
          }
        }
      }
    }
  }
}

