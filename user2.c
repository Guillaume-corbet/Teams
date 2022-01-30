/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user
*/

#include "serveur.h"

int is_good_user(char *buffer, char *str)
{
    char *first = malloc(sizeof(char) * 1024);
    char *second = malloc(sizeof(char) * 1024);
    int i = 0;
    int ret = 0;

    first = get_param_buffer(buffer, 1);
    while (str[i] != ';' && str[i] != '\0') {
        second[i] = str[i];
        i = i + 1;
    }
    second[i] = '\0';
    ret = strcmp(first, second);
    return (ret);
}

void display_user_read_end_line(char *str)
{
    if (str[strlen(str) - 1] != '\n')
        str[strlen(str)] = '\n';
}