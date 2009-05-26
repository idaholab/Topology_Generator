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
* \file MainWindow.h
* \brief The main windows file.
* \author Pierre Weiss
* \date 2009
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "DragWidget.h"
#include "Configuration.h"
#include "Generator.h"

/**
 * \ingroup generator
 * \brief The main window.
 *
 * This class create the menu, tool bar and the drag n drop zone.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    /**
     * \brief Constructor
     */
    MainWindow(const std::string &simulationName);
    
    /**
     * \brief Destructor
     */
    ~MainWindow();
    
     /**
     * \brief attribute used tu delete object.
     * Is attribute to setDisable ...
     */
    static QAction *delAction;
    
    /**
     * \brief attribute which represent the core object. 
     */
    static Generator *gen;
    
  private:
    /**
     * \brief attribute which represent the drag n drop zone.
     */
    DragWidget *dw;
    
    /**
     * \brief attribute which represent the configuration gui.
     */
    Configuration *config;
    
    /**
     * \brief interface which are used.
     */ 
    std::vector<std::string> listIface;
    
    /**
     * \procedure to erase the unused iface. 
     */
    void CleanIface();
    
  private slots:
    /**
     * \brief procedure called by the tool bar to create a pc.
     */
    void CreatePc();
    
    /**
     * \brief procedure called by the tool bar to create an Emu link.
     */
    void CreateEmu();
    
    /**
     * \brief procedure called by the tool bar to create a tap device.
     */
    void CreateTap();
    
    /**
     * \brief procedure called by the tool bar to create an access point.
     */
    void CreateAp();
    
    /**
     * \brief procedure called by the tool bar to create a wifi station.
     */
    void CreateStation();
    
    /**
     * \brief procedure called by the tool bar to create a hub (csma link)
     */
    void CreateHub();
    
    /**
     * \brief procedure called by the tool bar to create a switch (bridge)
     */
    void CreateSwitch();
    
    /**
     * \brief procedure called by the tool bar to create a router.
     */
    void CreateRouter();
    
    /**
     * \brief procedure called by the tool bar to delete an object.
     */
    void deleteObject();
    
    /**
     * \brief procedure called by the tool bar to get the configuration pop up.
     */
    void ConfigurationMenu();
    
    /**
     * \brief about gui.
     */
    void About();
    
    /**
     * \brief help gui/
     */
    void Help();
  
};

#endif /* END MAINWINDOW_H */
