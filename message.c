/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message
*/

#include "serveur.h"

char *get_id_list_message(char *buffer)
{
    int i = 0;
    int j = 0;
    char *id = malloc(sizeof(char) * 1024);

    memset(id, '\0', 1024);
    while (buffer[i] != ' ' && buffer[i] != '\0')
        i = i + 1;
    i = i + 1;
    while (buffer[i] != '\n' && buffer[i] != '\0') {
        id[j] = buffer[i];
        i = i + 1;
        j = j + 1;
    }
    id[j] = '\0';
    return (id);
}

int is_good_message(info_t *info, char *first, char *second, char *buffer)
{
    if (strcmp(info->user->id, first) == 0 && strcmp(buffer, second) == 0)
        return (0);
    else if (strcmp(info->user->id, second) == 0 && strcmp(buffer, first) == 0)
        return (0);
    return (1);
}

char *send_one_message_list(info_t *info, char *str)
{
    char *response = malloc(sizeof(char) * 1024);
    char *sender;
    char *timestamp;
    char *message;

    sender = get_param_file(str, 1, ';');
    timestamp = get_param_file(str, 3, ';');
    message = get_param_file(str, 4, '\n');
    response[sprintf(response, "%s%s;%s;%s\n", MESSAGE_DISPLAY, sender,
    timestamp, message)] = 0;
    write_communication(info->fd, response);
    memset(str, '\0', 1024);
    while (strlen(str) < 1)
        str = new_read_communication(info->fd, str);
    free(response);
    free(sender);
    free(timestamp);
    free(message);
    return (str);
}

void end_list_message(info_t *info, char *str, char *id, FILE *filed)
{
    write_communication(info->fd, LIST_FINISH);
    free(str);
    free(id);
    fclose(filed);
}

void display_list_message(info_t *info, char *buffer, rlist *list)
{
    char *str = malloc(sizeof(char) * 1024);
    char *first;
    char *second;
    char *id;
    FILE *filed = fopen("message", "a+");
    size_t bufs = 1024;

    memset(str, '\0', 1024);
    id = get_param_buffer(buffer, 1);
    while (getline(&str, &bufs, filed) > 0) {
        first = get_param_file(str, 1, ';');
        second = get_param_file(str, 2, ';');
        if (is_good_message(info, first, second, id) == 0) {
            str = send_one_message_list(info, str);
        }
        memset(str, '\0', 1024);
        free(first);
        free(second);
    }
    end_list_message(info, str, id, filed);
}