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
 * \file test.cpp
 * \brief The test runner class
 * \author Pierre Weiss
 * \date 2009
 */

#include <cstdlib>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

/**
 * \brief Entry point of program.
 * \param argc number of argument
 * \param argv array of argument
 * \return EXIT_SUCCESS
 */
int main(int argc, char** argv)
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry& registry  = CppUnit::TestFactoryRegistry::getRegistry();

  argc = argc;
  argv = argv;

  runner.addTest(registry.makeTest());
  runner.run();

  return EXIT_SUCCESS;
}

