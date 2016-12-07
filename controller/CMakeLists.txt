# Copyright: (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Massimo Regoli, Nawid Jamali
# CopyPolicy: Released under the terms of the GNU GPL v3.0.

cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME controller)
project(${PROJECTNAME})

set(sources src/main.cpp) 

add_executable(${PROJECTNAME} ${sources})
target_link_libraries(${PROJECTNAME})
install(TARGETS ${PROJECTNAME} DESTINATION bin)

