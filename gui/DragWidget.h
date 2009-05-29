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
* \file DragWidget.h
* \brief The drag n drop zone file.
* \author Pierre Weiss
* \date 2009
*/

#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <vector>
#include <QtGui>

class DragObject;
class MainWindow;
class DragLines;

class QDragEnterEvent;
class QDropEvent;

#include "DragObject.h"
#include "DragLines.h"

/**
 * \ingroup generator
 * \brief The drag ne drop zone.
 *
 * This class create the drag n drop zone.
 */
class DragWidget : public QWidget
{
  public:
    /**
     * \brief constructor
     * \param parent 
     */
    DragWidget(QWidget *parent=0);
    
    /**
     * \brief Destructor
     */
    ~DragWidget();
    
    /**
     * \brief Procedure to create object which are on the tool bar.
     * \param type the type of the object to create.
     * \param name his name.
     */
    void CreateObject(const std::string &type, const std::string &name);
    
    /**
     * \brief Procedure to delete the last selecte elem.
     */
    void deleteSelected();
    
    /**
     * \brief function to return the name of the last selected equipement.
     * \return last selected name.
     */
    std::vector<std::string> getLastSelected();
    
    /**
     * \brief procedure to reset lastSelected.
     */
    void ResetSelected();
    
    /**
     * \brief procedure to draw the link.
     */
    void DrawLine();
    
    /**
     * \brief procedure to draw lines.
     * \param event
     */
    void paintEvent(QPaintEvent *event);
    
    /**
     * \brief attribute to say if we trace link or not
     */
    bool traceLink;
    
    /**
     * \brief procedure to set the mainwindow attribute.
     * \param _mw
     */
    void setMainWindow(MainWindow *_mw);
    
    /**
     * \brief link type.
     */
    std::string linkType;
    
    /**
     * \brief the link end.
     */
    std::string linkEnd;
    
    /**
     * \brief DrawLines class attribute
     */
    DragLines lines;
    
    /**
     * \brief the attribute which containt the attribute name to draw lines.
     */
    std::vector<DragLines> drawLines;
    
  private:
    /**
     * \brief attribute to save the Position from the last object which moved.
     */ 
    QPoint lastPosition;
    
    /**
     * \brief the link begin
     */
    std::string linkBegin;
    
    /**
     * \brief function to get the child object from his name.
     * \param name
     */
    DragObject* getChildFromName(const std::string &name);
    
    /**
     * \brief the main window attribute
     */
    MainWindow *mw;
    
  protected:
    /**
     * \brief function which have been rewritted. see Qt doc.
     */
    void dragEnterEvent(QDragEnterEvent *event);
    
    /**
    * \brief function which have been rewritted. see Qt doc.
    */
    void dropEvent(QDropEvent *event);
     
    /**
    * \brief function which have been rewritted. see Qt doc.
    */
    void mousePressEvent(QMouseEvent *event);
    
    /**
    * \brief function which have been rewritted. see Qt doc.
    */
    void mouseMoveEvent(QMouseEvent *event);
    
};

#endif /* END DRAGWIDGET_H */
