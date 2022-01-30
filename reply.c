/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** reply
*/

#include "serveur.h"

void create_reply(info_t *info, char *body, char *thread)
{
    FILE *filed;
    size_t bufs = 1024;
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    filed = fopen("reply", "a+");
    if (getline(&buffer, &bufs, filed) > 0)
        fwrite("\n", 1, 1, filed);
    memset(buffer, '\0', 1024);
    buffer = int_to_str(time(NULL));
    fwrite(thread, 1, strlen(thread), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->team->id, 1, strlen(info->team->id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(buffer, 1, strlen(buffer), filed);
    fwrite(";", 1, 1, filed);
    fwrite(body, 1, strlen(body), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    fclose(filed);
    free(buffer);
}

void add_first_reply(info_t *info, char *buffer, char *thread)
{
    char *body;
    char *timestamp = malloc(sizeof(char) * 1024);

    body = get_param_buffer(buffer, 1);
    timestamp = int_to_str(time(NULL));
    create_reply(info, body, thread);
    free(body);
    free(timestamp);
}

void add_reply(info_t *info, char *buffer, rlist *list)
{
    char *body;
    char *timestamp = malloc(sizeof(char) * 1024);
    char *response = malloc(sizeof(char) * 1024);
    struct node *tmp = list->p_head;

    body = get_param_buffer(buffer, 1);
    timestamp = int_to_str(time(NULL));
    create_reply(info, body, info->thread->id);
    response[sprintf(response, "%s%s;%s;%s;%s\n", REPLY_CREATED,
    info->thread->id, info->user->id, timestamp, body)] = 0;
    server_event_thread_new_message(info->thread->id, info->user->id, body);
    free(body);
    free(timestamp);
    write_communication(info->fd, response);
    while (tmp) {
        if (tmp->info->user->id != NULL && tmp->info->fd != info->fd)
            write_communication(tmp->info->fd, response);
        tmp = tmp->p_next;
    }
    free(response);
}