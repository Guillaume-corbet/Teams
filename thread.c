/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread
*/

#include "serveur.h"

void thread_null(info_t *info)
{
    if (info->thread->body != NULL) {
        free(info->thread->body);
        info->thread->body = NULL;
    }
    if (info->thread->id != NULL) {
        free(info->thread->id);
        info->thread->id = NULL;
    }
    if (info->thread->title != NULL) {
        free(info->thread->title);
        info->thread->title = NULL;
    }
}

int is_thread_existing(char *thread)
{
    char *id;
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("thread", "a+");
    size_t bufs = 1024;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(thread, id) == 0) {
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

int is_thread_channel_id(char *thread, char *channel, char *str, int ret)
{
    char *id;
    id = get_param_file(str, 1, ';');
    if (strcmp(thread, id) == 0) {
        free(id);
        id = get_param_file(str, 2, ';');
        if (strcmp(channel, id) == 0)
            return (TRUE);
    }
    memset(str, '\0', 1024);
    free(id);
    return (ret);
}

int is_thread_channel(char *thread, char *channel)
{
    char *str = malloc(sizeof(char) * 1024);
    FILE *filed = fopen("thread", "a+");
    size_t bufs = 1024;
    int ret = FALSE;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        ret = is_thread_channel_id(thread, channel, str, ret);
    }
    free(str);
    fclose(filed);
    return (ret);
}

void display_list_thread_2(char *buffer, info_t *info)
{
    char *id = get_param_file(buffer, 1, ';');
    char *creator = get_param_file(buffer, 6, '\n');
    char *timestamp = get_param_file(buffer, 3, ';');
    char *title = get_param_file(buffer, 4, ';');
    char *body = get_param_file(buffer, 5, ';');
    char *response = malloc(sizeof(char) * 1024);
    response[sprintf(response, "%s%s;%s;%s;%s;%s\n", THREAD_DISPLAY,
    id, creator, timestamp, title, body)] = 0;
    write_communication(info->fd, response);
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(info->fd, buffer);
    free(id);
    free(creator);
    free(timestamp);
    free(title);
    free(body);
    free(response);
}
