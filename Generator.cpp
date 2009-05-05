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
* \file Generator.cpp
* \brief The main class of the Generator.
* \author Pierre Weiss
* \date 2009
*/


#include "Generator.h"
#include "Equipement.h"
#include "Pc.h"

int Generator::indiceEquipement = 0;
int Generator::indiceApplication = 0;
int Generator::indiceLink = 0;
std::vector<Equipement*> Generator::listEquipement;
//~ vector<Application> Generator::listApplication;
//~ vector<Link> Generator::listLink;


Generator::Generator()
{
}

//
// Part of Equipement.
//


void Generator::AddEquipement(std::string type) 
{
  // call to the right type constructor. 
  if(type.compare("Pc") == 0)
  {
  	Pc *equi = new Pc();
  	Generator::listEquipement.push_back(equi);
  } 
  else if(type.compare("Router") == 0)
  {
  	//~ Router equi;
  } 
  else if(type.compare("Ap") == 0)
  {
  	//~ Ap equi;
  } 
  else if(type.compare("Station") == 0)
  {
    //~ Station equi;
  } 
  else if(type.compare("Hub") == 0)
  {
  	//~ Hub equi;
  } 
  else if(type.compare("Bridge") == 0)
  {
    //~ Switch equi;
  } 
  else if(type.compare("Tap") == 0)
  {
  	//~ Tap equi;
  } 
  
  //add to the equipement list.
  //You can't write this here ... you got an compile error. 
  //Generator::listEquipement.push_back(equi);
  
  // equipement added incrementation of indice. 
  Generator::indiceEquipement += 1;
}

int Generator::getIndiceEquipement() 
{
  return Generator::indiceEquipement;
}

//
// Part of Application.
//


void Generator::AddApplication(std::string type) 
{
  std::cout << type << std::endl;
/*  
  // call to the right type constructor. 
  if(type.compare("Ping") == 0){
  	Ping apps;
  } else if(type.compare("Tcp_large_transfert") == 0){
  	Tcp_large_transfert apps;
  } else if(type.compare("Udp_echo") == 0){
  	Udp_Echo apps;
  } 
  
  // add to the application list. 
  listApplication.push_back(apps);
  
  // application added incrementation of indice. 
  Generator::indiceApplixation += 1;
*/
}

int Generator::getIndiceApplication() 
{
  return Generator::indiceApplication;
}


//
// Part of Link.
//


void Generator::AddLink(std::string type) 
{
   std::cout << type << std::endl;
/*
  // call to the right type constructor.
  if(type.compare("Emu") == 0){
  	Emu link;
  } else if(type.compare("PointToPoint") == 0){
  	PointToPoint link;
  } else if(type.compare("Csma") == 0){
  	Csma link;
  } 
  
  // add to the application list.
  listLink.push_back(link);
  
  // application added incrementation of indice. 
  Generator::indiceLink += 1;
*/  
}

int Generator::getIndiceLink() 
{
  return Generator::indiceLink;
}


//
// Part around the code Generation.
// This part is looking about the code to write.
//


void Generator::GenerateCode() 
{	
  std::cout << "GenerateCode" << std::endl;
  GenerateHeader();
  //~ GenerateCmdLine() 
  //~ GenerateConfig() 
  GenerateNode(); 
  //~ GenerateLink() 
  //~ GenerateNetDevice() 
  //~ GenerateIpStack() 
  //~ GenerateIpAssign() 
  //~ GenerateRoute() 
  //~ GenerateApplications() 
}

std::vector<std::string> Generator::GenerateHeader() 
{
  std::vector<std::string> allHeaders;
  /* get all headers. */
  for(int i = 0; i < Generator::getIndiceEquipement(); i++)
  {
  	allHeaders.push_back((Generator::listEquipement.at(i))->GenerateHeader());
  }

  /* check for duplicate */
  std::vector<std::string> headersWithoutDuplicateElem;
  bool isDuplicate = false;
  /* iterate all headers string */
  for(int i = 0; i < (int) allHeaders.size(); i++)
  {
  	isDuplicate = false;
  	/* iterate the vector whith no duplicate */
  	for(int j = 0; j < (int) headersWithoutDuplicateElem.size(); j++)
  	{
  	  /* check if the string into the allHeaders vector is also in the vector without duplicate */
  	  if( allHeaders.at(i).compare(headersWithoutDuplicateElem.at(j)) == 0 )
  	  {
  	  	/* it's an duplicate. */
  	  	isDuplicate = true;
  	  	break;
	  }	
  	}
  	/* add the string from allHeaders if no duplicate have been detected. */
  	if(!isDuplicate)
  	{
  	  headersWithoutDuplicateElem.push_back(allHeaders.at(i));
  	}
  }
  
  /* print the res to see.*/
  for(int i = 0; i < (int) headersWithoutDuplicateElem.size(); i++)
  {
  	std::cout << "Num :" << i << " - " << headersWithoutDuplicateElem.at(i) << std::endl;
  }
  
  return headersWithoutDuplicateElem;
  
}

std::string Generator::GenerateCmdLine() 
{
  return "";
}

std::string Generator::GenerateConfig() 
{
  return "";
}

std::string Generator::GenerateNode() 
{
  return "";
}

std::string Generator::GenerateLink() 
{
  return "";
}
std::string Generator::GenerateNetDevice() 
{
  return "";
}

std::string Generator::GenerateIpStack() 
{
  return "";
}

std::string Generator::GenerateIpAssign() 
{
  return "";
}

std::string Generator::GenerateRoute() 
{
  return "";
}

std::string Generator::GenerateApplications() 
{
  return "";
}


//
// XML generation operation part.
//

void Generator::OpenXml() 
{
}

std::string Generator::getXmlFileName() 
{
  return this->xmlFileName;
}

void Generator::WriteXml(std::string _line) 
{
  std::cout << _line << std::endl;
}

void Generator::setXmlFileName(std::string _xmlFileName) 
{
  this->xmlFileName = _xmlFileName;
}

//
// Cpp generation operation part.
//

std::string Generator::getCppFileName() 
{
  return this->cppFileName;
}

void Generator::setCppFileName(std::string _cppFileName ) 
{
  this->cppFileName = _cppFileName;
}

void Generator::WriteCpp(std::string _line) 
{
  std::cout << _line << std::endl;
}

//
// Python generation operation part.
//
  
void Generator::WritePython(std::string _line)
{
   std::cout << _line << std::endl;
}

std::string Generator::getPyFileName() 
{
  return this->pyFileName;
}

void Generator::setPyFileName(std::string _pyFileName ) 
{
  this->pyFileName = _pyFileName;
}

