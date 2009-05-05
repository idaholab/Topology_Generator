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
   * 
   * The generator from the class.
   */
  Generator();	
	
  //
  // Part of Equipement.
  //
private:
  /**
   * \brief number attribute of equipement created.
   * 
   * This attribute is the number of equipement instance created.
   * It is used to set the node name, ....
   * 
   */
  static int indiceEquipement;
  
  
public: 
  /**
   * \brief list of equipement created instace.
   * 
   * This attribute is the list of the created instance of equipement.
   * 
   */
  static std::vector<Equipement*> listEquipement;
 
  /**
   * \brief Procedure used to add an equipement.
   * 
   * This procedure is used to add an equipement. It add the equipement to the
   * vector listEquipement and increment the number of equipement.
   * 
   * \param type the type of the equipement. (Pc, Hub, Switch,...)
   */
  static void AddEquipement(std::string type);
  
  /**
   * \brief Function wich return the number of equipement created.
   * 
   * This function return the number of equipement created in the application.
   * 
   * \return number of equipement
   */
  static int getIndiceEquipement();


  //
  // Part of Application.
  //
private:
  /**
   * \brief number attribute wich return the number of application created.
   * 
   * This function return the number of application created in the application.
   * 
   * \return number of application
   */
  static int indiceApplication; 
 
public:
  /**
   * \brief list of application created instace.
   * 
   * This attribute is the list of the created application of equipement.
   * 
   */
  //~ static vector<Application> listApplication;
   
  /**
   * \brief Procedure used to add an application.
   * 
   * This procedure is used to add an application. It add the application to the
   * vector listApplication and increment the number of application.
   * 
   * \param type the type of the application. (Ping, Udp_Echo,...)
   */
  static void AddApplication(std::string type);

  /**
   * \brief Function wich return the number of application created.
   * 
   * This function return the number of application created.
   * 
   * \return number of application
   */  static int getIndiceApplication();

  
  //
  // Part of Link.
  //
private:
  /**
   * \brief number attribute wich return the number of link created.
   * 
   * This function return the number of link created in the application.
   * 
   * \return number of link
   */
  static int indiceLink; 
  
public:
  /**
   * \brief list of link created instace.
   * 
   * This attribute is the list of the created instance of link.
   * 
   */
  //~ static vector<Link> listLink;
  
  /**
   * \brief Procedure used to add an link.
   * 
   * This procedure is used to add an link. It add the link to the
   * vector listLink and increment the number of link.
   * 
   * \param type the type of the link. (PointToPoint, Csma,...)
   */
  static void AddLink(std::string type);

  /**
   * \brief Function wich return the number of link created.
   * 
   * This function return the number of link created in the application.
   * 
   * \return number of link
   */
  static int getIndiceLink();
  
  
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
   * This function return a string wich contain all c++ command line.
   * 
   * \return command line 
   */
  std::string GenerateCmdLine();


  /**
   * \brief Function which return a string with the config option.
   * 
   * This function return a string which contain all config c++ code
   * 
   * \return generated config
   */
  std::string GenerateConfig();


  /**
   * \brief Function which return a string with all c++ node code.
   * 
   * This function return a string which contain all c++ node code.
   * 
   * \return generated node
   */
  std::string GenerateNode();


  /**
   * \brief Function which return a string with all c++ link code.
   * 
   * This function return a string which contain all c++ link code.
   * 
   * \return generated link
   */
  std::string GenerateLink();


  /**
   * \brief Function which return a string with all c++ net device code.
   * 
   * This function return a string which contain all c++ net device code.
   * 
   * \return generated net device
   */
  std::string GenerateNetDevice();


  /**
   * \brief Function which return a string with all c++ ip stack code.
   * 
   * This function return a string which contain all c++ ip stack code.
   * 
   * \return generated ip stack 
   */
  std::string GenerateIpStack();


  /**
   * \brief Function which return a string with all c++ ip assign code.
   * 
   * This function return a string which contain all c++ ip assign code.
   * 
   * \return generated ip assign
   */
  std::string GenerateIpAssign();


  /**
   * \brief Function which return string with all c++ route code.
   * 
   * This function return a string which contain all c++ route code.
   * 
   * \return generated route
   */
  std::string GenerateRoute();


  /**
   * \brief Function which return string with all c++ application code.
   * 
   * This function return a string which contain all c++ application node.
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
   * This file name is used to export the current simulation into xmlto save it.
   */
  std::string xmlFileName;
  
  /**
   * \brief function which return the attribute xml file name.
   * 
   * This function which return a string with the xml attribute file name.
   * 
   * \return xml file name
   */
  std::string getXmlFileName();
  
  /**
   * \brief procedure which set the xml file name.
   * 
   * This procedure is used to set the xml file name.
   * 
   * \param _xmlFileNam, the new xml file name.
   */
  void setXmlFileName(std::string _xmlFileName );

  /**
   * \brief Procedure wich write the simulation into xml file.
   * 
   * This procedure write the simulation into an xml file specified in attribute.
   * 
   * \param _line, the line to add to the xml file.
   */
  void WriteXml(std::string _line);
  
  /**
   * \brief procedure wich open and print graphicaly the xml file.
   * 
   * This procedure open and print graphicaly the xml file specified in attribute.
   */
  void OpenXml();
  
  
  //
  // Cpp generation operation part.
  //
private:

  /**
   * \brief attribute which are the name of the c++ output file name.
   * 
   * This attribute is the name of the c++ output file name
   */  
  std::string cppFileName;
  
  /**
   * \brief function which return the c++ output file name.
   * 
   * This function return astring which containe the c++ output file name.
   * 
   * \return c++ file name
   */
  std::string getCppFileName();
  
  /**
   * \brief procedure to set the c++ file name
   * 
   * This procedure set the cpp file name attribute.
   * 
   * \param _cppFileName, the new c++ file name
   */
  void setCppFileName(std::string _cppFileName );
  
  /**
   * \brief Procedure to write c++ code into the attribute file name.
   * 
   * This procedure write the c++ code passed in param.
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
   * 
   * This attribute is the name of the python output file name
   */
  std::string pyFileName;
  
  /**
   * \brief Function which return the python artribute name.
   * 
   * This function return the python outputfile name.
   * 
   * \return python file name
   */
  std::string getPyFileName();
  
  /**
   * \brief Procedure used to set the python file name attribute.
   * 
   * This procedure is used to set the python file name attribute.
   * 
   * \param _pyFileName the new python file name.
   */
  void setPyFileName(std::string _pyFileName);
  
  /**
   * \brief Procedure to write python code into the attribute file name.
   * 
   * This procedure is used tu write the param line into the attribute file name.
   * 
   * \param _line, the line to be writted. 
   */
   void WritePython(std::string _line);

};

#endif /* GENERATOR_H */

