/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** useful_func
*/

#include "serveur.h"

char *concat_str(char *src1, char *src2, char *src3)
{
    int i = (strlen(src1)
    + strlen(src2)
    + strlen(src3));
    char *dest = malloc(sizeof(char) * i + 1);

    dest[sprintf(dest, "%s%s;%s\n", src1, src2, src3)] = 0;

    return (dest);
}