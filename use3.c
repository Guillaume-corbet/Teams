/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "serveur.h"


void use_main_channel(info_t *info, char *buffer)
{
    char *id_team;
    char *id_channel;

    id_team = get_param_buffer(buffer, 1);
    id_channel = get_param_buffer(buffer, 2);
    if (check_use_team(info, id_team) == TRUE &&
        check_use_channel(info, id_channel, id_team) == TRUE)
        use_channel(info, buffer);
}

void use_main_thread(info_t *info, char *buffer)
{
    char *id_team;
    char *id_channel;
    char *id_thread;

    id_team = get_param_buffer(buffer, 1);
    id_channel = get_param_buffer(buffer, 2);
    id_thread = get_param_buffer(buffer, 3);
    if (check_use_team(info, id_team) == TRUE &&
        check_use_channel(info, id_channel, id_team) == TRUE &&
        check_use_thread(info, id_channel, id_team, id_thread) == TRUE)
        use_thread(info, buffer);
}

void use(info_t *info, char *buffer)
{
    int count_space = 0;

    for (int i = 0; buffer[i] != '\n'; i++) {
        if (buffer[i] == ' ')
            count_space = count_space + 1;
    }
    if (count_space == 1) {
        use_main_team(info, buffer);
    } else if (count_space == 2) {
        use_main_channel(info, buffer);
    } else if (count_space == 3) {
        use_main_thread(info, buffer);
    }
}