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

  this->SetTraceLink(false);

  this->SetLinkBegin("");
  this->SetLinkEnd("");
  this->SetLinkType("");

  this->SetAppsEnable(false);
  this->SetAppsPing(false);
  this->SetAppsUdpEcho(false);
  this->SetAppsTcp(false);
  this->SetAppsServer("");
  this->SetAppsClient("");
  this->SetStartTime(-1);
  this->SetEndTime(-1);
  this->SetPort(-1);
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

  this->SetTimer(new QTimer());
  this->GetTimer()->start(100);
  connect(this->GetTimer(), SIGNAL(timeout()), this, SLOT(update()));

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
    DragObject *child = static_cast<DragObject*>(childAt( this->GetLastPosition() ));
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
    this->GetMainWindow()->GetDelQAction()->setDisabled(true);
    return;
  }
  if(child->GetName() == "deleted")
  {
    /* the child has been deleted ... */
    return;
  }
  this->GetMainWindow()->GetDelQAction()->setDisabled(false);

  this->SetLastPosition(event->pos());

  /* trace link ... */
  if(this->GetTraceLink())
  {
    /* update if we drag an existant object. */

    /*il faut utiliser les noms des objects et non pas les positions ... les positions chanGetGenerator()t quand on drag et du coup après ont peut
      plus cast pour recup le child 
      ....*/

    /* set the attribute. */
    if(this->GetLinkBegin() == "")
    {
      /* begin is not used. */
      this->SetLinkBegin(child->GetName());
    }
    else if(this->GetLinkEnd() == "")
    {
      /* we got the last equipement. */
      DragObject *child2 = this->GetChildFromName(this->GetLinkBegin());
      if(child2)
      {
        if( child->GetName() != child2->GetName())
        {
          this->SetLinkEnd(child->GetName());
          DragLines lig;
          lig.SetFirst(this->GetLinkBegin());
          lig.SetSecond(this->GetLinkEnd());
          lig.SetLinkType(this->GetLinkType());
          this->AddDrawLines(lig);

          this->GetMainWindow()->ValidLink();
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
  if(this->GetAppsEnable())
  {
    if(this->GetAppsServer() == "")
    {
      this->SetAppsServer(child->GetName());
    }
    else
    {
      if(this->GetAppsClient() == "" && child->GetName() != this->GetAppsServer())
      {
        this->SetAppsClient(child->GetName());
      }
    }
  }

  if(this->GetAppsPing())
  {
    ShowGuiPing();
  }

  if(this->GetAppsUdpEcho())
  {
    ShowGuiUdpEcho();
  }

  if(this->GetAppsTcp())
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
  DragObject *child = static_cast<DragObject*>(childAt(this->GetLastPosition()));
  if (!child)
  {
    this->GetMainWindow()->GetDelQAction()->setDisabled(true);
    return;
  }

  /* Generator part */
  /* delete equipement. */
  try
  {
    this->GetMainWindow()->GetGenerator()->RemoveNode(child->GetName());
  }
  catch(const std::exception)
  {}

  /* delete link. */
  /* Attention, if you delete a Link wich need a Node, you must delete it ! */
  try
  {
    this->GetMainWindow()->GetGenerator()->RemoveLink(child->GetName());
  }
  catch(const std::exception)
  {}

  /* delete connections */
  std::vector<std::string> objDelLink;
  for(size_t i = 0; i < (size_t) this->GetMainWindow()->GetGenerator()->GetNLinks(); i++)
  {
    std::vector<std::string> nodes = this->GetMainWindow()->GetGenerator()->GetLink(i)->GetInstalledNodes();
    for(size_t j = 0; j < (size_t) nodes.size(); j++)
    {
      /* if the child to be deleted is connected ... we must remove it. */
      if(child->GetName() == nodes.at(j))
      {
        objDelLink.push_back(this->GetMainWindow()->GetGenerator()->GetLink(i)->GetLinkName());
        try
        {
          this->GetMainWindow()->GetGenerator()->GetLink(i)->removeInstalledNodes(j);
        }
        catch(const std::out_of_range &e)
        {
          this->GetMainWindow()->GetDelQAction()->setDisabled(true);
        }
      }
    }
  }

  /* delete hide create hub for until two Pc for example. */
  bool isHide = true;
  for(size_t i = 0; i < (size_t) objDelLink.size(); i++)
  {
    for(size_t j = 0; j < (size_t) this->GetMainWindow()->GetGenerator()->GetNLinks(); j++)
    {
      if( objDelLink.at(i) == this->GetMainWindow()->GetGenerator()->GetLink(j)->GetLinkName() )
      {
        if(this->GetMainWindow()->GetGenerator()->GetLink(j)->GetInstalledNodes().size() <= 1)
        {
          // the link where the deleted object 
          // check if the link is hide. 
          isHide = true;
          for(size_t k = 0; k < (size_t) this->children().size(); k++)
          {
            if(dynamic_cast<DragObject*>((this->children().at(k))))
            {
              if( dynamic_cast<DragObject*>((this->children().at(k)))->GetName() == this->GetMainWindow()->GetGenerator()->GetLink(j)->GetLinkName())
              {
                isHide = false;
              }
            }
          }
          if(isHide)
          {
            this->GetMainWindow()->GetGenerator()->RemoveLink(this->GetMainWindow()->GetGenerator()->GetLink(j)->GetLinkName());
          }
        }
      }
    }
  }

  /* remove from link part ... */
  if(child->GetName() == this->GetChildFromName(this->GetLinkBegin())->GetName())
  {
    this->SetLinkBegin("");
  }
  if(child->GetName() == this->GetChildFromName(this->GetLinkEnd())->GetName())
  {
    this->SetLinkEnd("");
  }
  for(size_t i = 0; i < (size_t) this->GetDrawLines().size(); i++)
  {
    if(child->GetName() == this->GetChildFromName(this->GetNDrawLines(i).GetFirst())->GetName() || child->GetName() == this->GetChildFromName(this->GetNDrawLines(i).GetSecond())->GetName())
    {
      try
      {
        this->EraseDrawLines(i);
      }
      catch(const std::out_of_range &e)
      {
        this->GetMainWindow()->GetDelQAction()->setDisabled(true);
      }
    }
  }

  /* remove application. */
  std::string sender("");
  std::string receiver("");
  for(size_t i = 0; i < (size_t) this->GetMainWindow()->GetGenerator()->GetNApplications(); i++)
  {
    if((child->GetName()).find("nodesGroup_") == 0)
    {
      sender = this->GetMainWindow()->GetGenerator()->GetApplication(i)->GetSenderNode();
      receiver = this->GetMainWindow()->GetGenerator()->GetApplication(i)->GetReceiverNode();

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
      sender = this->GetMainWindow()->GetGenerator()->GetApplication(i)->GetSenderNode();
      receiver = this->GetMainWindow()->GetGenerator()->GetApplication(i)->GetReceiverNode(); 
    }

    if(child->GetName() == sender ||
        child->GetName() == receiver )
    {
      this->GetMainWindow()->GetGenerator()->RemoveApplication(this->GetMainWindow()->GetGenerator()->GetApplication(i)->GetAppName());
    }
  }

  /* Gui part */
  child->clear();
  child->Destroy();

  this->GetMainWindow()->GetDelQAction()->setDisabled(true);
}

std::vector<std::string> DragWidget::GetLastSelected()
{
  std::vector<std::string> res;
  DragObject *child = this->GetChildFromName(this->GetLinkBegin());
  DragObject *child2 = this->GetChildFromName(this->GetLinkEnd());
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

  res.push_back(this->GetLinkType());

  return res;
}

void DragWidget::DrawLine()
{
  update();
}

void DragWidget::ResetSelected()
{
  this->SetLinkBegin("");
  this->SetLinkEnd("");
  this->SetLinkType("");
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


  for(size_t i = 0; i < (size_t) this->GetDrawLines().size(); i++)
  {
    if(this->GetChildFromName(this->GetNDrawLines(i).GetFirst())->GetName() != "" && this->GetChildFromName(this->GetNDrawLines(i).GetSecond())->GetName() != "")
    {
      std::string type = this->GetNDrawLines(i).GetLinkType();

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
      DragObject *begin = this->GetChildFromName(this->GetNDrawLines(i).GetFirst());
      DragObject *end = this->GetChildFromName(this->GetNDrawLines(i).GetSecond());
      paint.drawLine((begin->pos().x() + (begin->width() / 2)), (begin->pos().y() + (begin->height() / 2)),
                     (end->pos().x() + (end->width() / 2)), (end->pos().y() + (end->height() / 2)));
    }
  }
  if(this->GetTraceLink())
  {

    if(this->GetLinkBegin() != "" && this->GetLinkEnd() == "")
    {
      if(this->GetLinkType() == "WiredLink")
      {
        paint.setPen(pen);
      }
      else if(this->GetLinkType() == "WifiLink")
      {
        paint.setPen(point);
      }
      else if(this->GetLinkType() == "P2pLink")
      {
        paint.setPen(p2p);
      }
      paint.drawLine((this->GetChildFromName(this->GetLinkBegin()))->pos().x() + ((this->GetChildFromName(this->GetLinkBegin()))->width() / 2),
          (this->GetChildFromName(this->GetLinkBegin()))->pos().y() + ((this->GetChildFromName(this->GetLinkBegin()))->height() / 2),
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
  this->SetAppsEnable(false);

  this->SetDialog(new QDialog(this));
  this->GetDialog()->setWindowTitle("Ping");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(this->GetDialog());
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);//QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), this->GetDialog(), SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this->GetDialog(), SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->GetAppsServer() != "")
  {
    label_machineLeft = "Sender : " + this->GetAppsServer();
  }
  else
  {
    label_machineLeft = "Sender : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), this->GetDialog());
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", this->GetDialog());
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->GetAppsClient() != "")
  {
    label_machineRight = "Target : " + this->GetAppsClient();
  }
  else
  {
    label_machineRight = "Target : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), this->GetDialog());
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", this->GetDialog());
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start time (s):", this->GetDialog());
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(this->GetDialog());
  if(this->GetStartTime() != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->GetStartTime()).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End time (s):", this->GetDialog());
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(this->GetDialog());
  if(this->GetEndTime() != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->GetEndTime()).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", this->GetDialog());
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  this->GetDialog()->setLayout(layout);
  this->GetDialog()->exec();

  if(this->GetDialog()->result() == 1)
  {
    this->SetStartTime(line_m_startTime->text().toInt());
    this->SetEndTime(line_m_endTime->text().toInt());

    if(this->GetAppsServer() != "" && this->GetAppsClient() != "" && this->GetStartTime() != (size_t) - 1 && this->GetStartTime() != (size_t) - 1)
    {
      if((this->GetStartTime() < this->GetEndTime()))
      {
        this->GetMainWindow()->ValidApps();
        this->SetAppsPing(false);
      }
      else
      {
        QMessageBox::about(this, "Ping", "Start time can't be greather than end time.");
        this->ShowGuiPing();
      }
    }
    else
    {
      if(this->GetAppsServer() == "" || this->GetAppsClient() == "")
      {
        QMessageBox::about(this, "ping", "Sorry, you must choose all machines.");
        this->ShowGuiPing();
      }
      else
      {
        if(this->GetStartTime() == (size_t) - 1 || this->GetEndTime() == (size_t) - 1)
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
  this->SetAppsEnable(true);
  this->GetDialog()->hide();
  this->SetAppsServer("");
}

void DragWidget::ChooseClient()
{
  this->SetAppsEnable(true); 
  this->GetDialog()->hide();
  this->SetAppsClient("");
}

void DragWidget::Cancel()
{
  this->GetDialog()->hide();
  this->SetAppsServer("");
  this->SetAppsClient("");

  this->SetAppsEnable(false);
  this->SetAppsPing(false);
  this->SetAppsUdpEcho(false);
  this->SetAppsTcp(false);
}

void DragWidget::ShowGuiUdpEcho()
{
  this->SetAppsEnable(false);

  this->SetDialog(new QDialog(this));
  this->GetDialog()->setWindowTitle("Udp Echo");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(this->GetDialog());
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), this->GetDialog(), SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this->GetDialog(), SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->GetAppsServer() != "")
  {
    label_machineLeft = "Server : " + this->GetAppsServer();
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), this->GetDialog());
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", this->GetDialog());
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->GetAppsClient() != "")
  {
    label_machineRight = "Client : " + this->GetAppsClient();
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), this->GetDialog());
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", this->GetDialog());
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start time (s):", this->GetDialog());
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(this->GetDialog());
  if(this->GetStartTime() != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->GetStartTime()).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End time (s):", this->GetDialog());
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(this->GetDialog());
  if(this->GetEndTime() != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->GetEndTime()).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  QLabel *lab_m_port = new QLabel("Port :", this->GetDialog());
  layout->addWidget(lab_m_port, 7, 0);

  QLineEdit *line_m_port = new QLineEdit(this->GetDialog());
  if(this->GetPort() != (size_t) - 1)
  {
    line_m_port->insert(utils::integerToString(this->GetPort()).c_str());
  }
  layout->addWidget(line_m_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", this->GetDialog());
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  this->GetDialog()->setLayout(layout);
  this->GetDialog()->exec();

  if(this->GetDialog()->result() == 1)
  {
    this->SetStartTime(line_m_startTime->text().toInt());
    this->SetEndTime(line_m_endTime->text().toInt());
    this->SetPort(line_m_port->text().toInt());

    if(this->GetAppsServer() != "" && this->GetAppsClient() != "" && this->GetStartTime() != (size_t) - 1 && this->GetStartTime() != (size_t) - 1 && this->GetPort() != (size_t) - 1)
    {
      if((this->GetStartTime() < this->GetEndTime()))
      {
        this->GetMainWindow()->ValidApps();
        this->SetAppsPing(false);
      }
      else
      {
        QMessageBox::about(this, "Udp Echo", "Start time can't be greather than end time.");
        this->ShowGuiUdpEcho();
      }
    }
    else
    {
      if(this->GetAppsServer() == "" || this->GetAppsClient() == "")
      {
        QMessageBox::about(this, "Udp Echo", "Sorry, you must choose all machines.");
        this->ShowGuiUdpEcho();
      }
      else
      {
        if(this->GetStartTime() == (size_t) - 1 || this->GetEndTime() == (size_t) - 1)
        {
          QMessageBox::about(this, "Udp Echo", "Sorry, start time and end time can't be null.");
          this->ShowGuiUdpEcho();
        }
        else
        {
          if(this->GetPort() == (size_t) - 1)
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
  this->SetAppsEnable(false);

  this->SetDialog(new QDialog(this));
  this->GetDialog()->setWindowTitle("Tcp Large Transfer");

  QGridLayout *layout = new QGridLayout;

  QDialogButtonBox *buttonBox = new QDialogButtonBox(this->GetDialog());
  buttonBox->setStandardButtons(QDialogButtonBox::Ok);

  connect(buttonBox, SIGNAL(accepted()), this->GetDialog(), SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this->GetDialog(), SLOT(reject()));

  /* MACHINE LEFT */
  std::string label_machineLeft("");
  if(this->GetAppsServer() != "")
  {
    label_machineLeft = "Server : " + this->GetAppsServer();
  }
  else
  {
    label_machineLeft = "Server : ___________";
  }

  QLabel *machineLeft = new QLabel(QString(label_machineLeft.c_str()), this->GetDialog());
  layout->addWidget(machineLeft, 2, 0);

  QPushButton *button_machineLeft = new QPushButton("Choose", this->GetDialog());
  connect(button_machineLeft, SIGNAL( clicked() ), this, SLOT( ChooseServer() ) );

  layout->addWidget(button_machineLeft, 2, 1);

  /* MACHINE RIGHT */
  std::string label_machineRight("");
  if(this->GetAppsClient() != "")
  {
    label_machineRight = "Client : " + this->GetAppsClient();
  }
  else
  {
    label_machineRight = "Client : ___________";
  }

  QLabel *machineRight = new QLabel(QString(label_machineRight.c_str()), this->GetDialog());
  layout->addWidget(machineRight, 3, 0);

  QPushButton *button_machineRight = new QPushButton("Choose", this->GetDialog());
  connect(button_machineRight, SIGNAL( clicked() ), this, SLOT( ChooseClient() ) );
  layout->addWidget(button_machineRight, 3, 1);

  /* PARAMS. */
  QLabel *lab_m_startTime = new QLabel("Start time (s):", this->GetDialog());
  layout->addWidget(lab_m_startTime, 5, 0);

  QLineEdit *line_m_startTime = new QLineEdit(this->GetDialog());
  if(this->GetStartTime() != (size_t) - 1)
  {
    line_m_startTime->insert(utils::integerToString(this->GetStartTime()).c_str());
  }
  layout->addWidget(line_m_startTime, 5, 1);

  QLabel *lab_m_endTime = new QLabel("End time (s):", this->GetDialog());
  layout->addWidget(lab_m_endTime, 6, 0);

  QLineEdit *line_m_endTime = new QLineEdit(this->GetDialog());
  if(this->GetEndTime() != (size_t) - 1)
  {
    line_m_endTime->insert(utils::integerToString(this->GetEndTime()).c_str());
  }
  layout->addWidget(line_m_endTime, 6, 1);

  QLabel *lab_m_port = new QLabel("Port :", this->GetDialog());
  layout->addWidget(lab_m_port, 7, 0);

  QLineEdit *line_m_port = new QLineEdit(this->GetDialog());
  if(this->GetPort() != (size_t) - 1)
  {
    line_m_port->insert(utils::integerToString(this->GetPort()).c_str());
  }
  layout->addWidget(line_m_port, 7, 1);

  /* add OK, CANCEL button */
  QPushButton *cancel = new QPushButton("Cancel", this->GetDialog());
  connect(cancel, SIGNAL( clicked() ), this, SLOT( Cancel() ) );
  layout->addWidget(cancel, 8, 3);
  layout->addWidget(buttonBox, 8, 4);

  this->GetDialog()->setLayout(layout);
  this->GetDialog()->exec();

  if(this->GetDialog()->result() == 1)
  {
    this->SetStartTime(line_m_startTime->text().toInt());
    this->SetEndTime(line_m_endTime->text().toInt());
    this->SetPort(line_m_port->text().toInt());

    if(this->GetAppsServer() != "" && this->GetAppsClient() != "" && this->GetStartTime() != (size_t) - 1 && this->GetStartTime() != (size_t) - 1 && this->GetPort() != (size_t) - 1)
    {
      if((this->GetStartTime() < this->GetEndTime()))
      {
        this->GetMainWindow()->ValidApps();
        this->SetAppsPing(false);
      }
      else
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Start time can't be greather than end time.");
        this->ShowGuiTcp();
      }
    }
    else
    {
      if(this->GetAppsServer() == "" || this->GetAppsClient() == "")
      {
        QMessageBox::about(this, "Tcp Large Transfer", "Sorry, you must choose all machines.");
        this->ShowGuiTcp();
      }
      else
      {
        if(this->GetStartTime() == (size_t) - 1 || this->GetEndTime() == (size_t) - 1)
        {
          QMessageBox::about(this, "Tcp Large Transfer", "Sorry, start time and end time can't be null.");
          this->ShowGuiTcp();
        }
        else
        {
          if(this->GetPort() == (size_t) - 1)
          {
            QMessageBox::about(this, "Tcp Large Transfer", "Sorry, port field can't be null.");
            this->ShowGuiTcp();
          }
        }
      }
    }
  }
}

void DragWidget::SetLinkType(const std::string& linkType)
{
  this->m_linkType = linkType;
}

std::string DragWidget::GetLinkType() const
{
  return this->m_linkType;
}

void DragWidget::SetLastPosition(const QPoint &pos)
{
  this->m_lastPosition = pos;
}

QPoint DragWidget::GetLastPosition()
{
  return this->m_lastPosition;
}

void DragWidget::SetLinkBegin(const std::string &linkBegin)
{
  this->m_linkBegin = linkBegin;
}

std::string DragWidget::GetLinkBegin()
{
  return this->m_linkBegin;
}

MainWindow* DragWidget::GetMainWindow()
{
  return m_mw;
}

void DragWidget::SetTraceLink(const bool &state)
{
  this->m_traceLink = state;
}

bool DragWidget::GetTraceLink()
{
  return this->m_traceLink;
}

void DragWidget::SetLinkEnd(const std::string &link)
{
  this->m_linkEnd = link;
}

std::string DragWidget::GetLinkEnd()
{
  return this->m_linkEnd;
}

void DragWidget::SetDragLines(const DragLines &lines)
{
  this->m_lines = lines;
}

DragLines DragWidget::GetDragLines()
{
  return this->m_lines;
}

void DragWidget::AddDrawLines(const DragLines &dl)
{
  this->m_drawLines.push_back(dl);
}

DragLines DragWidget::GetNDrawLines(const size_t &index)
{
  return this->m_drawLines.at(index);
}

std::vector<DragLines> DragWidget::GetDrawLines()
{
  return this->m_drawLines;
}

void DragWidget::EraseDrawLines(const size_t &index)
{
  this->m_drawLines.erase(this->m_drawLines.begin() + index);
}

void DragWidget::SetTimer(QTimer *timer)
{
  this->m_timer = timer;
}

QTimer* DragWidget::GetTimer()
{
  return this->m_timer;
}
  
void DragWidget::SetAppsServer(const std::string &appsServ)
{
  this->m_appsServer = appsServ;
}

std::string DragWidget::GetAppsServer()
{
  return this->m_appsServer;
}

void DragWidget::SetAppsClient(const std::string &appsCli)
{
  this->m_appsClient = appsCli;
}

std::string DragWidget::GetAppsClient()
{
  return this->m_appsClient;
}

void DragWidget::SetAppsPing(const bool &appsPing)
{
  this->m_appsPing = appsPing;
}

bool DragWidget::GetAppsPing()
{
  return this->m_appsPing;
}

void DragWidget::SetAppsUdpEcho(const bool &appsUdp)
{
  this->m_appsUdpEcho = appsUdp;
}

bool DragWidget::GetAppsUdpEcho()
{
  return this->m_appsUdpEcho;
}

void DragWidget::SetAppsTcp(const bool &appsTcp)
{
  this->m_appsTcp = appsTcp;
}

bool DragWidget::GetAppsTcp()
{
  return this->m_appsTcp;
}

void DragWidget::SetStartTime(const size_t &start)
{
  this->m_startTime = start;
}

size_t DragWidget::GetStartTime()
{
  return this->m_startTime;
}

void DragWidget::SetEndTime(const size_t &end)
{
  this->m_endTime = end;
}

size_t DragWidget::GetEndTime()
{
  return this->m_endTime;
}

void DragWidget::SetPort(const size_t &port)
{
  this->m_port = port;
}

size_t DragWidget::GetPort()
{
  return this->m_port;
}

void DragWidget::SetDialog(QDialog *dialog)
{
  this->m_dialog = dialog;
}

QDialog* DragWidget::GetDialog()
{
  return this->m_dialog;
}

void DragWidget::SetAppsEnable(const bool &state)
{
  this->m_appsEnable = state;
}

bool DragWidget::GetAppsEnable()
{
  return this->m_appsEnable;
}

