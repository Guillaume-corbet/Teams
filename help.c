/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "serveur.h"

void help(info_t *info, char *buf, rlist *list)
{
    write_communication(info->fd, HELP);
}