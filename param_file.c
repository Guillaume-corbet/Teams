/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** param_file
*/

#include "serveur.h"

char *get_param_file(char *buffer, int nb, char end)
{
    char *param = malloc(sizeof(char) * 1024);
    int i = 0;
    int j = 0;

    memset(param, '\0', 1024);
    while (nb > 1) {
        while (buffer[i] != ';' && buffer[i] != '\0')
            i = i + 1;
        i = i + 1;
        nb = nb - 1;
    }
    while (buffer[i] != end && buffer[i] != '\0') {
        param[j] = buffer[i];
        i = i + 1;
        j = j + 1;
    }
    param[j] = '\0';
    return (param);
}