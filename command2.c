/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** command
*/

#include "serveur.h"

void command_info(info_t *info, char *buffer, rlist *list)
{
    char *str = malloc(sizeof(char) * 1024);

    memset(str, '\0', 1024);
    if (info->team->id == NULL) {
        str = strcpy(str, "/user \"");
        str = strcat(str, info->user->id);
        str = strcat(str, "\"\n");
        display_user(info, str, list);
    } else if (info->channel->id == NULL) {
        display_one_team(info, info->team->id);
    } else if (info->thread->id == NULL) {
        display_one_channel(info, info->channel->id);
    } else {
        display_one_thread(info, info->thread->id);
    }
}

void command_list(info_t *info, char *buffer, rlist *list)
{
    if (info->team->id == NULL) {
        display_list_team(info);
    } else if (info->channel->id == NULL) {
        display_list_channel(info, info->team->id);
    } else if (info->thread->id == NULL) {
        display_list_thread(info, info->channel->id);
    } else {
        display_list_reply(info, info->thread->id);
    }
}

void command_use(info_t *info, char *buffer, rlist *list)
{
    if (strcmp("/use\n", buffer) == 0) {
        thread_null(info);
        channel_null(info);
        team_null(info);
        write_communication(info->fd, USE_ZERO);
    } else
        use(info, buffer);
}

void command_create(info_t *info, char *buffer, rlist *list)
{
    if (info->team->id == NULL) {
        add_team(info, buffer, list);
    } else if (info->channel->id == NULL) {
        add_channel(info, buffer, list);
    } else if (info->thread->id == NULL) {
        add_thread(info, buffer, list);
    } else {
        add_reply(info, buffer, list);
    }
}

struct tab function[] =
{
    {"/logout\n", &logout},
    {"/help\n", &help},
    {"/users\n", &display_list_user},
    {"/user ", &display_user},
    {"/messages ", &display_list_message},
    {"/send ", &create_private_message},
    {"/info\n", &command_info},
    {"/list\n", &command_list},
    {"/use\n", &command_use},
    {"/use ", &command_use},
    {"/create ", &command_create},
    {"/subscribed", &subscribed},
    {"/unsubscribe ", &unsubscribe}
};

int do_action(info_t *info, char *buffer, rlist *list)
{
    int find = -1;

    if (strcmp("/logout\n", buffer) == 0) {
        logout(info, buffer, list);
        return (84);
    } else if (strncmp("/subscribe ", buffer, 11) == 0) {
        subscribe(info, buffer, TRUE, list);
        return (0);
    } for (int i = 0; i < 13; i += 1) {
        if (strncmp(buffer, function[i].str, strlen(function[i].str)) == 0)
            find = i;
    } if (find == -1) {
        write_communication(info->fd, SYNTAX);
        return (0);
    } else {
        function[find].func(info, buffer, list);
    }
    return (0);
}