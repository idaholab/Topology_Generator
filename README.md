The ns-3 topology generator
===========================

The ns-3 topology generator project aims to provide a quick and easy way to create ns-3 topology.
It provides intuitive GUI so you can add nodes, link, applications, ... and generates C++ simulation 
code for ns-3.

1) Build / install
------------------

You need Qt 4 librarie to compile and use ns-3 topology generator.

To build the project:
 $ qmake
 $ make 

To use it, simply run:
 $ ./ns-3-generator

To generate the API documentation (you need doxygen tool):
$ doxygen Doxyfile

The HTML generated documentation is located in doc/html/ directory of sources.

License
------------------
/*
 * Copyright (c) 2009 University of Strasbourg
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * © 2015 Battelle Energy Alliance, LLC. ALL RIGHTS RESERVED
 *
 * Prepared by Battelle Energy Alliance, LLC.
 * Under Contract No. DE-AC07-05ID14517
 * With the U. S. Department of Energy
 *
 * NOTICE:  This computer software was prepared by Battelle Energy
 * Alliance, LLC, hereinafter the Contractor, under Contract
 * No. AC07-05ID14517 with the United States (U. S.) Department of
 * Energy (DOE).  The Government is granted for itself and others acting on
 * its behalf a nonexclusive, paid-up, irrevocable worldwide license in this
 * data to reproduce, prepare derivative works, and perform publicly and
 * display publicly, by or on behalf of the Government. There is provision for
 * the possible extension of the term of this license.  Subsequent to that
 * period or any extension granted, the Government is granted for itself and
 * others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide
 * license in this data to reproduce, prepare derivative works, distribute
 * copies to the public, perform publicly and display publicly, and to permit
 * others to do so.  The specific term of the license can be identified by
 * inquiry made to Contractor or DOE.  NEITHER THE UNITED STATES NOR THE UNITED
 * STATES DEPARTMENT OF ENERGY, NOR CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR
 * IMPLIED, OR ASSUMES ANY LIABILITY OR RESPONSIBILITY FOR THE USE, ACCURACY,
 * COMPLETENESS, OR USEFULNESS OR ANY INFORMATION, APPARATUS, PRODUCT, OR
 * PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY
 * OWNED RIGHTS.
 * 
 */
