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

//  Topology Generated :
//  
//  PC ---- HUB ---- PC
// 

using namespace std;

#include <cstdlib>
#include <iostream>

#include "../generator.h"
#include "../udp-echo.h"

int main(int argc, char *argv[])
{
  /* avoid compile warnings */
  argc = argc;
  argv = argv;
  
  Generator *gen = new Generator(std::string("example-udpEcho"));
  
  /* Add the Pc equipement. */
  gen->AddNode("Pc");
  gen->AddNode("Pc"); 

  /* Add the NetworkHardware (csma) */
  gen->AddNetworkHardware("Hub"); 
  /* Add equipement to te link */
  gen->GetNetworkHardware(0)->Install(gen->GetNode(0)->GetNodeName());
  gen->GetNetworkHardware(0)->Install(gen->GetNode(1)->GetNodeName());

  /* Enable trace... */
  gen->GetNetworkHardware(0)->SetTrace(true);

  /* Add Udp echo application from pc to pc on PORT 6666 */
  gen->AddApplication("UdpEcho", gen->GetNode(0)->GetNodeName(), gen->GetNode(1)->GetNodeName(), 0, 5, 6666);// 0 start time - 5 end time
  
  UdpEcho *app = dynamic_cast<UdpEcho*>(gen->GetApplication(0));
  app->SetPacketSize(512);

  gen->GenerateCodeCpp();
  
  delete app;
  delete gen;
}
