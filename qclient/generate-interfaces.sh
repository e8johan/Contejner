#!/bin/sh

#  Copyright (C) 2016 Johan Thelin <e8johan@gmail.com>
#  Licensed under GPLv2, see file LICENSE in this source tree.

# Generates C++ sources from d-bus XML
# usage: generate-interfaces <source dir>

qdbusxml2cpp $1/../service/dbus-service.xml -p contejnermanager -c ContejnerManager -N
qdbusxml2cpp $1/../service/contejner-instance.xml -p contejnerinstance -c ContejnerInstance -N
