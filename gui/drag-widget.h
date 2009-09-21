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
#include <QtGui>

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
     */
    void CreateObject(const std::string &type, const std::string &name);

    /**
     * \brief Delete the last selected element.
     */
    void DeleteSelected();

    /**
     * \brief Get name of the last selected equipment.
     * \return last selected name.
     */
    std::vector<std::string> GetLastSelected();

    /**
     * \brief Reset lastSelected equipment.
     */
    void ResetSelected();

    /**
     * \brief Draw the link.
     */
    void DrawLine();

    /**
     * \brief Paint widget.
     * \param event event from Qt
     */
    void paintEvent(QPaintEvent *event);

    /**
     * \brief Set the MainWindow.
     * \param _mw
     */
    void SetMainWindow(MainWindow *_mw);

    /**
     * \brief Show the ping UI.
     */
    void ShowGuiPing();

    /**
     * \brief Show the udp-echo UI.
     */
    void ShowGuiUdpEcho();

    /**
     * \brief Show the tcp-large-transfer UI.
     */
    void ShowGuiTcp();

    /**
     * \brief Get the child object from his name.
     * \param name name of the object to find
     */
    DragObject* GetChildFromName(const std::string &name);

/* to be made private ... but ... */ 
  //private:
    /**
     * \brief last position of last object which moved.
     */ 
    QPoint m_lastPosition;

    /**
     * \brief Link begin.
     */
    std::string m_linkBegin;

    /**
     * \brief Main window.
     */
    MainWindow *m_mw;

    /**
     * \brief If we trace link or not.
     */
    bool m_traceLink;

     /**
     * \brief Link type.
     */
    std::string m_linkType;

    /**
     * \brief Link end.
     */
    std::string m_linkEnd;

    /**
     * \brief Lines.
     */
    DragLines m_lines;

    /**
     * \brief Vector of lines (which represent links).
     */
    std::vector<DragLines> m_drawLines;

    /**
     * \brief Timer to refresh a line draw.
     */
    QTimer *m_timer;

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
     * \brief Start time.
     */
    size_t m_startTime;

    /**
     * \brief End Time.
     */
    size_t m_endTime;

    /**
     * \brief Port attribute. 
     */
    size_t m_port;

    /**
     * \brief Application dialog box.
     */
    QDialog *m_dialog;

    /**
     * \brief Show if applications are at this time in use or not.
     */
    bool m_appsEnable;

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

  public slots:
    /**
     * \brief Choose the new server node.
     */
    void ChooseServer();

    /**
     * \brief Choose the new client node.
     */
    void ChooseClient();

    /**
     * \brief Cancel button.
     */
    void Cancel();
};

#endif /*DRAG_WIDGET_H */

