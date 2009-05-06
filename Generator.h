/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss
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
* \file Generator.h
* \brief The main class of the Generator.
* \author Pierre Weiss
* \date 2009
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include "Equipement.h"
#include "Link.h"


/* Others */
#include <iostream>
#include <string>
#include <vector>

/**
 * \ingroup generator
 * \brief The main class of the Generator.
 *
 * This class is the main class from the generation of simulation.
 * It containt the main method to generate the code for the simulation.
 * 
 */
class Generator
{
public:

  /**
   * \brief the generator of the class Generator.
   */
  Generator();
  
  /**
   * \brief the destructor of the class.
   */
  ~Generator();	
	
  //
  // Part of Equipement.
  //
private:
  /**
   * \brief number attribute of Pc equipement created.
   */
  size_t indiceEquipementPc;
  
  /**
   * \brief number attribute of Router equipement created.
   */
  size_t indiceEquipementRouter;
  
  /**
   * \brief number attribute of Ap equipement created.
   */
  size_t indiceEquipementAp;
  
  /**
   * \brief number attribute of Station equipement created.
   */
  size_t indiceEquipementStation;
  
  /**
   * \brief number attribute of Bridge equipement created.
   */
  size_t indiceEquipementBridge;
  
  /**
   * \brief number attribute of Tap equipement created.
   */
  size_t indiceEquipementTap;
  
  
public: 
  /**
   * \brief list of equipement created instace.
   * 
   * This attribute is the list of the created instance of equipement.
   * 
   */
  std::vector<Equipement*> listEquipement;
 
  /**
   * \brief Procedure used to add an equipement.
   * 
   * This procedure is used to add an equipement. It add the equipement to the
   * vector listEquipement and increment the number of equipement.
   * 
   * \param type the type of the equipement. (Pc, Hub, Switch,...)
   */
  void AddEquipement(std::string type);
  
  
  //
  // Part of Application.
  //
private:
  /**
   * \brief 
   */
  size_t indiceApplication; 
 
public:
  
  //~ std::vector<Application> listApplication;
  /**
   * \brief 
   * \param type
   */
  void AddApplication(std::string type);

  
  //
  // Part of Link.
  //
private:
  /**
   * \brief number attribute of Ap link created.
   */
  size_t indiceLinkAp;
  
  /**
   * \brief number attribute of Station link created.
   */
  size_t indiceLinkStation;
  
  /**
   * \brief number attribute of Emu link created.
   */
  size_t indiceLinkEmu;
  
  /**
   * \brief number attribute of PointToPoint link created.
   */
  size_t indiceLinkPointToPoint;
  
  /**
   * \brief number attribute of Tap link created.
   */
  size_t indiceLinkTap;
  
  /**
   * \brief number attribute of Hub link created.
   */
  size_t indiceLinkHub;
  
  /**
   * \brief number attribute of Bridge link created.
   */
  size_t indiceLinkBridge; 
  
public:
  /**
   * \brief list of link created instace.
   * 
   * This attribute is the list of the created instance of link.
   * 
   */
  std::vector<Link*> listLink;
  
  /**
   * \brief Procedure used to add an link.
   * 
   * This procedure is used to add an link. It add the link to the
   * vector listLink and increment the number of link.
   * 
   * \param type the type of the link. (PointToPoint, Csma,...)
   */
  void AddLink(std::string type);

 
  //
  // Part around the code Generation.
  // This part is looking about the code to write.
  // 
public:
  /**
   * \brief Procedure wich are the main code generator.
   * 
   * This procedure is the main procedure to generate the code from the simulation.
   * It also go to use all the procedure on the bottom like generate all headers, ...
   * 
   */
  void GenerateCode();

private:
  /**
   * \brief Function which return all headers to use.
   * 
   * This function return a string wich contain all c++ header without duplicate.
   * 
   * \return header 
   */
  std::vector<std::string> GenerateHeader();


  /**
   * \brief Function which return all command line c++ code.
   * 
   * \return command line 
   */
  std::string GenerateCmdLine();


  /**
   * \brief Function which return a string with the config option.
   * 
   * \return generated config
   */
  std::string GenerateConfig();


  /**
   * \brief Function which return a string with all c++ node code.
   *
   * \return generated node
   */
  std::vector<std::string> GenerateNode();


  /**
   * \brief Function which return a string with all c++ link code.
   * 
   * \return generated link
   */
  std::vector<std::string> GenerateLink();


  /**
   * \brief Function which return a string with all c++ net device code.
   * 
   * \return generated net device
   */
  std::vector<std::string> GenerateNetDevice();


  /**
   * \brief Function which return a string with all c++ ip stack code.
   * 
   * \return generated ip stack 
   */
  std::vector<std::string> GenerateIpStack();


  /**
   * \brief Function which return a string with all c++ ip assign code.
   * 
   * \return generated ip assign
   */
  std::vector<std::string> GenerateIpAssign();


  /**
   * \brief Function which return string with all c++ route code.
   * 
   * \return generated route
   */
  std::string GenerateRoute();


  /**
   * \brief Function which return string with all c++ application code.
   * 
   * \return generated application
   */
  std::string GenerateApplications();


  
  //
  // XML generation operation part.
  //
private: 
 
  /**
   * \brief xml file name atribute.
   * 
   * This file name is used to export the current simulation into xml to save it.
   */
  std::string xmlFileName;
  
  /**
   * \brief function which return the attribute xml file name.
   *
   * \return xml file name
   */
  std::string getXmlFileName();
  
  /**
   * \brief procedure which set the xml file name.
   *
   * \param _xmlFileNam, the new xml file name.
   */
  void setXmlFileName(std::string _xmlFileName );

  /**
   * \brief Procedure wich write the simulation into xml file.
   * 
   * \param _line, the line to add to the xml file.
   */
  void WriteXml(std::string _line);
  
  /**
   * \brief procedure wich open and print graphicaly the xml file.
   */
  void OpenXml();
  
  
  //
  // Cpp generation operation part.
  //
private:

  /**
   * \brief attribute which are the name of the c++ output file name.
   */  
  std::string cppFileName;
  
  /**
   * \brief function which return the c++ output file name.
   * 
   * \return c++ file name
   */
  std::string getCppFileName();
  
  /**
   * \brief procedure to set the c++ file name
   * 
   * \param _cppFileName, the new c++ file name
   */
  void setCppFileName(std::string _cppFileName );
  
  /**
   * \brief Procedure to write c++ code into the attribute file name.
   * 
   * \param _line the new line to add to the attribute file name.
   */
  void WriteCpp(std::string _line);
  
  
  
  //
  // Python generation operation part.
  //
private:  
  
  /**
   * \brief Attribute which are the name of the python output file.
   */
  std::string pyFileName;
  
  /**
   * \brief Function which return the python artribute name.
   * 
   * \return python file name
   */
  std::string getPyFileName();
  
  /**
   * \brief Procedure used to set the python file name attribute.
   * 
   * \param _pyFileName the new python file name.
   */
  void setPyFileName(std::string _pyFileName);
  
  /**
   * \brief Procedure to write python code into the attribute file name.
   * 
   * \param _line, the line to be writted. 
   */
   void WritePython(std::string _line);

};

#endif /* GENERATOR_H */

