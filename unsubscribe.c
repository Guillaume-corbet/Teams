/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe
*/

#include "serveur.h"

char *read_file(char *buffer, int line)
{
    int j = 0;
    char *str = malloc(sizeof(char) * 1024);
    size_t buf = 1024;
    FILE *out = fopen("team_user", "r");

    memset(str, '\0', 1024);
    while (getline(&str, &buf, out) > 0) {
        if (j == 0)
            buffer = strcpy(buffer, str);
        else if (line != j)
            buffer = strcat(buffer, str);
        memset(str, '\0', 1024);
        j += 1;
    } fclose(out);
    free(str);
    return (buffer);
}

void rewrite_file(info_t *info, int line)
{
    int fd = 0;
    struct stat st;
    char *buffer;

    stat("team_user", &st);
    buffer = malloc(sizeof(char) * st.st_size + 1);
    memset(buffer, '\0', st.st_size);
    buffer = read_file(buffer, line);
    if ((fd = open("team_user", O_WRONLY | O_TRUNC)) == -1)
        perror("open marche aps");
    write(fd, buffer, strlen(buffer));
    close(fd);
    free(buffer);
}

int compare_param(info_t *info, char *str, char *buffer)
{
    char *tmp1;
    char *tmp2;

    tmp1 = get_param_file(str, 1, ';');
    tmp2 = get_param_file(str, 2, '\n');
    if (strcmp(tmp1, buffer) == 0 && strcmp(tmp2, info->user->id) == 0) {
        free(tmp1);
        free(tmp2);
        return (1);
    }
    free(tmp1);
    free(tmp2);
    return (0);
}

void unsubscribe_team_user(info_t *info, char *buffer)
{
    char *str = malloc(sizeof(char) * 1024);
    size_t bufs = 1024;
    FILE *filed = fopen("team_user", "r");
    int i = 0;

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        if (compare_param(info, str, buffer) == 1) {
            break;
        }
        i += 1;
        memset(str, '\0', 1024);
    }
    fclose(filed);
    rewrite_file(info, i);
    free(str);
}

void unsubscribe(info_t *info, char *buffer, rlist *list)
{
    char *team;
    char *response = malloc(sizeof(char) * 1024);

    team = get_param_buffer(buffer, 1);
    if (is_team_existing(team) == FALSE) {
        response[sprintf(response, "%s%s\n", TEAM_NOT_FOUND, team)] = 0;
        write_communication(info->fd, response);
    } else if (is_subscribe(info, team) == FALSE)
        write_communication(info->fd, UNAUTHORIZED);
    else {
        unsubscribe_team_user(info, team);
        server_event_user_leave_a_team(team, info->user->id);
        write_communication(info->fd,
        concat_str(UNSUB, info->user->id, team));
    }
    free(response);
    free(team);
}