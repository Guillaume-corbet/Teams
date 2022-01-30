/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#include "client.h"

void log_notif_login(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, '\n');

    client_event_loggedin(id, name);
    free(id);
    free(name);
}

void log_notif_logout(char *buffer)
{
    char *user_id = get_param_file(buffer, 2, ';');
    char *username = get_param_file(buffer, 3, '\n');

    client_event_loggedout(user_id, username);
    free(user_id);
    free(username);
}

void log_notif_channel_created(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, ';');
    char *description = get_param_file(buffer, 4, '\n');

    client_event_channel_created(id, name, description);
    free(id);
    free(name);
    free(description);
}

void log_notif_team_created(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, ';');
    char *description = get_param_file(buffer, 4, '\n');

    client_event_team_created(id, name, description);
    free(id);
    free(name);
    free(description);
}

void log_notif_thread_created(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, ';');
    char *str_timestamp = get_param_file(buffer, 4, ';');
    char *title = get_param_file(buffer, 5, ';');
    char *description = get_param_file(buffer, 6, '\n');
    time_t timestamp = (time_t) strtol(str_timestamp, NULL, 10);

    client_event_thread_created(id, name, timestamp, title, description);
    free(id);
    free(name);
    free(description);
    free(title);
    free(str_timestamp);
}