#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <vector>
#include <QtGui>
#include "DragObject.h"

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QWidget
{
  public:
    size_t selectedObject;
    std::vector<DragObject*> listDrag;
    DragWidget(QWidget *parent=0);
    ~DragWidget();
    void CreateObject(const std::string &type, const std::string &name);
     
  protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    
    
};

#endif /* END DRAGWIDGET_H */
