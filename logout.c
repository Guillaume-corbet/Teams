/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** logout
*/

#include "serveur.h"

void end_write_file(char *buffer, FILE *filed, char *id)
{
    if (buffer[strlen(buffer) - 1] == '\n')
        fseek(filed, -2, SEEK_CUR);
    else
        fseek(filed, -1, SEEK_CUR);
    fwrite("0", 1, 1, filed);
    free(id);
    fclose(filed);
}

void put_zero_status(info_t *info, char *buffer, rlist *list)
{
    char *response = malloc(sizeof(char) * 1024);
    struct node *tmp = list->p_head;

    response = strcpy(response, USER_LOGGEDOUT);
    response = strcat(response, info->user->id);
    response = strcat(response, ";");
    response = strcat(response, info->user->name);
    response = strcat(response, "\n");
    write_communication(info->fd, response);
    while (tmp) {
        if (tmp->info->fd != info->fd)
            write_communication(tmp->info->fd, response);
        tmp = tmp->p_next;
    }
    free(response);
    server_event_user_logged_out(info->user->id);
}

void logout(info_t *info, char *buffer, rlist *list)
{
    size_t bufs = 1024;
    char *id;
    FILE *filed = fopen("user", "r+");

    memset(buffer, '\0', 1024);
    if (info->user->id == NULL) {
        fclose(filed);
        return;
    }
    while (getline(&buffer, &bufs, filed) > 0) {
        id = get_param_file(buffer, 1, ';');
        if (strcmp(info->user->id, id) == 0) {
            end_write_file(buffer, filed, id);
            put_zero_status(info, buffer, list);
            return;
        }
        memset(buffer, '\0', 1024);
        free(id);
    }
}