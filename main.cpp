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

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <stdexcept>
#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>
#include <iostream>


#include "kern/Generator.h"
#include "gui/MainWindow.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow *win = new MainWindow(std::string("Simulation-Name"));
  win->setWindowTitle("Generator");
  win->show();
    
  app.exec();
	
	delete win;
}



