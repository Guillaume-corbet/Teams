/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_log_prints
*/

#include "client.h"

void log_print_channels(char *buffer)
{
    char *channel_id = get_param_file(buffer, 2, ';');
    char *channel_name = get_param_file(buffer, 3, ';');
    char *channel_description = get_param_file(buffer, 4, '\n');

    client_team_print_channels(channel_id, channel_name, channel_description);
    free(channel_id);
    free(channel_name);
    free(channel_description);
}

void log_print_teams(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *name = get_param_file(buffer, 3, ';');
    char *description = get_param_file(buffer, 4, '\n');

    client_print_teams(id, name, description);
    free(id);
    free(name);
    free(description);
}

void log_print_replies(char *buffer)
{
    char *thread = get_param_file(buffer, 2, ';');
    char *user = get_param_file(buffer, 3, ';');
    char *str_timestamp = get_param_file(buffer, 4, ';');
    char *body = get_param_file(buffer, 5, '\n');
    time_t timestamp = (time_t) strtol(str_timestamp, NULL, 10);

    client_thread_print_replies(thread, user, timestamp, body);
    free(thread);
    free(user);
    free(str_timestamp);
    free(body);
}

void log_print_messages(char *buffer)
{
    char *user = get_param_file(buffer, 2, ';');
    char *str_timestamp = get_param_file(buffer, 3, ';');
    char *body = get_param_file(buffer, 4, '\n');
    time_t timestamp = (time_t) strtol(str_timestamp, NULL, 10);

    client_private_message_print_messages(user, timestamp, body);
    free(user);
    free(str_timestamp);
    free(body);
}

void log_print_threads(char *buffer)
{
    char *thread = get_param_file(buffer, 2, ';');
    char *user = get_param_file(buffer, 3, ';');
    char *timestr = get_param_file(buffer, 4, ';');
    char *title = get_param_file(buffer, 5, ';');
    char *body = get_param_file(buffer, 6, '\n');
    time_t timenum = (time_t) strtol(timestr, NULL, 10);

    client_channel_print_threads(thread, user, timenum, title, body);
    free(timestr);
    free(thread);
    free(user);
    free(body);
    free(title);
}