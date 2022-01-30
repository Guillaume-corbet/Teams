/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** gen_uuid
*/

#include "serveur.h"

char *generate_uuid(void)
{
    uuid_t uuid;
    char *buffer = malloc(sizeof(char) * 38);

    uuid_generate(uuid);
    uuid_unparse(uuid, buffer);
    return (buffer);
}