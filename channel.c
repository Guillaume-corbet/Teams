/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** channel
*/

#include "serveur.h"

void channel_null(info_t *info)
{
    if (info->channel->id != NULL) {
        free(info->channel->id);
        info->channel->id = NULL;
    }
    if (info->channel->description != NULL) {
        free(info->channel->description);
        info->channel->description = NULL;
    }
    if (info->channel->name != NULL) {
        free(info->channel->name);
        info->channel->name = NULL;
    }
}

int is_channel_existing(char *channel)
{
    char *id;
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("channel", "a+");
    size_t bufs = 1024;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(channel, id) == 0) {
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

int is_channel_team_verif_id(char *team, char *channel, char *str, FILE *filed)
{
    char *id;

    id = get_param_file(str, 1, ';');
    if (strcmp(channel, id) == 0) {
        free(id);
        id = get_param_file(str, 2, ';');
        if (strcmp(team, id) == 0) {
            free(str);
            free(id);
            fclose(filed);
            return (TRUE);
        }
    }
    free(id);
    return (FALSE);
}

int is_channel_team(char *channel, char *team)
{
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("channel", "a+");
    size_t bufs = 1024;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        if (is_channel_team_verif_id(team, channel, str, filed) == TRUE)
            return (TRUE);
        memset(str, '\0', 1024);
    }
    free(str);
    fclose(filed);
    return (FALSE);
}