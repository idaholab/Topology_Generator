#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <vector>
#include <QtGui>

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QWidget
{
   public:
     DragWidget(QWidget *parent=0);
     void CreateObject(std::string type);
     void deleteLastSelected();
     
   protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dropEvent(QDropEvent *event);
     void mousePressEvent(QMouseEvent *event);
     
   private:
     QLabel *last;
       
};

#endif
