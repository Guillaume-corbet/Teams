/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** free
*/

#include "serveur.h"

void free_user(user_t *user)
{
    free(user->id);
    free(user->name);
    free(user);
}

void free_info(info_t *info)
{
    free_user(info->user);
    free(info);
}