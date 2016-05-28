#include <stdio.h>
#include <gio/gio.h>

enum command {
    CMD_CREATE_THEN_EXIT,
    CMD_LIST_CONTAINERS_THEN_EXIT,
    CMD_EXECUTE_COMMAND
};

struct client {
    GDBusProxy *proxy;
    enum command command;
    GMainLoop *loop;
    gchar *exec_command;
    gchar **exec_command_args;
};

static void create (struct client *client)
{
    GError *error = NULL;
    gchar *interface = NULL;

    GVariant *retval = g_dbus_proxy_call_sync (client->proxy,
                                               "org.jonatan.Contejner.Create",
                                               NULL,
                                               G_DBUS_PROXY_FLAGS_NONE,
                                               -1,
                                               NULL,
                                               &error);
    if (retval) {
        g_variant_get (retval, "(s)", &interface);
        g_variant_unref (retval);
        g_print ("Created new container: %s", interface);
    } else if (error) {
        g_error("Failed to call Create");
    }
}

static void set_command (struct client *client)
{
    GError *error = NULL;
    gchar *interface = NULL;

    char *args[] = {"/", NULL};

    GVariant *params = g_variant_new("(s^as)",
                                     &client->exec_command,
                                     &args);

    GVariant *retval = g_dbus_proxy_call_sync (client->proxy,
                                               "org.jonatan.Contejner.Container0.SetCommand",
                                               params,
                                               G_DBUS_PROXY_FLAGS_NONE,
                                               -1,
                                               NULL,
                                               &error);
    if (retval) {
        g_variant_get (retval, "(s)", &interface);
        g_variant_unref (retval);
        g_print ("Created new container: %s", interface);
    } else if (error) {
        g_error("Failed to call SetCommand");
    }
}

static void list_containers(struct client *client)
{
    GError *error = NULL;
    GDBusObjectManager *mgr = g_dbus_object_manager_client_new_for_bus_sync (
                                     G_BUS_TYPE_SESSION,
                                     G_DBUS_OBJECT_MANAGER_CLIENT_FLAGS_NONE,
                                     "org.jonatan.Contejner",
                                     "/org/jonatan/Contejner",
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &error);
    if (mgr) {
        GList *objects = g_dbus_object_manager_get_objects(mgr);
        GList *l;
        for (l = objects; l != NULL; l = l->next)
        {
            GDBusObject *o = G_DBUS_OBJECT(l->data);
            g_print(g_dbus_object_get_object_path(o));
            GList *ifaces = g_dbus_object_get_interfaces(o);
            GList *ll;
            for (ll = ifaces; ll != NULL; ll = ll->next)
            {
                GDBusInterface *interface = G_DBUS_INTERFACE(ll->data);
                GDBusInterfaceInfo *info =
                    g_dbus_interface_get_info(interface);
                if (info) {
                    g_print(" - %s", info->name);
                } else {
                    g_print(" - Unable to get interface info");
                }
                g_object_unref(ll->data);
            }
            g_list_free(ifaces);
            g_object_unref(l->data);
        }
        g_list_free(objects);
    } else {
        g_print("Failed to list containers");
    }
}

static void proxy_ready (GObject *source_object,
                         GAsyncResult *res,
                         gpointer user_data)
{
    GError *error = NULL;
    struct client *client = user_data;
    client->proxy = g_dbus_proxy_new_for_bus_finish(res, &error);
    if (error) {
        g_error ("Failed to connect to Contejner service");
    }

    switch (client->command) {
        case CMD_CREATE_THEN_EXIT:
            create(client);
            g_main_loop_quit(client->loop);
            break;
        case CMD_LIST_CONTAINERS_THEN_EXIT:
            list_containers(client);
            break;
        case CMD_EXECUTE_COMMAND:
            create(client);
            set_command(client);
            g_main_loop_quit(client->loop);
            break;
        default:
            g_error("Unknown command");
    }
}

static void print_func (const gchar *string)
{
    printf("%s\n", string);
}

int main(int argc, char **argv) {
    struct client client = { 0 };
    client.command = CMD_EXECUTE_COMMAND;
    client.exec_command = "/bin/ls";
    (client.exec_command_args) = g_malloc0(sizeof(char*) * 2);
    (client.exec_command_args)[0] = "/";
    g_set_print_handler(print_func);

    g_dbus_proxy_new_for_bus (G_BUS_TYPE_SESSION,
                              G_DBUS_PROXY_FLAGS_NONE,
                              NULL,
                              "org.jonatan.Contejner",
                              "/org/jonatan/Contejner",
                              "org.jonatan.Contejner",
                              NULL,
                              proxy_ready,
                              &client);

    client.loop = g_main_loop_new (NULL, FALSE);
    g_main_loop_run (client.loop);
    return 0;
}
