/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "serveur.h"

int check_use_thread(info_t *info, char *id_channel, char *id_team,
char *id_thread)
{
    char *response = malloc(sizeof(char) * 1024);

    if (is_thread_existing(id_thread) == FALSE) {
        write_communication(info->fd, THREAD_NOT_FOUND);
        free_thread(id_team, id_channel, id_thread, response);
        return (FALSE);
    }
    if (is_thread_channel(id_thread, id_channel) == FALSE) {
        write_communication(info->fd, THREAD_NOT_IN_TEAM);
        free_thread(id_team, id_channel, id_thread, response);
        return (FALSE);
    }
    free(response);
    return (TRUE);
}

void use_team(info_t *info, char *buffer)
{
    char *id_team = get_param_buffer(buffer, 1);

    set_team(info, id_team);
    channel_null(info);
    thread_null(info);
    write_communication(info->fd, USE_OK);
    free(id_team);
}

void use_channel(info_t *info, char *buffer)
{
    char *id_team = get_param_buffer(buffer, 1);
    char *id_channel = get_param_buffer(buffer, 2);

    set_team(info, id_team);
    set_channel(info, id_channel);
    thread_null(info);
    write_communication(info->fd, USE_OK);
    free(id_team);
    free(id_channel);
}

void use_thread(info_t *info, char *buffer)
{
    char *id_team = get_param_buffer(buffer, 1);
    char *id_channel = get_param_buffer(buffer, 2);
    char *id_thread = get_param_buffer(buffer, 3);

    set_team(info, id_team);
    set_channel(info, id_channel);
    set_thread(info, id_thread);
    write_communication(info->fd, USE_OK);
    free(id_team);
    free(id_channel);
    free(id_thread);
}

void use_main_team(info_t *info, char *buffer)
{
    char *id_team;

    id_team = get_param_buffer(buffer, 1);
    if (check_use_team(info, id_team) == TRUE)
        use_team(info, buffer);
}