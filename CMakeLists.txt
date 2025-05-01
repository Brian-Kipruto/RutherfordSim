#this file tells CMake where to find Geant 4 and build the code
#CMake min version
cmake_minimum_required(VERSION 3.16)

#the project name is
project(RutherfordSim)

#first we have to find the GEANT4 Package, then ensure geant3 directory is set correctly when running cmake.
#cmake -DGeant4_DIR=/path/to/geant4_install/lib/cmake/Geant4 ..
find_package(Geant4 REQUIRED)

#Adding Geant 4 definitions and including the edirectories
include (${Geant4_USE_File})
include_directories()