/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe
*/

#include "serveur.h"

void subscribed_team(info_t *info)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    size_t bufs = 1024;
    FILE *filed = fopen("team_user", "a+");

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 2, '\n');
        if (strcmp(id, info->user->id) == 0) {
            display_subscribed_team(info, str);
        }
        memset(str, '\0', 1024);
        free(id);
    }
    write_communication(info->fd, LIST_FINISH);
    free(str);
    fclose(filed);
}

char *display_user_on_team(info_t *info, char *str, rlist *list)
{
    char *id_user;
    char *buf = malloc(sizeof(char) * 1024);

    id_user = get_param_file(str, 2, '\n');
    buf = strcpy(buf, "/user \"");
    buf = strcat(buf, id_user);
    buf = strcat(buf, "\"\n");
    display_user(info, buf, list);
    free(id_user);
    memset(buf, '\0', 1024);
    while (strlen(buf) < 1)
        buf = new_read_communication(info->fd, buf);
    free(buf);
}

void subscribed_user(info_t *info, char *team, rlist *list)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id_team;
    size_t bufs = 1024;
    FILE *filed = fopen("team_user", "a+");

    while (getline(&str, &bufs, filed) > 0) {
        id_team = get_param_file(str, 1, ';');
        if (strcmp(id_team, team) == 0) {
            display_user_on_team(info, str, list);
        }
        memset(str, '\0', 1024);
        free(id_team);
    }
    free(str);
    write_communication(info->fd, LIST_FINISH);
    fclose(filed);
}

void while_func(info_t *info, char *team)
{
    char *response = malloc(sizeof(char) * 1024);
    response[sprintf(response, "%s%s\n", TEAM_NOT_FOUND, team)] = 0;
    write_communication(info->fd, response);
    free(response);
    memset(team, '\0', 1024);
    while (strlen(team) < 1)
        team = new_read_communication(info->fd, team);
    write_communication(info->fd, LIST_FINISH);
}

void subscribed(info_t *info, char *buffer, rlist *list)
{
    char *team;

    if (strcmp("/subscribed\n", buffer) == 0) {
        subscribed_team(info);
    } else {
        team = get_param_buffer(buffer, 1);
        if (is_team_existing(team) == TRUE)
            subscribed_user(info, team, list);
        else {
            while_func(info, team);
        }
        free(team);
    }
}