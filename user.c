/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "serveur.h"

char *display_user_read(char *response, char *buffer, FILE *filed)
{
    char *str = malloc(sizeof(char) * 1024);
    size_t bufs = 1024;

    while (getline(&str, &bufs, filed) > 0) {
        if (is_good_user(buffer, str) == 0) {
            display_user_read_end_line(str);
            response = strcpy(response, USER_DISPLAY);
            response = strcat(response, str);
            free(str);
            return (response);
        }
        memset(str, '\0', 1024);
    }
    free(str);
    response[0] = 0;
    return (response);
}

void display_user(info_t *info, char *buffer, rlist *list)
{
    FILE *filed;
    char *response = malloc(sizeof(char) * 1024);
    char *id = NULL;
    int error = 0;

    filed = fopen("user", "r");
    response = display_user_read(response, buffer, filed);
    if (response[0] == 0) {
        id = get_param_buffer(buffer, 1);
        response[sprintf(response, "%s%s\n", USER_NOT_FOUND, id)] = 0;
    }
    write_communication(info->fd, response);
    free(response);
    if (id != NULL)
        free(id);
    fclose(filed);
}

void create_user(info_t *info, int empty, FILE *filed, int fd)
{
    info->user->id = generate_uuid();
    info->user->status = 1;
    if (empty == 0)
        fwrite("\n", 1, 1, filed);
    fwrite(info->user->id, 1, strlen(info->user->id), filed);
    fwrite(";", 1, 1, filed);
    fwrite(info->user->name, 1, strlen(info->user->name), filed);
    fwrite(";1", 1, 2, filed);
    fclose(filed);
    close(fd);
    server_event_user_created(info->user->id, info->user->name);
    server_event_user_logged_in(info->user->id);
}

void load_user(info_t *info, char *buffer, FILE *filed, int fd)
{
    char *id;
    char *name;

    id = get_param_file(buffer, 1, ';');
    name = get_param_file(buffer, 2, ';');
    info->user->id = strdup(id);
    info->user->status = 1;
    if (buffer[strlen(buffer) - 1] == '\n')
        fseek(filed, -2, SEEK_CUR);
    else
        fseek(filed, -1, SEEK_CUR);
    fwrite("1", 1, 1, filed);
    fclose(filed);
    close(fd);
    free(buffer);
    free(name);
    free(id);
    server_event_user_loaded(info->user->id, info->user->name);
    server_event_user_logged_in(info->user->id);
}

int check_user(info_t *info)
{
    char *buffer = malloc(sizeof(char) * 1024);
    size_t bufs = 1024;
    char *name;
    int empty = 1;
    int fd = open("user", O_RDWR | O_CREAT, 0666);
    FILE *filed = fdopen(fd, "r+");

    while (getline(&buffer, &bufs, filed) > 0) {
        empty = 0;
        name = get_param_file(buffer, 2, ';');
        if (strcmp(info->user->name, name) == 0) {
            load_user(info, buffer, filed, fd);
            free(name);
            return (0);
        }
        memset(buffer, '\0', 1024);
        free(name);
    }
    free(buffer);
    create_user(info, empty, filed, fd);
    return (0);
}