/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** channel_sodomie
*/

#include "serveur.h"

void display_channel(info_t *info)
{
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    buffer = strcpy(buffer, info->channel->id);
    buffer = strcat(buffer, ";");
    buffer = strcat(buffer, info->team->id);
    buffer = strcat(buffer, ";");
    buffer = strcat(buffer, info->channel->name);
    buffer = strcat(buffer, ";");
    buffer = strcat(buffer, info->channel->description);
    buffer = strcat(buffer, "\n");
    write_communication(info->fd, buffer);
    free(buffer);
}

void create_channel(info_t *info, char *id, char *name, char *description)
{
    FILE *filed;
    size_t bufs = 1024;
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    filed = fopen("channel", "a+");
    if (getline(&buffer, &bufs, filed) > 0)
        fwrite("\n", 1, 1, filed);
    fwrite(id, 1, strlen(id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->team->id, 1, strlen(info->team->id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(name, 1, strlen(name), filed);
    fwrite(";", 1, 1, filed);
    fwrite(description, 1, strlen(description), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    fclose(filed);
    free(id);
    free(name);
    free(description);
}

void add_channel(info_t *info, char *buffer, rlist *list)
{
    char *name;
    char *description;
    char *id;
    char *response = malloc(sizeof(char) * 1024);
    struct node *tmp = list->p_head;

    name = get_param_buffer(buffer, 1);
    description = get_param_buffer(buffer, 2);
    id = generate_uuid();
    response[sprintf(response, "%s%s;%s;%s\n", CHAN_CREATED, id, name,
    description)] = 0;
    server_event_channel_created(info->team->id, id, name);
    while (tmp) {
        if (tmp->info->user->id != NULL && tmp->info->fd != info->fd &&
            is_user_subscribe(tmp->info->user->id, info->team->id) == TRUE)
            write_communication(tmp->info->fd, response);
        tmp = tmp->p_next;
    }
    create_channel(info, id, name, description);
    write_communication(info->fd, response);
    free(response);
}

void set_value(info_t *info, char *id, char *str, FILE *filed)
{
    char *name = get_param_file(str, 3, ';');
    char *description = get_param_file(str, 4, ';');
    info->channel->id = strdup(id);
    info->channel->name = strdup(name);
    info->channel->description = strdup(description);
    free(name);
    free(description);
    free(str);
    fclose(filed);
}

void set_channel(info_t *info, char *id_channel)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    size_t bufs = 1024;
    FILE *filed = fopen("channel", "a+");

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(id, id_channel) == 0) {
            set_value(info, id, str, filed);
            return;
        } memset(str, '\0', 1024);
        free(id);
    } free(str);
    fclose(filed);
}