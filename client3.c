/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#include "client.h"

void log_notif_message(char *buffer)
{
    char *id = get_param_file(buffer, 2, ';');
    char *message = get_param_file(buffer, 3, '\n');

    client_event_private_message_received(id, message);
    free(id);
    free(message);
}

void log_notif_thread_message(char *buffer)
{
    char *team = get_param_file(buffer, 2, ';');
    char *thread = get_param_file(buffer, 3, ';');
    char *user = get_param_file(buffer, 4, ';');
    char *message = get_param_file(buffer, 5, '\n');

    client_event_thread_message_received(team, thread, user, message);
    free(team);
    free(thread);
    free(user);
    free(message);
}

struct tab function_notif[] =
{
    {"2 ", &log_notif_login},
    {"3 ", &log_notif_logout},
    {"9 ", &log_notif_channel_created},
    {"12", &log_notif_message},
    {"13", &log_notif_thread_message},
    {"18", &log_notif_team_created},
    {"23", &log_notif_thread_created}
};

int do_action_notif(char *buffer)
{
    int find = -1;

    for (int i = 0; i < 7; i += 1) {
        if (strncmp(buffer, function_notif[i].str, 2) == 0)
            find = i;
    } if (find != -1) {
        function_notif[find].func(buffer);
        return (TRUE);
    } else
        return (FALSE);

    return (0);
}

int print_response(char *buffer)
{
    if (strncmp(buffer, USER_LOGGEDOUT, strlen(USER_LOGGEDOUT)) == 0)
        return (TRUE);
    return (FALSE);
}

int create_connection(char *str_host, char *str_port)
{
    struct sockaddr_in addr;
    struct sockaddr addrRet;
    int len = sizeof(addr);
    int fd = 0;
    int port = 0;

    port = my_getnbr(str_port);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        perror("socket");
    memset((char*)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(str_host);
    addr.sin_port = htons((unsigned short)port);
    memcpy((char *)&addrRet, (char *)&addr, sizeof(addrRet));
    if (connect(fd, &addrRet, sizeof(addrRet)) != 0)
        perror("connect");
    return (fd);
}
