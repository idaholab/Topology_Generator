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
	QLabel *label = new QLabel(this);
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
  
  DragObject *drag = new DragObject();
  drag->label = label;
  drag->name = _name;
  drag->x = 10;
  drag->y = 10;
  
  //~ this->listDrag.push_back(label);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
  {
    if (event->source() == this) 
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
      std::cout << "###################################" << std::endl;
      std::cout << "Position Avant :" << std::endl;
      std::cout << "x :" << event->pos().x() << " - " << event->pos().y() << std::endl;
      std::cout << "###################################" << std::endl;
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
   
    std::cout << "###################################" << std::endl;
    std::cout << "Position Après:" << std::endl;
    std::cout << "x :" << event->pos().x() << " - " << event->pos().y() << std::endl;
    std::cout << "event : " << event << std::endl;
    std::cout << "###################################" << std::endl;
   
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
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
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
}
