#this file tells CMake where to find Geant 4 and build the code
#CMake min version
cmake_minimum_required(VERSION 3.16)

#the project name is
project(RutherfordSim)

#first we have to find the GEANT4 Package, then ensure geant3 directory is set correctly when running cmake.
#cmake -DGeant4_DIR=/path/to/geant4_install/lib/cmake/Geant4 ..
find_package(Geant4 REQUIRED)

#Adding Geant 4 definitions and including the edirectories
include(${Geant4_USE_FILE})
include_directories(${Geant4_INCLUDE_DIRS})

#Adding the executable targets
add_executable(rutherford 
rutherford.cc
DetectorConstruction.cc 
PhysicsList.cc
ActionInitialization.cc
PrimaryGeneratorAction.cc
)

#linking the  created executables against geant4 libraries

target_link_libraries(rutherford ${Geant4_LIBRARIES})

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Geant4 Libraries: ${Geant4_Libraries}")
