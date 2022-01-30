/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread
*/

#include "serveur.h"


void display_list_thread(info_t *info, char *channel)
{
    char *buffer = malloc(sizeof(char) * 1024);
    FILE *filed;
    size_t bufs = 1024;
    char *id_channel;

    filed = fopen("thread", "a+");
    memset(buffer, '\0', 1024);
    while (getline(&buffer, &bufs, filed) > 0) {
        id_channel = get_param_file(buffer, 2, ';');
        if (strcmp(channel, id_channel) == 0) {
            display_list_thread_2(buffer, info);
        }
        memset(buffer, '\0', 1024);
        free(id_channel);
    }
    free(buffer);
    fclose(filed);
    write_communication(info->fd, LIST_FINISH);
}

void display_one_thread2(char *response, char *str, info_t *info)
{
    char *timestamp = get_param_file(str, 3, ';');
    char *creator = get_param_file(str, 6, '\n');

    response[sprintf(response, "%s%s;%s;%s;%s;%s\n", THREAD_DISPLAY,
    info->thread->id, creator, timestamp, info->thread->title,
    info->thread->body)] = 0;

    write_communication(info->fd, response);

    free(response);
    free(creator);
    free(timestamp);
    free(str);
}

void display_one_thread(info_t *info, char *id_thread)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    size_t bufs = 1024;
    FILE *filed = fopen("thread", "a+");
    char *response = malloc(sizeof(char) * 1024);
    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(id, id_thread) == 0) {
            display_one_thread2(response, str, info);
            fclose(filed);
            return;
        }
        memset(str, '\0', 1024);
        free(id);
    }
    free(response);
    free(str);
    write_communication(info->fd, THREAD_NOT_FOUND);
    fclose(filed);
}