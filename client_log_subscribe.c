/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_log_subscribe
*/

#include "client.h"

void log_print_already_exist(char *buffer)
{
    client_error_already_exist();
}

void log_print_subscribed(char *buffer)
{
    char *user = get_param_file(buffer, 2, ';');
    char *team = get_param_file(buffer, 3, '\n');

    client_print_subscribed(user, team);
    free(user);
    free(team);
}

void log_unauthorized(char *buffer)
{
    client_error_unauthorized();
}

void log_print_unsubscribed(char *buffer)
{
    char *user = get_param_file(buffer, 2, ';');
    char *team = get_param_file(buffer, 3, '\n');

    client_print_unsubscribed(user, team);
    free(user);
    free(team);
}