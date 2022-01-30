/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** command
*/

#include "serveur.h"

int check_if_connect(info_t *info, char *buffer, rlist *list)
{
    if (info->user->name != NULL)
        return (do_action(info, buffer, list));
    else if (strcmp("/logout\n", buffer) == 0) {
        logout(info, buffer, list);
        return (84);
    } else if (strcmp("/help\n", buffer) == 0) {
        help(info, NULL, list);
    }
    return (1);
}

char *login(info_t *info, char *buffer, rlist *list)
{
    char *response = malloc(sizeof(char) * 1024);
    struct node *tmp = list->p_head;

    buffer = get_param_buffer(buffer, 1);
    info->user->name = strdup(buffer);
    check_user(info);
    response = strcpy(response, USER_LOGGEDIN);
    response = strcat(response, info->user->id);
    response = strcat(response, ";");
    response = strcat(response, info->user->name);
    response = strcat(response, "\n");
    write_communication(info->fd, response);
    while (tmp) {
        if (tmp->info->fd != info->fd && tmp->info->user->id != NULL)
            write_communication(tmp->info->fd, response);
        tmp = tmp->p_next;
    }
    free(response);
    return (buffer);
}

int make_command(info_t *info, char *buffer, rlist *list)
{
    int ret = 0;
    int j = 0;
    struct node *tmp = list->p_head;

    if ((ret = check_if_connect(info, buffer, list)) != 1) {
        return (ret);
    } if (strncmp(buffer, "/login ", 7) == 0 && strlen(buffer) > 7) {
        buffer = login(info, buffer, list);
    } else {
        write_communication(info->fd, UNAUTHORIZED);
    }
    memset(buffer, '\0', 1024);
    return (0);
}

char *check_if_command_error(int ret, struct node *tmp, char *buffer)
{
    if (ret == -1) {
        perror("select");
    } else if (ret != 0) {
        memset(buffer, '\0', 1024);
        buffer = new_read_communication(tmp->info->fd, buffer);
        return (buffer);
    }
    return (buffer);
}

rlist *check_if_command(rlist *list)
{
    int ret = 0;
    struct node *tmp = list->p_head;
    char *buffer = malloc(sizeof(char) * 1024);

    while (tmp) {
        ret = check_select_read(tmp);
        buffer = check_if_command_error(ret, tmp, buffer);
        if (ret > 0 && make_command(tmp->info, buffer, list) == 84) {
            list = remove_client(list, tmp);
            return (list);
        }
        if (list == NULL)
            break;
        tmp = tmp->p_next;
    }
    free(buffer);
    return (list);
}