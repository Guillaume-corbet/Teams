/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#include "client.h"


char *get_response(char *buffer, int fd)
{
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(fd, buffer);
    return (buffer);
}

char *get_list(char *buffer, int fd)
{
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(fd, buffer);
    while (strcmp(buffer, LIST_FINISH) != 0) {
        do_action_list(buffer);
        write_communication(fd, "OK\n");
        memset(buffer, '\0', 1024);
        while (strlen(buffer) < 1)
            buffer = new_read_communication(fd, buffer);
    }
    return (buffer);
}

int is_read(int fd)
{
    fd_set ensemble;
    struct timeval timeout;
    int ret = 0;

    timeout.tv_sec = 0;
    timeout.tv_usec = 1000;
    FD_ZERO(&ensemble);
    FD_SET(fd, &ensemble);
    ret = select(FD_SETSIZE, &ensemble, NULL, NULL, &timeout);
    if (ret == -1) {
        perror("select");
        return (FALSE);
    } else if (ret != 0)
        return (TRUE);
    return (FALSE);
}

char *main_s_read(int fd, char *buffer)
{
    buffer = get_command(buffer, fd);
    if (strcmp(buffer, "/users\n") == 0 ||
    strncmp(buffer, "/messages ", 10) == 0||
    strcmp(buffer, "/list\n") == 0 ||
    strncmp(buffer, "/subscribed", 11) == 0) {
        buffer = get_list(buffer, fd);
    } else {
        buffer = get_response(buffer, fd);
        do_action(buffer);
    }
    return (buffer);
}

int main(int argc, char **argv)
{
    int fd = 0;
    char *buffer = malloc(sizeof(char) * 1024);

    fd = create_connection(argv[1], argv[2]);
    memset(buffer, '\0', 1024);
    while (strlen(buffer) < 1)
        buffer = new_read_communication(fd, buffer);
    while (1) {
        if (print_response(buffer) == TRUE)
            return (0);
        if (is_read(0) == TRUE) {
            buffer = main_s_read(fd, buffer);
        } else if (is_read(fd) == TRUE) {
            buffer = read_communication(fd);
            do_action_notif(buffer);
            memset(buffer, '\0', 1024);
        }
    }
    return (0);
}