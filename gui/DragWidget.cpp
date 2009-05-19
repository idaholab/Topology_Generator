#include <QtGui>
#include <iostream>
#include "DragWidget.h"

DragWidget::DragWidget(QWidget *parent) : QWidget(parent)
{
     setMinimumSize(400, 400);
     setAcceptDrops(true);
     last = new QLabel(this);
}

DragWidget::~DragWidget()
{
  delete last;
}

void DragWidget::CreateObject(std::string type)
{
	QLabel *label = new QLabel(this);
	if(type.compare("Pc") == 0)
	{
    label->setPixmap(QPixmap("./gui/Ico/PC.png"));
  } 
  else if(type.compare("Emu") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/PC-Emu.png"));
  } 
  else if(type.compare("Tap") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/PC-Tap.png"));
  } 
  else if(type.compare("Ap") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/AP-Wifi.png"));
  } 
  else if(type.compare("Station") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/StationWifi.png"));
  } 
  else if(type.compare("Hub") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/Hub.png"));
  } 
  else if(type.compare("Switch") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/Switch.png"));
  } 
  else if(type.compare("Router") == 0)
  {
    label->setPixmap(QPixmap("./gui/Ico/Router.png"));
  }
    
    label->move(10, 10);
    label->show();
    label->setAttribute(Qt::WA_DeleteOnClose);  
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
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
}

void DragWidget::dropEvent(QDropEvent *event)
{
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         QPixmap pixmap;
         QPoint offset;
         dataStream >> pixmap >> offset;

         QLabel *newIcon = new QLabel(this);
         newIcon->setPixmap(pixmap);
         newIcon->move(event->pos() - offset);
         newIcon->show();
         newIcon->setAttribute(Qt::WA_DeleteOnClose);
         //set the last object moved.
         last = newIcon;

         if (event->source() == this) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
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

void DragWidget::deleteLastSelected()
{
	if(last != NULL){
		last->clear();
	}
}
