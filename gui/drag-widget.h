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
     * \brief Create object which are on the tool bar.
     * \param type the type of the object to create
     * \param name his name
     * \param x position
     * \param y position
     */
    void CreateObject(const std::string &type, const std::string &name, const size_t &x, const size_t &y);

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
    void DrawLines();

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
     * \brief Set last position.
     * \param pos new position
     */
    void SetLastPosition(const QPoint &pos);
    
    /**
     * \brief Get last position.
     * \return last position
     */
    QPoint GetLastPosition();

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
     * \brief Get main window.
     * \return main window
     */
    MainWindow* GetMainWindow();
  
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
     * \brief Set drag lines.
     * \param lines added draglines
     */
    void SetDragLine(const DragLines &lines);
    
    /**
     * \brief Get drag lines.
     * \return dragLines
     */
    DragLines GetDragLines();
  
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
     * \brief Set timer.
     * \param timer new timer
     */
    void SetTimer(QTimer *timer);
    
    /**
     * \brief Get timer.
     * \return timer
     */
    QTimer* GetTimer();
  
    /**
     * \brief Set apps server.
     * \param appsServ new server name
     */
    void SetAppsServer(const std::string &appsServ);

    /**
     * \brief Get apps server.
     * \return apps server name
     */
    std::string GetAppsServer();

    /**
     * \brief Set apps client.
     * \param appsCli the apps client name
     */
    void SetAppsClient(const std::string &appsCli);
    
    /**
     * \brief Get apps Client.
     * \return apps client name
     */
    std::string GetAppsClient();

    /**
     * \brief Set apps ping.
     * \param appsPing new apps ping state
     */
    void SetAppsPing(const bool &appsPing);
    
    /**
     * \brief Get apps ping state
     * \return apps ping state
     */
    bool GetAppsPing();

    /**
     * \brief Set apps udp echo state.
     * \param appsUdp new state
     */
    void SetAppsUdpEcho(const bool &appsUdp);
    
    /**
     * \brief Get apps udp echo state.
     * \return apps udp echo state
     */
    bool GetAppsUdpEcho();

    /**
     * \brief Set apps tcp state.
     * \param appsTcp new apps ctp state
     */
    void SetAppsTcp(const bool &appsTcp);

    /**
     * \brief Get apps tcp state.
     * \return apps tcp state
     */
    bool GetAppsTcp();

    /**
     * \brief Set start time.
     * \param start new start time
     */
    void SetStartTime(const size_t &start);
    
    /**
     * \brief Get start time.
     * \return start time
     */
    size_t GetStartTime();

    /**
     * \brief Set end time.
     * \param end new end time
     */
    void SetEndTime(const size_t &end);
    
    /**
     * \brief Get end time.
     * \return end time
     */
    size_t GetEndTime();

    /**
     * \brief Set port.
     * \param port new port
     */
    void SetPort(const size_t &port);
    
    /**
     * \brief Get port.
     * \return port
     */
    size_t GetPort();

    /**
     * \brief Set dialog object.
     * \param dialog new dialog object
     */
    void SetDialog(QDialog *dialog);
    
    /**
     * \brief Get dialog object.
     * \return dialog object
     */
    QDialog* GetDialog();
  
    /**
     * \brief Set apps enable state.
     * \param state new state
     */
    void SetAppsEnable(const bool &state);
    
    /**
     * \brief Get apps enable state.
     * \return apps state
     */
    bool GetAppsEnable();

    /**
     * \brief Update tool tip text from dragged object
     * \param childName name of tool tip to update
     * \return tool tip text
     */
    std::string UpdateToolTip(const std::string &childName);

  private:
    /**
     * \brief last position of last object which moved.
     */ 
    QPoint m_lastPosition;

    /**
     * \brief Link begin.
     */
    std::string m_networkHardwareBegin;

    /**
     * \brief Main window.
     */
    MainWindow *m_mw;

    /**
     * \brief If we trace link or not.
     */
    bool m_traceNetworkHardware;

     /**
     * \brief Link type.
     */
    std::string m_networkHardwareType;

    /**
     * \brief Link end.
     */
    std::string m_networkHardwareEnd;

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

