/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_command
*/

#include "client.h"

char *get_command(char *buffer, int fd)
{
    size_t bufs = 1024;

    memset(buffer, '\0', 1024);
    getline(&buffer, &bufs, stdin);
    if (strlen(buffer) == 0)
        buffer = strcpy(buffer, "/logout\n");
    if (buffer[strlen(buffer) - 1] != '\n')
        buffer[strlen(buffer)] = '\n';
    write_communication(fd, buffer);
    return (buffer);
}

struct tab function[] =
{
    {"2 ", &log_login},
    {"3 ", &log_logout},
    {"7 ", &log_unknown_user},
    {"8 ", &log_unknown_chan},
    {"9 ", &log_print_channel_created},
    {"13", &log_print_reply_created},
    {"14", &log_print_already_exist},
    {"15", &log_print_subscribed},
    {"17", &log_unknown_team},
    {"18", &log_print_team_created},
    {"20", &log_print_unsubscribed},
    {"22", &log_unknown_thread},
    {"23", &log_print_thread_created},
    {"27", &log_print_user},
    {"28", &log_print_thread},
    {"29", &log_print_channel},
    {"30", &log_print_team},
    {"33", &log_unauthorized}
};

struct tab function_list[] =
{
    {"7 ", &log_unknown_user},
    {"8 ", &log_unknown_chan},
    {"17", &log_unknown_team},
    {"22", &log_unknown_thread},
    {"27", &log_print_users},
    {"28", &log_print_threads},
    {"29", &log_print_channels},
    {"30", &log_print_teams},
    {"31", &log_print_replies},
    {"32", &log_print_messages},
    {"33", &log_unauthorized}
};

int do_action(char *buffer)
{
    int find = -1;

    for (int i = 0; i < 18; i += 1) {
        if (strncmp(buffer, function[i].str, 2) == 0)
            find = i;
    } if (find != -1) {
        function[find].func(buffer);
        return (TRUE);
    } else
        return (FALSE);

    return (0);
}

int do_action_list(char *buffer)
{
    int find = -1;

    for (int i = 0; i < 11; i += 1) {
        if (strncmp(buffer, function_list[i].str, 2) == 0)
            find = i;
    } if (find != -1) {
        function_list[find].func(buffer);
        return (TRUE);
    } else
        return (FALSE);

    return (0);
}