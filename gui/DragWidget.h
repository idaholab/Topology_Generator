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
    struct slabel
    {
      QLabel *label;
      std::string name;
    };
    std::vector<slabel> listDrag;
    DragWidget(QWidget *parent=0);
    ~DragWidget();
    void CreateObject(const std::string &type, const std::string &name);
     
  protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
     
  private:
     //QLabel *last;
       
};

#endif /* END DRAGWIDGET_H */
