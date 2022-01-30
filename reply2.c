/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** reply
*/

#include "serveur.h"

void get_response_list_reply(info_t *info, char *buffer)
{
    char *response = malloc(sizeof(char) * 1024);
    char *id;
    char *creator;
    char *timestamp;
    char *body;

    id = get_param_file(buffer, 1, ';');
    creator = get_param_file(buffer, 5, '\n');
    timestamp = get_param_file(buffer, 3, ';');
    body = get_param_file(buffer, 4, ';');
    response = malloc(sizeof(char) * 1024);
    response[sprintf(response, "%s%s;%s;%s;%s\n", REPLY_DISPLAY,
    id, creator, timestamp, body)] = 0;
    free(id);
    free(creator);
    free(timestamp);
    free(body);
    write_communication(info->fd, response);
    free(response);
    return;
}

char *get_buffer_list_reply(info_t *info, char *buffer)
{
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(info->fd, buffer);
    return (buffer);
}

void display_list_reply(info_t *info, char *thread)
{
    char *buffer = malloc(sizeof(char) * 1024);
    FILE *filed;
    size_t bufs = 1024;
    char *id_thread;

    filed = fopen("reply", "a+");
    while (getline(&buffer, &bufs, filed) > 0) {
        id_thread = get_param_file(buffer, 1, ';');
        if (strcmp(thread, id_thread) == 0) {
            get_response_list_reply(info, buffer);
            buffer = get_buffer_list_reply(info, buffer);
        }
        memset(buffer, '\0', 1024);
        free(id_thread);
    }
    free(buffer);
    fclose(filed);
    write_communication(info->fd, LIST_FINISH);
}