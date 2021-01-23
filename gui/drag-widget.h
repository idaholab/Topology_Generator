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
 * \file drag-widget.h
 * \brief The drag n drop zone file.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef DRAG_WIDGET_H
#define DRAG_WIDGET_H

#include <QFrame>
#include <vector>
#include <QtWidgets>

class DragObject;
class MainWindow;
class DragLines;

class QDragEnterEvent;
class QDropEvent;


#include "drag-object.h"
#include "drag-lines.h"

/**
 * \ingroup generator
 * \brief The drag ne drop zone.
 *
 * This class create the drag n drop zone.
 */
class DragWidget : public QWidget
{
  Q_OBJECT

  public:
    /**
     * \brief Constructor.
     * \param parent 
     */
    DragWidget(QWidget *parent=0);

    /**
     * \brief Destructor.
     */
    ~DragWidget();

    /**
     * \brief Create object which are on the tool bar.
     * \param type the type of the object to create
     * \param name his name
     * \param x position
     * \param y position
     */
    void CreateObject(const std::string &type, const std::string &name, size_t x = 10, size_t y = 10);

    /**
     * \brief Set the MainWindow.
     * \param _mw
     */
    void SetMainWindow(MainWindow *_mw);

    /**
     * \brief Reset lastSelected equipment.
     */
    void ResetSelected();

    /**
     * \brief Set trace link.
     * \param state new state
     */
    void SetTraceNetworkHardware(const bool &state);
    
    /**
     * \brief Get trace link.
     * \return trace link
     */
    bool GetTraceNetworkHardware();

    /**
     * \brief Set link begin.
     * \param linkBegin new link begin
     */
    void SetNetworkHardwareBegin(const std::string &linkBegin);
    
    /**
     * \brief Get link begin.
     * \return link begin
     */
    std::string GetNetworkHardwareBegin();

    /**
     * \brief Set link end.
     * \param link new link end
     */
    void SetNetworkHardwareEnd(const std::string &link);
    
    /**
     * \brief Get link end.
     * \return link end
     */
    std::string GetNetworkHardwareEnd();

    /**
     * \brief Set link type.
     * \param linkType link type
     */
    void SetNetworkHardwareType(const std::string& linkType);

    /**
     * \brief Get link type.
     * \return link type
     */
    std::string GetNetworkHardwareType() const;

    /**
     * \brief Get the child object from his name.
     * \param name name of the object to find
     */
    DragObject* GetChildFromName(const std::string &name);

    /**
     * \brief Add draw line.
     * \param dl drag line to add
     */
    void AddDrawLine(const DragLines &dl);
    
    /**
     * \brief Get the index drag lines.
     * \param index the get index
     * \return drag lines
     */
    DragLines GetDrawLine(const size_t &index);
    
    /**
     * \brief Get draw lines.
     * \return drawLines
     */
    std::vector<DragLines> GetDrawLines();
    
    /**
     * \brief Erase the index drag lines.
     * \param index the index to remove
     */
    void EraseDrawLine(const size_t &index);
  
    /**
     * \brief Draw the link.
     */
    void DrawLines();
  
    /**
     * \brief Paint widget.
     * \param event event from Qt
     */
    void paintEvent(QPaintEvent *event);

    /**
     * \brief Delete the last selected element.
     */
    void DeleteSelected();

    /**
     * \brief Update all tool tip text from all equipements.
     */
    void UpdateToolTips();

     /**
     * \brief Application server node name.
     */
    std::string m_appsServer;

    /**
     * \brief Application client node name.
     */
    std::string m_appsClient;

    /**
     * \brief Application type ping.
     */
    bool m_appsPing;

    /**
     * \brief Application type udp-echo.
     */
    bool m_appsUdpEcho;

    /**
     * \brief Application type tcp-large-transfer. 
     */
    bool m_appsTcp;

    /**
     * \brief Main window.
     */
    MainWindow *m_mw;


  private:
    /**
     * \brief last position of last object which moved.
     */ 
    QPoint m_lastPosition;
    
    /**
     * \brief last selected line boolean
     */
    bool m_isDrawLine;

    /**
     * \brief last selected line.
     */
    DragLines m_lastLine;
 
    /**
     * \brief Timer to refresh a line draw.
     */
    QTimer *m_timer;

    /**
     * \brief If we trace link or not.
     */
    bool m_traceNetworkHardware;

    /**
     * \brief Link begin.
     */
    std::string m_networkHardwareBegin;
    
    /**
     * \brief Link end.
     */
    std::string m_networkHardwareEnd;

    /**
     * \brief Link type.
     */
    std::string m_networkHardwareType;

    /**
     * \brief Lines.
     */
    //DragLines m_lines;

    /**
     * \brief Vector of lines (which represent links).
     */
    std::vector<DragLines> m_drawLines;

    /**
     * \brief Get name of the last selected equipment.
     * \return last selected name.
     */
    std::vector<std::string> GetLastSelected();

  protected:
    /**
     * \brief See Qt doc.
     */
    void dragEnterEvent(QDragEnterEvent *event);

    /**
     * \brief See Qt doc.
     */
    void dropEvent(QDropEvent *event);

    /**
     * \brief See Qt doc.
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * \brief See Qt doc.
     */
    void mouseMoveEvent(QMouseEvent *event);

};

#endif /*DRAG_WIDGET_H */

