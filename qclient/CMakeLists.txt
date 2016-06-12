#  Copyright (C) 2016 Johan Thelin <e8johan@gmail.com>
#  Licensed under GPLv2, see file LICENSE in this source tree.

PROJECT (qclient)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Core and DBus libraries
find_package(Qt5Core)
find_package(Qt5DBus)

SET (SOURCES
     qcontainerprocess.cpp main.cpp
     ${CMAKE_CURRENT_BINARY_DIR}/contejnermanager.cpp ${CMAKE_CURRENT_BINARY_DIR}/contejnerinstance.cpp)

ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/contejnermanager.h ${CMAKE_CURRENT_BINARY_DIR}/contejnermanager.cpp ${CMAKE_CURRENT_BINARY_DIR}/contejnerinstance.h ${CMAKE_CURRENT_BINARY_DIR}/contejnerinstance.cpp
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate-interfaces.sh ${CMAKE_CURRENT_SOURCE_DIR}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS ../service/dbus-service.xml ../service/contejner-instance.xml)

SET(qcontainerprocess.cpp_DEPS
    ${CMAKE_CURRENT_BINARY_DIR}/contejnermanager.h ${CMAKE_CURRENT_BINARY_DIR}/contejnermanager.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/contejnerinstance.h ${CMAKE_CURRENT_BINARY_DIR}/contejnerinstance.cpp)

SET_SOURCE_FILES_PROPERTIES(qcontainerprocess.cpp PROPERTIES OBJECT_DEPENDS "${qcontainerprocess.cpp_DEPS}")

ADD_DEFINITIONS(-Wall -Werror)

INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE (qclient
    ${SOURCES})

TARGET_LINK_LIBRARIES (qclient Qt5::Core
    ${GLIB_LIBRARIES})
