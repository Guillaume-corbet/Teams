/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe
*/

#include "serveur.h"

void create_link(info_t *info, char *team, int write_fd)
{
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("team_user", "a+");
    size_t bufs = 1024;
    int empty = 0;

    while (getline(&str, &bufs, filed) > 0) {
        empty = 1;
        if (is_already_subscribe(info, str, team, 1) == TRUE) {
            fclose(filed);
            return;
        } memset(str, '\0', 1024);
    }
    if (empty == 1)
        fwrite("\n", 1, 1, filed);
    write_link_in_file(team, filed, info, str);
    server_event_user_join_a_team(team, info->user->id);
    if (write_fd == TRUE)
        write_communication(info->fd,
        concat_str(TEAM_SUB, info->user->id, team));
}

void subscribe(info_t *info, char *buffer, int write_fd, rlist *list)
{
    char *team;
    char *response;

    team = get_param_buffer(buffer, 1);
    usleep(100);
    if (is_team_existing(team) == FALSE) {
        response = malloc(sizeof(char) * 1024);
        response[sprintf(response, "%s%s\n", TEAM_NOT_FOUND, team)] = 0;
        write_communication(info->fd, response);
        free(team);
        free(response);
    } else {
        create_link(info, team, write_fd);
        free(team);
    }
}

void display_subscribed_team(info_t *info, char *str)
{
    char *id_team;

    id_team = get_param_file(str, 1, ';');
    display_one_team(info, id_team);
    memset(id_team, '\0', 1024);
    while (strlen(id_team) < 1)
        id_team = new_read_communication(info->fd, id_team);
    free(id_team);
}