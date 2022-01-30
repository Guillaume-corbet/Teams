/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** int_to_str
*/

#include "serveur.h"

char *int_to_str(int nb)
{
    int a = 0;
    char *str;

    str = malloc(sizeof(char) * 11);
    memset(str, '\0', 11);
    while (nb > 0) {
        str[a] = (nb % 10) + 48;
        nb = nb / 10;
        a = a + 1;
    }
    str[a] = '\0';
    str = my_revstr(str);
    return (str);
}