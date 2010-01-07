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
 * \file main-window.h
 * \brief The main windows file.
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>

#include "drag-widget.h"
#include "generator.h"

/**
 * \ingroup generator
 * \brief The main window.
 *
 * This class create the menu, tool bar and the drag'n'drop zone.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    /**
     * \brief Constructor.
     */
    MainWindow(const std::string &simulationName);

    /**
     * \brief Destructor.
     */
    ~MainWindow();

    /**
     * \brief Valid links.
     */
    void ValidNetworkHardware();

    /**
     * \brief Valid applications install.
     */
    void ValidApps();

    /**
     * \brief Procedure to erase the unused iface. 
     */
    void CleanIface();

    /**
     * \brief Procedure to connect node to linkNumber.
     * This procedure prevent mask overflow.
     * \param linkNumber the number of the link
     * \param nodeName the node name tu be added
     */
    void ConnectNode(const size_t &linkNumber, const std::string &nodeName);

    /**
     * \brief Set generator object.
     * \param gen new generator object
     */
    void SetGenerator(Generator *gen);
    
    /**
     * \brief Get generator object.
     * \return generator object
     */
    Generator* GetGenerator();
    
    /**
     * \brief Set delete qaction button.
     * \param delAction new qaction object
     */
    void SetDelQAction(QAction *delAction);
    
    /**
     * \brief Get delete qaction button.
     * \return qaction object
     */
    QAction* GetDelQAction();
    
    /**
     * \brief Set the drag widget object.
     * \param dw new drag widget
     */
    void SetDragWidget(DragWidget *dw);

    /**
     * \brief Get the drag widget object.
     * \return drag widget object
     */
    DragWidget* GetDragWidget();
  
    /**
     * \brief Add an element to the iface list.
     * \param str the element to be added
     */
    void AddIfaceList(const std::string &str);

    /**
     * \brief Get the iface list.
     * \return iface list
     */
    std::vector<std::string> GetIfaceLists();
    
    /**
     * \brief Get the N element from the iface list.
     * \param index the n element index
     * \return the n element
     */
    std::string GetIfaceList(const size_t &index);

    /**
     * \brief Erase the N element from iface list.
     * \param index the n element index
     */
    void EraseIfaceList(const size_t &index);

  private:
    /**
     * \brief Generator.
     */
    Generator *m_gen;

    /**
     * \brief Action to delete object.
     * Is attribute to setDisable ...
     */
    QAction *m_delAction;

    /**
     * \brief The drag'n'drop zone.
     */
    DragWidget *m_dw;

    /**
     * \brief interface which are used.
     */ 
    std::vector<std::string> m_listIface;

  private slots:
    /**
     * \brief Create PC.
     */
    void CreatePc();

    /**
     * \brief Create group of PCs.
     */
    void CreatePcGroup();

    /**
     * \brief Create an "Emu" link.
     */
    void CreateEmu();

    /**
     * \brief Create a tap device.
     */
    void CreateTap();

    /**
     * \brief Create an access point (AP).
     */
    void CreateAp();

    /**
     * \brief Create a WI-FI station.
     */
    void CreateStation();

    /**
     * \brief Create a hub (csma link)
     */
    void CreateHub();

    /**
     * \brief Create a switch (bridge)
     */
    void CreateSwitch();

    /**
     * \brief Create a router.
     */
    void CreateRouter();

    /**
     * \brief Create a wired link from equipement to equipement.
     */
    void CreateWiredNetworkHardware();

    /**
     * \brief Create a link from station to AP.
     */
    void CreateStationNetworkHardware();

    /**
     * \brief Procedure to create a p2p link from equipement to equipement.
     */
    void CreateP2pNetworkHardware();

    /**
     * \brief Procedure called by the tool bar to delete an object.
     */
    void DeleteObject();

    /**
     * \brief Procedure called by the tool bar to get the configuration pop up.
     */
    void ConfigurationMenu();

    /**
     * \brief Show about UI.
     */
    void About();

    /**
     * \brief Show help UI.
     */
    void Help();

    /**
     * \brief Generate the C++ code.
     */
    void GenerateCpp();

    /**
     * \brief Generate the Python code.
     */
    void GeneratePython();

    /**
     * \brief Create an application for a simulation node.
     */
    void CreateApps();
    
    /**
     * \brief Save simulation as a picture.
     */
    void SavePicture();

    /**
     * \brief Save Simulation into xml file.
     */
    void SaveXml();

    /**
     * \brief Load xml simulation file.
     */
    void LoadXml();
};

#endif /* MAIN_WINDOW_H */

