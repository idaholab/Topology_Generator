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
