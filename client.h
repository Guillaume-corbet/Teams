/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include "lib/myteams/logging_client.h"

// man socket
#include <sys/types.h>
#include <sys/socket.h>
// man ip
#include <netinet/in.h>
#include <netinet/ip.h>
// man select
#include <sys/select.h>
//lib
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
//opendir
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
//lib
#include "lib/my/my.h"

#define STR (str[i] != '\0')

struct tab
{
    char *str;
    void (*func)(char *buf);
};

#define CONNECTION_SERVEUR "1 Service ready for new user;\n"
#define USER_LOGGEDIN "2 User connected;"
#define USER_LOGGEDOUT "3 User disconnected;"
#define HELP "4 /help, /login, /user, /users, /logout, /messages\
, /send, /list, /use, /create, /info, /subscribe;\n"
#define COMMAND_GOOD "5 Command okay.;\n"
#define SYNTAX "6 Syntax error, command unrecognized and the requested \
action did not take place.;\n"
#define USER_NOT_FOUND "7 User not found;"
#define CHAN_NOT_FOUND "8 Channel not found;"
#define CHAN_CREATED "9 Channel created;"
#define CHAN_NOT_IN_TEAMS "10 Channel not in this team;\n"
#define USE_ZERO "11 Remise a zero use;\n"
#define MESSAGE_SEND "12 Message envoyé;\n"
#define REPLY "13 Reply created;"
#define ALREADY_SUB "14 Already subscribe;\n"
#define TEAM_SUB "15 Team subscribe;"
#define TEAM_NOT_SUB "16 Team not subscribe;"
#define TEAM_NOT_FOUND "17 Team not found;"
#define TEAM_CREATED "18 Team created;"
#define NOT_SUB "19 Not subscibed;\n"
#define UNSUB "20 Unsubscribed;"
#define THREAD_NOT_IN_TEAM "21 Thread not in this channel;\n"
#define THREAD_NOT_FOUND "22 Thread not found;"
#define THREAD_CREATED "23 Thread created;"
#define USE_OK "24 Use okay;\n" 
#define NOT_LOGGED "25 Not logged in.;\n"
#define LIST_FINISH "26 List finish;\n"
#define USER_DISPLAY "27 Display user;"
#define THREAD_DISPLAY "28 Display thread;"
#define CHANNEL_DISPLAY "29 Display channel;"
#define TEAM_DISPLAY "30 Display team;"
#define REPLY_DISPLAY "31 Display reply;"
#define MESSAGE_DISPLAY "32 Display message;"
#define UNAUTHORIZED "33 Unauthorized command\n"
#define REPLY_CREATED "34 Reply created;"
#define TRUE 0
#define FALSE 1



int do_action(char *buffer);

/* client.c */

void log_notif_login(char *buffer);
void log_notif_logout(char *buffer);
void log_notif_channel_created(char *buffer);
void log_notif_team_created(char *buffer);
void log_notif_thread_created(char *buffer);
void log_notif_message(char *buffer);
void log_notif_thread_message(char *buffer);
int do_action_notif(char *buffer);
int print_response(char *buffer);
int create_connection(char *str_host, char *str_port);

/* param_file.c */

char *get_param_file(char *buffer, int nb, char end);

/* communicate.c */

char *read_communication(int fd);
int write_communication(int fd, char *buffer);
char *new_read_communication(int fd, char *buffer);

/* client_log_unknown.c */

void log_unknown_chan(char *buffer);
void log_unknown_user(char *buffer);
void log_unknown_team(char *buffer);
void log_unknown_thread(char *buffer);

/* client_log_created.c */

void log_print_channel_created(char *buffer);
void log_print_reply_created(char *buffer);
void log_print_team_created(char *buffer);
void log_print_thread_created(char *buffer);

/* client_log_prints.c */

void log_print_channels(char *buffer);
void log_print_teams(char *buffer);
void log_print_replies(char *buffer);
void log_print_messages(char *buffer);
void log_print_threads(char *buffer);

/* client_log_print.c */

void log_print_thread(char *buffer);
void log_print_channel(char *buffer);
void log_print_team(char *buffer);

/* client_log_user.c */

void log_print_user(char *buffer);
void log_print_users(char *buffer);
void log_login(char *buffer);
void log_logout(char *buffer);

/* client_log_subscribe.c */

void log_print_already_exist(char *buffer);
void log_print_subscribed(char *buffer);
void log_unauthorized(char *buffer);
void log_print_unsubscribed(char *buffer);

/* client_command.c */

int do_action_list(char *buffer);
int do_action(char *buffer);
char *get_command(char *buffer, int fd);

#endif /* !CLIENT_H_ */