/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread_create
*/

#include "serveur.h"

void thread_write(FILE *filed, char *buffer, char *title, char *body)
{
    fwrite(buffer, 1, strlen(buffer), filed);
    fwrite(";", 1, 1, filed);
    fwrite(title, 1, strlen(title), filed);
    fwrite(";", 1, 1, filed);
    fwrite(body, 1, strlen(body), filed);
    fwrite(";", 1, 1, filed);
}

void create_thread(info_t *info, char *id, char *title, char *body)
{
    FILE *filed;
    size_t bufs = 1024;
    char *buffer = malloc(sizeof(char) * 1024);

    memset(buffer, '\0', 1024);
    filed = fopen("thread", "a+");
    if (getline(&buffer, &bufs, filed) > 0)
        fwrite("\n", 1, 1, filed);
    memset(buffer, '\0', 1024);
    buffer = int_to_str(time(NULL));
    fwrite(id, 1, strlen(id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->channel->id, 1, strlen(info->channel->id), filed);
    fwrite(";", 1, 1, filed);
    thread_write(filed, buffer, title, body);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    fclose(filed);
    free(buffer);
}
