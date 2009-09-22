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

#include <QtGui>
#include <iostream>
#include <stdexcept>

#include "main-window.h"
#include "drag-widget.h"

#include "drag-object.h"
#include "drag-lines.h"

#include "utils.h"

DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
  setMinimumSize(400, 400);
  setAcceptDrops(true);
  setMouseTracking(true);

  this->m_traceLink = false;

  this->m_linkBegin = "";
  this->m_linkEnd = "";
  this->m_linkType = "";

  this->m_appsEnable = false;
  this->m_appsPing = false;
  this->m_appsUdpEcho = false;
  this->m_appsTcp = false;
  this->m_appsServer = "";
  this->m_appsClient = "";
  this->m_startTime = -1;
  this->m_endTime = -1;
  this->m_port = -1;
}

DragWidget::~DragWidget()
{
  delete this->m_timer;
}

void DragWidget::SetMainWindow(MainWindow *mw)
{
  this->m_mw = mw;
}

void DragWidget::CreateObject(const std::string &type, const std::string &name)
{
  DragObject *label = new DragObject(this);
  label->SetName(name);
  label->SetToolTipText(QString(name.c_str()));
  label->setToolTip(QString(name.c_str()));
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

  this->m_timer = new QTimer();
  this->m_timer->start(100);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

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
    DragObject *child = static_cast<DragObject*>(childAt( this->m_lastPosition ));
    DragObject *label = new DragObject(this);
    if(child)
    {
      label->SetName(child->GetName());
      label->SetToolTipText(child->GetToolTipText());
      label->setToolTip(label->GetToolTipText());
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
    this->m_mw->m_delAction->setDisabled(true);
    return;
  }
  if(child->GetName() == "deleted")
  {
    /* the child has been deleted ... */
    return;
  }
  this->m_mw->m_delAction->setDisabled(false);

  this->m_lastPosition = event->pos();

  /* trace link ... */
  if(this->m_traceLink)
  {
    /* update if we drag an existant object. */

    /*il faut utiliser les noms des objects et non pas les positions ... les positions chanm_gent quand on drag et du coup après ont peut
      plus cast pour recup le child 
      ....*/

    /* set the attribute. */
    if(this->m_linkBegin == "")
    {
      /* begin is not used. */
      m_linkBegin = child->GetName();
    }
    else if(this->m_linkEnd == "")
    {
      /* we got the last equipement. */
      DragObject *child2 = this->GetChildFromName(this->m_linkBegin);
      if(child2)
      {
        if( child->GetName() != child2->GetName())
        {
          m_linkEnd = child->GetName();
          DragLines lig;
          lig.SetFirst(this->m_linkBegin);
          lig.SetSecond(this->m_linkEnd);
          lig.SetLinkType(this->m_linkType);
          this->m_drawLines.push_back(lig);

          this->m_mw->ValidLink();
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
  if(this->m_appsEnable)
  {
    if(this->m_appsServer == "")
    {
      this->m_appsServer = child->GetName();
    }
    else
    {
      if(this->m_appsClient == "" && child->GetName() != this->m_appsServer)
      {
        this->m_appsClient = child->GetName();
      }
    }
  }

  if(this->m_appsPing)
  {
    ShowGuiPing();
  }

  if(this->m_appsUdpEcho)
  {
    ShowGuiUdpEcho();
  }

  if(this->m_appsTcp)
  {
    ShowGuiTcp();
  }

  //~ this->m_appsEnable = false;
}

void DragWidget::mouseMoveEvent(QMouseEvent * /*event*/)
{
  update();
}

void DragWidget::DeleteSelected()
{
  DragObject *child = static_cast<DragObject*>(childAt(this->m_lastPosition));
  if (!child)
  {
    this->m_mw->m_delAction->setDisabled(true);
    return;
  }

  /* Generator part */
  /* delete equipement. */
  try
  {
    this->m_mw->m_gen->RemoveNode(child->GetName());
  }
  catch(const std::exception)
  {}

  /* delete link. */
  /* Attention, if you delete a Link wich need a Node, you must delete it ! */
  try
  {
    this->m_mw->m_gen->RemoveLink(child->GetName());
  }
  catch(const std::exception)
  {}

  /* delete connections */
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < (size_t) this->m_mw->m_gen->GetNLinks(); i++)
  {
    std::vector<std::string> nodes = this->m_mw->m_gen->GetLink(i)->GetInstalledNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      /* if the child to be deleted is connected ... we must remove it. */
      if(child->GetName() == nodes.at(j))
      {
        objDelLink.push_back(this->m_mw->m_gen->GetLink(i)->GetLinkName());
        try
        {
          this->m_mw->m_gen->GetLink(i)->removeInstalledNodes(j);
        }
        catch(const std::out_of_range &e)
        {
          this->m_mw->m_delAction->setDisabled(true);
        }
      }
    }
  }

  /* delete hide create hub for until two Pc for example. */
  bool isHide = true;
  for(size_t i = 0; i < (size_t) objDelLink.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->m_mw->m_gen->GetNLinks(); j++)
    {
      if( objDelLink.at(i) == this->m_mw->m_gen->GetLink(j)->GetLinkName() )
      {
        if(this->m_mw->m_gen->GetLink(j)->GetInstalledNodes().size() <= 1)
        {
          // the link where the deleted object 
          // check if the link is hide. 
          isHide = true;
          for(size_t k = 0; k < (size_t) this->children().size(); k++)
          {
            if(dynamic_cast<DragObject*>((this->children().at(k))))
            {
              if( dynamic_cast<DragObject*>((this->children().at(k)))->GetName() == this->m_mw->m_gen->GetLink(j)->GetLinkName())
              {
                isHide = false;
              }
            }
          }
          if(isHide)
          {
            this->m_mw->m_gen->RemoveLink(this->m_mw->m_gen->GetLink(j)->GetLinkName());
          }
        }
      }
    }
  }

  /* remove from link part ... */
  if(child->GetName() == this->GetChildFromName(this->m_linkBegin)->GetName())
  {
    this->m_linkBegin = "";
  }
  if(child->GetName() == this->GetChildFromName(this->m_linkEnd)->GetName())
  {
    this->m_linkEnd = "";
  }
  for(size_t i = 0; i < (size_t) this->m_drawLines.size(); i++)
  {
    if(child->GetName() == this->GetChildFromName(this->m_drawLines.at(i).GetFirst())->GetName() || child->GetName() == this->GetChildFromName(this->m_drawLines.at(i).GetSecond())->GetName())
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

  /* remove application. */
  std::string sender("");
  std::string receiver("");
  for(size_t i = 0; i < (size_t) this->m_mw->m_gen->GetNApplications(); i++)
  {
    if((child->GetName()).find("nodesGroup_") == 0)
    {
      sender = this->m_mw->m_gen->GetApplication(i)->GetSenderNode();
      receiver = this->m_mw->m_gen->GetApplication(i)->GetReceiverNode();

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
      sender = this->m_mw->m_gen->GetApplication(i)->GetSenderNode();
      receiver = this->m_mw->m_gen->GetApplication(i)->GetReceiverNode(); 
    }

    if(child->GetName() == sender ||
        child->GetName() == receiver )
    {
      this->m_mw->m_gen->RemoveApplication(this->m_mw->m_gen->GetApplication(i)->GetAppName());
    }
  }

  /* Gui part */
  child->clear();
  child->Destroy();

  this->m_mw->m_delAction->setDisabled(true);
}

std::vector<std::string> DragWidget::GetLastSelected()
{
  std::vector<std::string> res;
  DragObject *child = this->GetChildFromName(this->m_linkBegin);
  DragObject *child2 = this->GetChildFromName(this->m_linkEnd);
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

  res.push_back(this->m_linkType);

  return res;
}

void DragWidget::DrawLine()
{
  update();
}

void DragWidget::ResetSelected()
{
  this->m_linkBegin = "";
  this->m_linkEnd = "";
  this->m_linkType = "";
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


  for(size_t i = 0; i < (size_t) this->m_drawLines.size(); i++)
  {
    if(this->GetChildFromName(this->m_drawLines.at(i).GetFirst())->GetName() != "" && this->GetChildFromName(this->m_drawLines.at(i).GetSecond())->GetName() != "")
    {
      std::string type = this->m_drawLines.at(i).GetLinkType();

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
  if(this->m_traceLink)
  {

    if(this->m_linkBegin != "" && this->m_linkEnd == "")
    {
      if(this->m_linkType == "WiredLink")
      {
        paint.setPen(pen);
      }
      else if(this->m_linkType == "WifiLink")
      {
        paint.setPen(point);
      }
      else if(this->m_linkType == "P2pLink")
      {
        paint.setPen(p2p);
      }
      paint.drawLine((this->GetChildFromName(this->m_linkBegin))->pos().x() + ((this->GetChildFromName(this->m_linkBegin))->width() / 2),
          (this->GetChildFromName(this->m_linkBegin))->pos().y() + ((this->GetChildFromName(this->m_linkBegin))->height() / 2),
          mapFromGlobal(QCursor::pos()).x(),  mapFromGlobal(QCursor::pos()).y());
    }
  }
  paint.setPen(pen);
}

DragObject* DragWidget::GetChildFromName(const std::string &name)
{
  for(size_t i = 0; i < (size_t) this->children().size(); i++)
  {
    DragObject *child = dynamic_cast<DragObject*>(this->children().at(i));
    if(child)
    {
      if( child->GetName() == name)
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
  this->m_appsEnable = false;

  m_dialog = new QDialog(this);
  m_dialog->setWindowTitle("Ping");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(m_dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);//QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), m_dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), m_dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->m_appsServer != "")
  {
    label_machineLeft = "Sender : " + this->m_appsServer;
  }
  else
  {
    label_machineLeft = "Sender : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), m_dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", m_dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->m_appsClient != "")
  {
    label_machineRight = "Target : " + this->m_appsClient;
  }
  else
  {
    label_machineRight = "Target : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), m_dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", m_dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start time (s):", m_dialog);
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(m_dialog);
  if(this->m_startTime != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->m_startTime).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End time (s):", m_dialog);
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(m_dialog);
  if(this->m_endTime != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->m_endTime).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", m_dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  m_dialog->setLayout(layout);
  m_dialog->exec();

  if(m_dialog->result() == 1)
  {
    this->m_startTime = line_m_startTime->text().toInt();
    this->m_endTime = line_m_endTime->text().toInt();

    if(this->m_appsServer != "" && this->m_appsClient != "" && this->m_startTime != (size_t) - 1 && this->m_startTime != (size_t) - 1)
    {
      if((this->m_startTime < this->m_endTime))
      {
        this->m_mw->ValidApps();
        this->m_appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Ping", "Start time can't be greather than end time.");
        this->ShowGuiPing();
      }
    }
    else
    {
      if(this->m_appsServer == "" || this->m_appsClient == "")
      {
        QMessageBox::about(this, "ping", "Sorry, you must choose all machines.");
        this->ShowGuiPing();
      }
      else
      {
        if(this->m_startTime == (size_t) - 1 || this->m_endTime == (size_t) - 1)
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
  this->m_appsEnable = true;
  m_dialog->hide();
  this->m_appsServer = "";
}

void DragWidget::ChooseClient()
{
  this->m_appsEnable = true; 
  m_dialog->hide();
  this->m_appsClient = "";
}

void DragWidget::Cancel()
{
  m_dialog->hide();
  this->m_appsServer = "";
  this->m_appsClient = "";

  this->m_appsEnable = false;
  this->m_appsPing = false;
  this->m_appsUdpEcho = false;
  this->m_appsTcp = false;
}

void DragWidget::ShowGuiUdpEcho()
{
  this->m_appsEnable = false;

  m_dialog = new QDialog(this);
  m_dialog->setWindowTitle("Udp Echo");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(m_dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), m_dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), m_dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->m_appsServer != "")
  {
    label_machineLeft = "Server : " + this->m_appsServer;
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), m_dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", m_dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->m_appsClient != "")
  {
    label_machineRight = "Client : " + this->m_appsClient;
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), m_dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", m_dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start time (s):", m_dialog);
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(m_dialog);
  if(this->m_startTime != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->m_startTime).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End time (s):", m_dialog);
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(m_dialog);
  if(this->m_endTime != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->m_endTime).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  QLabel *lab_m_port = new QLabel("Port :", m_dialog);
  layout->addWidget(lab_m_port, 7, 0);

  QLineEdit *line_m_port = new QLineEdit(m_dialog);
  if(this->m_port != (size_t) - 1)
  {
    line_m_port->insert(utils::integerToString(this->m_port).c_str());
  }
  layout->addWidget(line_m_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", m_dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  m_dialog->setLayout(layout);
  m_dialog->exec();

  if(m_dialog->result() == 1)
  {
    this->m_startTime = line_m_startTime->text().toInt();
    this->m_endTime = line_m_endTime->text().toInt();
    this->m_port = line_m_port->text().toInt();

    if(this->m_appsServer != "" && this->m_appsClient != "" && this->m_startTime != (size_t) - 1 && this->m_startTime != (size_t) - 1 && this->m_port != (size_t) - 1)
    {
      if((this->m_startTime < this->m_endTime))
      {
        this->m_mw->ValidApps();
        this->m_appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Udp Echo", "Start m_time can't be greather than end m_time.");
        this->ShowGuiUdpEcho();
      }
    }
    else
    {
      if(this->m_appsServer == "" || this->m_appsClient == "")
      {
        QMessageBox::about(this, "Udp Echo", "Sorry, you must choose all machines.");
        this->ShowGuiUdpEcho();
      }
      else
      {
        if(this->m_startTime == (size_t) - 1 || this->m_endTime == (size_t) - 1)
        {
          QMessageBox::about(this, "Udp Echo", "Sorry, start m_time and end m_time can't be null.");
          this->ShowGuiUdpEcho();
        }
        else
        {
          if(this->m_port == (size_t) - 1)
          {
            QMessageBox::about(this, "Udp Echo", "Sorry, m_port field can't be null.");
            this->ShowGuiUdpEcho();
          }
        }
      }
    }
  }

}

void DragWidget::ShowGuiTcp()
{
  this->m_appsEnable = false;

  m_dialog = new QDialog(this);
  m_dialog->setWindowTitle("Tcp Large Transfer");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(m_dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), m_dialog, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), m_dialog, SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->m_appsServer != "")
  {
    label_machineLeft = "Server : " + this->m_appsServer;
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), m_dialog);
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", m_dialog);
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->m_appsClient != "")
  {
    label_machineRight = "Client : " + this->m_appsClient;
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), m_dialog);
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", m_dialog);
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start m_time (s):", m_dialog);
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(m_dialog);
  if(this->m_startTime != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->m_startTime).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End m_time (s):", m_dialog);
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(m_dialog);
  if(this->m_endTime != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->m_endTime).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  QLabel *lab_m_port = new QLabel("Port :", m_dialog);
  layout->addWidget(lab_m_port, 7, 0);

  QLineEdit *line_m_port = new QLineEdit(m_dialog);
  if(this->m_port != (size_t) - 1)
  {
    line_m_port->insert(utils::integerToString(this->m_port).c_str());
  }
  layout->addWidget(line_m_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", m_dialog);
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  m_dialog->setLayout(layout);
  m_dialog->exec();

  if(m_dialog->result() == 1)
  {
    this->m_startTime = line_m_startTime->text().toInt();
    this->m_endTime = line_m_endTime->text().toInt();
    this->m_port = line_m_port->text().toInt();

    if(this->m_appsServer != "" && this->m_appsClient != "" && this->m_startTime != (size_t) - 1 && this->m_startTime != (size_t) - 1 && this->m_port != (size_t) - 1)
    {
      if((this->m_startTime < this->m_endTime))
      {
        this->m_mw->ValidApps();
        this->m_appsPing = false;
      }
      else
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Start m_time can't be greather than end m_time.");
        this->ShowGuiTcp();
      }
    }
    else
    {
      if(this->m_appsServer == "" || this->m_appsClient == "")
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Sorry, you must choose all machines.");
        this->ShowGuiTcp();
      }
      else
      {
        if(this->m_startTime == (size_t) - 1 || this->m_endTime == (size_t) - 1)
        {
          QMessageBox::about(this, "Tcp Large Transfer", "Sorry, start m_time and end m_time can't be null.");
          this->ShowGuiTcp();
        }
        else
        {
          if(this->m_port == (size_t) - 1)
          {
            QMessageBox::about(this, "Tcp Large Transfer", "Sorry, m_port field can't be null.");
            this->ShowGuiTcp();
          }
        }
      }
    }
  }
}

