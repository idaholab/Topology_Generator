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
#include <iostream>
#include <stdlib.h>
using namespace std;

//
// This class is written to test all the implementation of the generator code.
//


/* this procedure list all Equipement created by the generator and print it. */
void ListAllEquipement()
{
  for(int i = 0; i < Generator::getIndiceEquipement(); i++){
  	//~ cout << "#################" << endl;	
    cout << "Numéro :" << i << endl;
	cout << "nodeName :"<< Generator::listEquipement.at(i).getNodeName() << endl;
	cout << "ip :"<< Generator::listEquipement.at(i).getIp() << endl;
	cout << "mask :" << Generator::listEquipement.at(i).getMask() << endl;
	cout << "ipInterfaceName :" << Generator::listEquipement.at(i).getIpInterfaceName() << endl;
	cout << "header :" << Generator::listEquipement.at(i).getHeader() << endl;
	cout << "x :" << Generator::listEquipement.at(i).getX() << endl;
	cout << "y :" << Generator::listEquipement.at(i).getY() << endl;
	cout << "#################" << endl;	
  }	
		
}

void ListAllApplication()
{
}

void ListAllLink()
{
}

void Usage(){
  cout << "0 - exit." << endl;
  cout << "1 - List all equipements." << endl;
  cout << "2 - add a PC" << endl;
  cout << "choose :";
}

int main()
{
  int nbrChoose = 0;
  Generator gen;
  
  /* add 10 pc. */
  int i = 0;	
  while( i < 10 ){
  	gen.AddEquipement("Pc");
  	i += 1;
  }	
  
  cout << Generator::listEquipement.at(0).GenerateHeader() << endl;
	
  //gen.GenerateCode();
	
	
  /* manual operations. */	
  /*while(1){
  	Usage();
    cin >> nbrChoose;
    if(nbrChoose == 0){
      exit(EXIT_SUCCESS);
    } else if(nbrChoose == 1){
      ListAllEquipement(); 
    } else if(nbrChoose == 2){
      gen.AddEquipement("Pc");
    }
  }*/
}
