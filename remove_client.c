/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** remove_client
*/

#include "serveur.h"

rlist *remove_client(rlist *list, struct node *tmp)
{
    close(tmp->info->fd);
    list = remove_element(list, tmp);
    return (list);
}