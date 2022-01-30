/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** inic
*/

#include "serveur.h"

user_t *init_struct_user(void)
{
    user_t *user = malloc(sizeof(user_t));

    if (user == NULL)
        return (NULL);
    user->id = NULL;
    user->name = NULL;
    user->status = 0;
    return (user);
}

team_t *init_struct_team(void)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return (NULL);
    team->description = NULL;
    team->id = NULL;
    team->name = NULL;
    return (team);
}

channel_t *init_struct_channel(void)
{
    channel_t *channel = malloc(sizeof(channel_t));

    if (channel == NULL)
        return (NULL);
    channel->description = NULL;
    channel->id = NULL;
    channel->name = NULL;
    return (channel);
}

thread_t *init_struct_thread(void)
{
    thread_t *thread = malloc(sizeof(thread_t));

    if (thread == NULL)
        return (NULL);
    thread->id = NULL;
    thread->title = NULL;
    thread->body = NULL;
}

info_t *init_struct_info(int fd)
{
    info_t *info = malloc(sizeof(info_t));

    if (info == NULL)
        return (NULL);
    info->fd = fd;
    info->user = init_struct_user();
    if (info->user == NULL)
        return (NULL);
    info->team = init_struct_team();
    if (info->team == NULL)
        return (NULL);
    info->channel = init_struct_channel();
    if (info->channel == NULL)
        return (NULL);
    info->thread = init_struct_thread();
    if (info->thread == NULL)
        return (NULL);
    return (info);
}