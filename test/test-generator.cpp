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
* \file test-Generator.cpp
* \brief Unit test for Generator class
* \author Pierre Weiss
* \date 2009
*/

#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>
#include "../kern/Generator.h"

namespace tests
{
  /**
   * \ingroup generator
   * \brief The generator test class
   *
   */
  class TestGenerator : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(tests::TestGenerator);
    
    CPPUNIT_TEST(testAddNode);
    CPPUNIT_TEST(testRemoveNode);
    CPPUNIT_TEST_EXCEPTION(addWrongEquipement, std::exception);
    CPPUNIT_TEST_EXCEPTION(getWrongEquipement, std::out_of_range);
    
    CPPUNIT_TEST(testAddLink);
    CPPUNIT_TEST(testRemoveLink);
    CPPUNIT_TEST_EXCEPTION(addWrongLink, std::exception);
    CPPUNIT_TEST_EXCEPTION(getWrongLink, std::out_of_range);
    
    CPPUNIT_TEST_SUITE_END();

    private:
      Generator *gen;
      
    public:
      void setUp()
      {
        this->gen = new Generator("testGenerator");
      }

      void tearDown()
      {
        delete this->gen;
      }


      //
      // Equipements
      //
      /**
       * \brief test to add an equipement.
       */
      void testAddNode()
      {
        size_t initSize = gen->listNode.size();
        this->gen->AddNode("Pc");
        size_t finalSize = gen->listNode.size();
        CPPUNIT_ASSERT(initSize == (finalSize - 1));
      }
      
      /**
       * \brief test to remove an equipement.
       */
      void testRemoveNode()
      {
        size_t initSize = gen->listNode.size();
        this->gen->AddNode("Pc");
        this->gen->RemoveNode(gen->listNode.size() - 1);
        size_t finalSize = gen->listNode.size();
        CPPUNIT_ASSERT(initSize == finalSize);
      }
      
      /**
       * \brief test to add a wrong equipement
       */
      void addWrongEquipement()
      {
        this->gen->AddNode("");
      }
      
      /**
       * \brief get a wrong equipement.
       */
      void getWrongEquipement()
      {
        this->gen->listNode.at(-1);
      }
      
      //
      // Links
      //
      
      /**
       * \brief test to add a link.
       */
      void testAddLink()
      {
        size_t initSize = gen->listLink.size();
        this->gen->AddLink("Hub");
        size_t finalSize = gen->listLink.size();
        CPPUNIT_ASSERT(initSize == (finalSize - 1));
      }
      
      /**
       * \brief test to remove a link.
       */
      void testRemoveLink()
      {
        size_t initSize = gen->listLink.size();
        this->gen->AddLink("Hub");
        this->gen->RemoveLink(gen->listLink.size() - 1);
        size_t finalSize = gen->listLink.size();
        CPPUNIT_ASSERT(initSize == finalSize);
      }
      
      /**
       * \brief test to add a wring link.
       */
      void addWrongLink()
      {
        this->gen->AddLink("");
      }
      
      /**
       * \brief test to get a wrong link.
       */
      void getWrongLink()
      {
        this->gen->listLink.at(-1);
      }
  };
} 

CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestGenerator);

