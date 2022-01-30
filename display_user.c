/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** display_user
*/

#include "serveur.h"

char *display_list_set(info_t *info, char *buffer)
{
    char *response;
    if (buffer[strlen(buffer) - 1] != '\n')
        buffer[strlen(buffer)] = '\n';
    response = malloc(sizeof(char) * 1024);
    response = strcpy(response, USER_DISPLAY);
    response = strcat(response, buffer);
    write_communication(info->fd, response);
    memset(buffer, '\0', 1024);
    free(response);
    return (buffer);
}

void display_list_user(info_t *info, char *buf, rlist *list)
{
    char *buffer = malloc(sizeof(char) * 1024);
    FILE *filed;
    size_t bufs = 1024;

    memset(buffer, '\0', 1024);
    filed = fopen("user", "r");
    while (getline(&buffer, &bufs, filed) > 0) {
        buffer = display_list_set(info, buffer);
        while (strlen(buffer) < 1)
            buffer = new_read_communication(info->fd, buffer);
        if (strlen(buffer) < 2)
            my_putstr("error\n");
        memset(buffer, '\0', 1024);
    }
    write_communication(info->fd, LIST_FINISH);
    free(buffer);
    fclose(filed);
}