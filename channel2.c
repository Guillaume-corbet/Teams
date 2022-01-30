/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** channel
*/

#include "serveur.h"


void display_list_channel_sec(info_t *info, char *buffer)
{
    char *id_team;
    char *response;
    char *id;
    char *name;
    char *description;

    id = get_param_file(buffer, 1, ';');
    name = get_param_file(buffer, 3, ';');
    description = get_param_file(buffer, 4, ';');
    response = malloc(sizeof(char) * 1024);
    response[sprintf(response, "%s%s;%s;%s\n",
    CHANNEL_DISPLAY, id, name, description)] = 0;
    write_communication(info->fd, response);
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(info->fd, buffer);
    free(id);
    free(name);
    free(description);
    free(response);
}

void display_list_channel(info_t *info, char *team)
{
    char *buffer = malloc(sizeof(char) * 1024);
    FILE *filed;
    size_t bufs = 1024;
    char *id_team;

    filed = fopen("channel", "a+");
    memset(buffer, '\0', 1024);
    while (getline(&buffer, &bufs, filed) > 0) {
        id_team = get_param_file(buffer, 2, ';');
        if (strcmp(team, id_team) == 0) {
            display_list_channel_sec(info, buffer);
        }
        memset(buffer, '\0', 1024);
        free(id_team);
    }
    free(buffer);
    fclose(filed);
    write_communication(info->fd, LIST_FINISH);
}

void display_one_channel_sec(info_t *info, char *str, FILE *filed)
{
    char *response = malloc(sizeof(char) * 1024);

    response[sprintf(response, "%s%s;%s;%s\n", CHANNEL_DISPLAY,
    info->channel->id, info->channel->name,
    info->channel->description)] = 0;
    write_communication(info->fd, response);
    free(response);
    free(str);
    fclose(filed);
}

void display_one_channel(info_t *info, char *id_channel)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    size_t bufs = 1024;
    FILE *filed = fopen("channel", "a+");

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(id, id_channel) == 0) {
            display_one_channel_sec(info, str, filed);
            return;
        }
        memset(str, '\0', 1024);
        free(id);
    }
    free(str);
    write_communication(info->fd, CHAN_NOT_FOUND);
    fclose(filed);
}