/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team
*/

#include "serveur.h"


void display_team(info_t *info)
{
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    buffer = strcpy(buffer, info->team->id);
    buffer = strcat(buffer, ";");
    buffer = strcat(buffer, info->team->name);
    buffer = strcat(buffer, ";");
    buffer = strcat(buffer, info->team->description);
    buffer = strcat(buffer, "\n");
    write_communication(info->fd, buffer);
    free(buffer);
}

void team_null(info_t *info)
{
    if (info->team->id != NULL) {
        free(info->team->id);
        info->team->id = NULL;
    }
    if (info->team->name != NULL) {
        free(info->team->name);
        info->team->name = NULL;
    }
    if (info->team->description != NULL) {
        free(info->team->description);
        info->team->description = NULL;
    }
}

void create_team(info_t *info, char *id, char *name, char *description)
{
    FILE *filed;
    size_t bufs = 1024;
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    filed = fopen("team", "a+");
    if (getline(&buffer, &bufs, filed) > 0)
        fwrite("\n", 1, 1, filed);
    fwrite(id, 1, strlen(id), filed);
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

void send_notif_add_team(char *response, rlist *list)
{
    struct node *tmp = list->p_head;

    while (tmp) {
        if (tmp->info->user->id != NULL) {
            write_communication(tmp->info->fd, response);
        }
        tmp = tmp->p_next;
    }
}

void add_team(info_t *info, char *buffer, rlist *list)
{
    char *name;
    char *description;
    char *id;
    char *command = malloc(sizeof(char) * 1024);
    char *response = malloc(sizeof(char) * 1024);

    name = get_param_buffer(buffer, 1);
    description = get_param_buffer(buffer, 2);
    id = generate_uuid();
    server_event_team_created(id, name, info->user->id);
    command[sprintf(command, "/subscribe \"%s\"\n", id)] = 0;
    response[sprintf(response, "%s%s;%s;%s\n", TEAM_CREATED, id, name,
    description)] = 0;
    create_team(info, id, name, description);
    write_communication(info->fd, response);
    send_notif_add_team(response, list);
    subscribe(info, command, FALSE, list);
    free(command);
}