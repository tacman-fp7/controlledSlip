# Copyright: (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Massimo Regoli, Nawid Jamali
# CopyPolicy: Released under the terms of the GNU GPL v3.0.

cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME controller)
project(${PROJECTNAME})

set(sources
    src/main.cpp
    src/ControllerUtil.cpp
    src/DataCollector.cpp
    src/IncomingData.cpp) 

set(headers
    src/include/main.h
    src/include/ControllerUtil.h
    src/include/DataCollector.h
    src/include/IncomingData.h) 

add_executable(${PROJECTNAME} ${sources} ${headers})
target_link_libraries(${PROJECTNAME})
install(TARGETS ${PROJECTNAME} DESTINATION bin)

