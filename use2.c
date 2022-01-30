/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use
*/

#include "serveur.h"

void free_team(char *id_team, char *response)
{
    if (id_team != NULL)
        free(id_team);
    if (response != NULL)
        free(response);
}

void free_channel(char *id_team, char *id_channel, char *response)
{
    free_team(id_team, response);
    if (id_channel != NULL)
        free(id_channel);
}

void free_thread(char *id_team, char *id_channel, char *id_thread,
char *response)
{
    free_channel(id_team, id_channel, response);
    if (id_thread != NULL)
        free(id_thread);
}

int check_use_team(info_t *info, char *id_team)
{
    char *response = malloc(sizeof(char) * 1024);

    if (is_team_existing(id_team) == FALSE) {
        response[sprintf(response, "%s%s\n", TEAM_NOT_FOUND, id_team)] = 0;
        write_communication(info->fd, response);
        free_team(id_team, response);
        return (FALSE);
    }
    if (is_subscribe(info, id_team) == FALSE) {
        write_communication(info->fd, UNAUTHORIZED);
        free_team(id_team, response);
        return (FALSE);
    }
    free(response);
    return (TRUE);
}

int check_use_channel(info_t *info, char *id_channel, char *id_team)
{
    char *response = malloc(sizeof(char) * 1024);

    if (is_channel_existing(id_channel) == FALSE) {
        write_communication(info->fd, CHAN_NOT_FOUND);
        free_channel(id_team, id_channel, response);
        return (FALSE);
    }
    if (is_channel_team(id_channel, id_team) == FALSE) {
        write_communication(info->fd, CHAN_NOT_IN_TEAMS);
        free_channel(id_team, id_channel, response);
        return (FALSE);
    }
    free(response);
    return (TRUE);
}