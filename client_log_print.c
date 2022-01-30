/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_log_print
*/

#include "client.h"

void log_print_thread(char *buffer)
{
    char *thread = get_param_file(buffer, 2, ';');
    char *user = get_param_file(buffer, 3, ';');
    char *timestr = get_param_file(buffer, 4, ';');
    char *title = get_param_file(buffer, 5, ';');
    char *body = get_param_file(buffer, 6, '\n');
    time_t timenum = (time_t) strtol(timestr, NULL, 10);

    client_print_thread(thread, user, timenum, title, body);
    free(timestr);
    free(thread);
    free(user);
    free(body);
    free(title);
}

void log_print_channel(char *buffer)
{
    char *channel_id = get_param_file(buffer, 2, ';');
    char *channel_name = get_param_file(buffer, 3, ';');
    char *channel_description = get_param_file(buffer, 4, '\n');

    client_print_channel(channel_id, channel_name, channel_description);
    free(channel_id);
    free(channel_name);
    free(channel_description);
}

void log_print_team(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, ';');
    char *description = get_param_file(buffer, 4, '\n');

    client_print_team(id, name, description);
    free(id);
    free(name);
    free(description);
}