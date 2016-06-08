/*
 * Copyright (C) 2016 Jonatan Pålsson <jonatan.p@gmail.com>
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */

#ifndef CONTEJNER_COMMON_H
#define CONTEJNER_COMMON_H

#ifndef CONTEJNER_MANAGER_INTERFACE_DBUS_NAME
#define CONTEJNER_MANAGER_INTERFACE_DBUS_NAME "org.jonatan.Contejner"
#endif

#ifndef CONTEJNER_MANAGER_INTERFACE_DBUS_PATH
#define CONTEJNER_MANAGER_INTERFACE_DBUS_PATH "/org/jonatan/Contejner"
#endif

#ifndef CONTEJNER_INSTANCE_INTERFACE_NAME
#define CONTEJNER_INSTANCE_INTERFACE_NAME "org.jonatan.Contejner.Container"
#endif

#ifndef CONTEJNER_INSTANCE_INTERFACE_PATH
#define CONTEJNER_INSTANCE_INTERFACE_PATH "/org/jonatan/Contejner/Containers"
#endif

enum contejner_error_code {
    CONTEJNER_OK = 0,
    CONTEJNER_ERR_FAILED_TO_START,
    CONTEJNER_ERR_NO_SUCH_CONTAINER
};

#endif /* CONTEJNER_COMMON_H */
