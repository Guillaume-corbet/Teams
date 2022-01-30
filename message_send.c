/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_send
*/

#include "serveur.h"

void send_notif_private_message(rlist *list, char *id, char *response)
{
    struct node *tmp = list->p_head;

    while (tmp) {
        if (tmp->info->user->id != NULL &&
        strcmp(tmp->info->user->id, id) == 0) {
            write_communication(tmp->info->fd, response);
            break;
        }
        tmp = tmp->p_next;
    }
    free(id);
}

void create_private_message(info_t *info, char *buffer, rlist *list)
{
    char *message = malloc(sizeof(char) * 1024);
    char *id;
    char *timestamp = int_to_str(time(NULL));
    FILE *filed;
    char *response = malloc(sizeof(char) * 1024);

    id = get_param_buffer(buffer, 1);
    message = get_param_buffer(buffer, 2);
    filed = fopen("message", "a+");
    create_message(info, id, timestamp, filed);
    fwrite(message, 1, strlen(message), filed);
    fclose(filed);
    server_event_private_message_sended(info->user->id, id, message);
    free(timestamp);
    write_communication(info->fd, MESSAGE_SEND);
    response[sprintf(response, "%s%s;%s", MESSAGE_SEND,
    info->user->id, message)] = 0;
    send_notif_private_message(list, id, response);
    free(message);
}

void create_message(info_t *info, char *id, char *timestamp, FILE *filed)
{
    char *buffer = malloc(sizeof(char) * 1024);
    size_t bufs = 1024;

    memset(buffer, '\0', 1024);
    if (getline(&buffer, &bufs, filed) > 0)
        fwrite("\n", 1, 1, filed);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(id, 1, strlen(id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(timestamp, 1, strlen(timestamp), filed);
    fwrite(";", 1, 1, filed);
}