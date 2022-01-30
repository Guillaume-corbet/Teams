/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_log_user
*/

#include "client.h"

void log_print_user(char *buffer)
{
    char *user_id = get_param_file(buffer, 2, ';');
    char *user_name = get_param_file(buffer, 3, ';');
    char *str_status = get_param_file(buffer, 4, '\n');
    int status = my_getnbr(str_status);

    client_print_user(user_id, user_name, status);
    free(user_id);
    free(user_name);
    free(str_status);
}

void log_print_users(char *buffer)
{
    char *user_id = get_param_file(buffer, 2, ';');
    char *user_name = get_param_file(buffer, 3, ';');
    char *str_status = get_param_file(buffer, 4, '\n');
    int status = my_getnbr(str_status);

    client_print_users(user_id, user_name, status);
    free(user_id);
    free(user_name);
    free(str_status);
}

void log_login(char *buffer)
{
    char *user_id = get_param_file(buffer, 2, ';');
    char *username = get_param_file(buffer, 3, '\n');

    client_event_loggedin(user_id, username);
    free(user_id);
    free(username);
}

void log_logout(char *buffer)
{
    char *user_id = get_param_file(buffer, 2, ';');
    char *username = get_param_file(buffer, 3, '\n');

    client_event_loggedout(user_id, username);
    free(user_id);
    free(username);
}
