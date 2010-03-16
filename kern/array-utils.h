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
 * \file array-utils.h
 * \brief implementation of associate arrays using template
 * \author Pierre Weiss
 * \date 2009
 */

#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <iostream>
#include <vector>

/**
 * \ingroup utils
 * \brief Provide associative array in Cpp
 */
template <class T>
class Array 
{
  /**
   * \brief struc of an associated element
   */
  struct ItemStruct 
  {
    /**
     * \brief association name
     */
    std::string indexName;
    /**
     * \brief association data
     */
    T data;
  };

  private:
    /**
     * \brief vector wich contain all datas
     */
  std::vector <ItemStruct> stack;

  public:

    /**
     * \brief return array size
     * \return size
     */
    long size() 
    {
      return stack.size();
    }

    /**
     * \brief add an associated item
     * \param indexName the association string
     * \param data the associated data
     */
    void add(std::string indexName, T data) 
    {
      for(long i = 0; i < stack.size(); i++) 
        if(stack[i].indexName == indexName)
        {
          stack[i].data = data;
          return;
        }                  
        ItemStruct obj;
        obj.indexName = indexName;
        obj.data = data;
        stack.push_back(obj);
      }
      /**
       * \brief overwrite tab accessors
       */
      T &operator [] (long index) 
      {
        if(index < 0)
        {
          index=0;
        }
        return stack[index].data;
      }
      
      /**
       * \brief overwrite tab accessors
       */
      T &operator [](std::string indexName) 
      {
        for(size_t i = 0; i < stack.size(); i++) 
        { 
          if(stack[i].indexName == std::string(indexName)) 
          {
            return stack[i].data;
          }
        }
        long idx = stack.size();
        ItemStruct obj;
        obj.indexName = indexName;
        stack.push_back(obj);  
        return stack[idx].data;             
      }        
};
#endif /* ARRAY_UTILS_H */

