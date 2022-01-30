/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team
*/

#include "serveur.h"

void set_team_value(info_t *info, char *str, FILE *filed, char *id)
{
    char *name = get_param_file(str, 2, ';');
    char *description = get_param_file(str, 3, ';');

    info->team->id = strdup(id);
    info->team->name = strdup(name);
    info->team->description = strdup(description);
    free(name);
    free(description);
    free(str);
    fclose(filed);
}

void set_team(info_t *info, char *id_team)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    char *name;
    char *description;
    size_t bufs = 1024;
    FILE *filed = fopen("team", "a+");

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(id, id_team) == 0) {
            set_team_value(info, str, filed, id);
            return;
        }
        memset(str, '\0', 1024);
        free(id);
    }
    free(str);
    fclose(filed);
}