#include <QtGui>
#include <iostream>
#include "DragWidget.h"

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
std::cout << "Enter CreateObject" << std::endl;
	QLabel *tlabel = new QLabel(this);
	if(type.compare("Pc") == 0)
	{
    tlabel->setPixmap(QPixmap(":/Ico/PC.png"));
  } 
  else if(type.compare("Emu") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/PC-Emu.png"));
  } 
  else if(type.compare("Tap") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/PC-Tap.png"));
  } 
  else if(type.compare("Ap") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/AP-Wifi.png"));
  } 
  else if(type.compare("Station") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/StationWifi.png"));
  } 
  else if(type.compare("Hub") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/Hub.png"));
  } 
  else if(type.compare("Switch") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/Switch.png"));
  } 
  else if(type.compare("Router") == 0)
  {
    tlabel->setPixmap(QPixmap(":/Ico/Router.png"));
  }
    
  tlabel->move(10, 10);
  tlabel->show();
  tlabel->setAttribute(Qt::WA_DeleteOnClose);
  
  slabel trans;
  trans.label = tlabel;
  trans.name = _name;
  
  this->listDrag.push_back(trans);
std::cout << "Out CreateObject" << std::endl;
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
std::cout << "Enter dragEnterEvent" << std::endl;
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
std::cout << "Out dragEnterEvent" << std::endl;
}

void DragWidget::dropEvent(QDropEvent *event)
{
std::cout << "Enter dropEvent" << std::endl;
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
  {
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    QPixmap pixmap;
    QPoint offset;
    dataStream >> pixmap >> offset;
   
    QLabel *label = new QLabel(this);
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
std::cout << "Out dropEvent" << std::endl;
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
std::cout << "Enter mousePressEvent" << std::endl;
     QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
     if (!child){
         return;
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
         child->close();
     else {
         child->show();
         child->setPixmap(pixmap);
     }
std::cout << "Out mousePressEvent" << std::endl;
}

