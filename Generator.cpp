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


#include "Generator.h"
#include "Equipement.h"
#include "Pc.h"

int Generator::indiceEquipement = 0;
int Generator::indiceApplication = 0;
int Generator::indiceLink = 0;
vector<Equipement> Generator::listEquipement;
//~ vector<Application> Generator::listApplication;
//~ vector<Link> Generator::listLink;


Generator::Generator(){
  
}

//
// Part of Equipement.
//


void Generator::AddEquipement(string type) {
  // call to the right type constructor. 
  if(type.compare("Pc") == 0){
  	Pc equi;
  	Generator::listEquipement.push_back(equi);
  } else if(type.compare("Router") == 0){
  	//~ Router equi;
  } else if(type.compare("Ap") == 0){
  	//~ Ap equi;
  } else if(type.compare("Station") == 0){
    //~ Station equi;
  } else if(type.compare("Hub") == 0){
  	//~ Hub equi;
  } else if(type.compare("Bridge") == 0){
    //~ Switch equi;
  } else if(type.compare("Tap") == 0){
  	//~ Tap equi;
  } 
  
  //add to the equipement list.
  //You can't write this here ... you got an compile error. 
  //Generator::listEquipement.push_back(equi);
  
  // equipement added incrementation of indice. 
  Generator::indiceEquipement += 1;

}

int Generator::getIndiceEquipement() {
  return Generator::indiceEquipement;
}

//
// Part of Application.
//


void Generator::AddApplication(string type) {
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

int Generator::getIndiceApplication() {
  return Generator::indiceApplication;
}


//
// Part of Link.
//


void Generator::AddLink(string type) {
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

int Generator::getIndiceLink() {
  return Generator::indiceLink;
}


//
// Part around the code Generation.
// This part is looking about the code to write.
//


void Generator::GenerateCode() {

}

string Generator::GenerateHeader() {

}

string Generator::GenerateCmdLine() {

}

string Generator::GenerateConfig() {

}

string Generator::GenerateNode() {

}

string Generator::GenerateLink() {

}
string Generator::GenerateNetDevice() {

}

string Generator::GenerateIpStack() {

}

string Generator::GenerateIpAssign() {

}

string Generator::GenerateRoute() {

}

string Generator::GenerateApplications() {

}


//
// XML generation operation part.
//

void Generator::OpenXml() {

}

string Generator::getXmlFileName() {
  return this->xmlFileName;
}

void Generator::WriteXml(string _line) {

}

void Generator::setXmlFileName(string _xmlFileName) {
  this->xmlFileName = _xmlFileName;
}

//
// Cpp generation operation part.
//

string Generator::getCppFileName() {
  return this->cppFileName;
}

void Generator::setCppFileName(string _cppFileName ) {
  this->cppFileName = _cppFileName;
}

void Generator::WriteCpp(string _line) {

}

//
// Python generation operation part.
//
  
void Generator::WritePython(string _line){
}

string Generator::getPyFileName() {
  return this->pyFileName;
}

void Generator::setPyFileName(string _pyFileName ) {
  this->pyFileName = _pyFileName;
}

