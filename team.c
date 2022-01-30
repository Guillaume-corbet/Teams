/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team
*/

#include "serveur.h"

int is_team_existing(char *team)
{
    char *id;
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("team", "a+");
    size_t bufs = 1024;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(team, id) == 0) {
            free(id);
            free(str);
            fclose(filed);
            return (TRUE);
        }
        memset(str, '\0', 1024);
        free(id);
    }
    free(str);
    fclose(filed);
    return (FALSE);
}

void display_list_team_sec(info_t *info, char *buffer)
{
    char *id = get_param_file(buffer, 1, ';');
    char *name = get_param_file(buffer, 2, ';');
    char *description = get_param_file(buffer, 3, ';');
    char *response = malloc(sizeof(char) * 1024);

    response[sprintf(response, "%s%s;%s;%s\n",
    TEAM_DISPLAY, id, name, description)] = 0;
    write_communication(info->fd, response);
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(info->fd, buffer);

    free(response);
    free(id);
    free(name);
    free(description);
}

void display_list_team(info_t *info)
{
    char *buffer = malloc(sizeof(char) * 1024);
    FILE *filed;
    size_t bufs = 1024;
    char *response;
    char *id;
    char *name;
    char *description;

    filed = fopen("team", "a+");
    memset(buffer, '\0', 1024);
    while (getline(&buffer, &bufs, filed) > 0) {
        display_list_team_sec(info, buffer);
        memset(buffer, '\0', 1024);
    }
    free(buffer);
    fclose(filed);
    write_communication(info->fd, LIST_FINISH);
}

int search_team(info_t *info, char *id_team, char *str, FILE *filed)
{
    char *id = get_param_file(str, 1, ';');
    char *name = get_param_file(str, 2, ';');
    char *description = get_param_file(str, 3, ';');
    char *response = malloc(sizeof(char) * 1024);

    if (strcmp(id, id_team) == 0) {
        response[sprintf(response, "%s%s;%s;%s\n", TEAM_DISPLAY,
        id, name, description)] = 0;
        write_communication(info->fd, response);
        free(response);
        free(str);
        fclose(filed);
        return (TRUE);
    }
    memset(str, '\0', 1024);
    free(id);
    free(name);
    free(description);
    free(response);
    return (FALSE);
}

void display_one_team(info_t *info, char *id_team)
{
    char *str = malloc(sizeof(char) * 1024);
    size_t bufs = 1024;
    FILE *filed = fopen("team", "a+");
    char *response = malloc(sizeof(char) * 1024);

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        if (search_team(info, id_team, str, filed) == TRUE)
            return;
    }
    free(str);
    response[sprintf(response, "%s%s\n", TEAM_NOT_FOUND, id_team)] = 0;
    write_communication(info->fd, response);
    fclose(filed);
    free(response);
}