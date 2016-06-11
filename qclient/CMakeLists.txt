#  Copyright (C) 2016 Johan Thelin <e8johan@gmail.com>
#  Licensed under GPLv2, see file LICENSE in this source tree.

PROJECT (qclient)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)

SET (SOURCES
     qcontainerprocess.cpp main.cpp)

ADD_DEFINITIONS(-Wall -Werror)

INCLUDE_DIRECTORIES (${GLIB_INCLUDE_DIRS})

ADD_EXECUTABLE (qclient
    ${SOURCES})

TARGET_LINK_LIBRARIES (qclient Qt5::Core
    ${GLIB_LIBRARIES})
