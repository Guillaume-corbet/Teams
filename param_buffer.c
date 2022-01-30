/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** param_buffer
*/

#include "serveur.h"

char *get_param_buffer(char *buffer, int nb)
{
    char *param = malloc(sizeof(char) * 1024);
    int i = 0;
    int j = 0;

    memset(param, '\0', 1024);
    while (nb > 0) {
        for (; buffer[i] != 34 && buffer[i] != '\0'; i++);
        i = i + 1;
        nb = nb - 1;
        if (nb > 0) {
            for (; buffer[i] != 34 && buffer[i] != '\0'; i++);
            i = i + 1;
        }
    }
    for (; buffer[i] != 34 && buffer[i] != '\0'; i++, j++)
        param[j] = buffer[i];
    param[j] = '\0';
    return (param);
}