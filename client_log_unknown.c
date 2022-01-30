/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_log_unkown
*/

#include "client.h"

void log_unknown_user(char *buffer)
{
    char *user = get_param_file(buffer, 2, '\n');

    client_error_unknown_user(user);
    free(user);
}

void log_unknown_chan(char *buffer)
{
    char *channel = get_param_file(buffer, 2, '\n');

    client_error_unknown_channel(channel);
    free(channel);
}

void log_unknown_team(char *buffer)
{
    char *team = get_param_file(buffer, 2, '\n');

    client_error_unknown_team(team);
    free(team);
}

void log_unknown_thread(char *buffer)
{
    char *thread = get_param_file(buffer, 2, '\n');

    client_error_unknown_thread(thread);
    free(thread);
}