/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe
*/

#include "serveur.h"

int is_already_subscribe(info_t *info, char *str, char *team, int write_fd)
{
    char *first;
    char *second;
    int result = FALSE;

    first = get_param_file(str, 1, ';');
    second = get_param_file(str, 2, '\n');
    if (strcmp(first, team) == 0 && strcmp(second, info->user->id) == 0) {
        free(str);
        if (write_fd == 1)
            write_communication(info->fd, ALREADY_SUB);
        result = TRUE;
    }
    free(first);
    free(second);
    return (result);
}

int is_already_user_subscribe(char *user, char *str, char *team)
{
    char *first;
    char *second;
    int result = FALSE;

    first = get_param_file(str, 1, ';');
    second = get_param_file(str, 2, '\n');
    if (strcmp(first, team) == 0 && strcmp(second, user) == 0) {
        free(str);
        result = TRUE;
    }
    free(first);
    free(second);
    return (result);
}

int is_subscribe(info_t *info, char *team)
{
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("team_user", "a+");
    size_t bufs = 1024;

    while (getline(&str, &bufs, filed) > 0) {
        if (is_already_subscribe(info, str, team, 0) == TRUE) {
            fclose(filed);
            return (TRUE);
        }
        memset(str, '\0', 1024);
    }
    free(str);
    fclose(filed);
    return (FALSE);
}

int is_user_subscribe(char *user, char *team)
{
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("team_user", "a+");
    size_t bufs = 1024;

    while (getline(&str, &bufs, filed) > 0) {
        if (is_already_user_subscribe(user, str, team) == TRUE) {
            fclose(filed);
            return (TRUE);
        }
        memset(str, '\0', 1024);
    }
    free(str);
    fclose(filed);
    return (FALSE);
}

void write_link_in_file(char *team, FILE *filed, info_t *info, char *str)
{
    fwrite(team, 1, strlen(team), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    free(str);
    fclose(filed);
}
