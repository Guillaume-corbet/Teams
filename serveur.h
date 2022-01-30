/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** serveur
*/

#ifndef SERVEUR_H_
#define SERVEUR_H_

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
//uuid
#include <uuid/uuid.h>

#include "lib/myteams/logging_server.h"
#include "lib/my/my.h"

#define STR (str[i] != '\0')

typedef struct t_user
{
    char *id;
    char *name;
    int status;
}user_t;

typedef struct t_team
{
    char *id;
    char *name;
    char *description;
}team_t;

typedef struct t_channel
{
    char *id;
    char *name;
    char *description;
}channel_t;

typedef struct t_thread
{
    char *id;
    char *title;
    char *body;
}thread_t;

typedef struct t_info
{
    int fd;
    user_t *user;
    team_t *team;
    channel_t *channel;
    thread_t *thread;
}info_t;

struct node
{
    info_t *info;
    struct node *p_next;
    struct node *p_prev;
};

typedef struct dlist
{
    size_t length;
    struct node *p_tail;
    struct node *p_head;
}rlist;

struct tab
{
    char *str;
    void (*func)(info_t *info, char *buf, rlist *list);
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

#ifndef INC_
#define INC_

/* remove_client.c */

rlist *remove_client(rlist *list, struct node *tmp);

/* logout.c */

void logout(info_t *info, char *buffer, rlist *list);

/* serveur.c */

int check_select_read(struct node *tmp);
int serveur(int port);
int main(int argc, char **argv);

/* add_to_list.c */

rlist *dlist_new(struct node *new);
struct node *init_node(info_t *info);
struct node *add_node_end(info_t *info, struct node *old);
void add_element(struct node *new, rlist *p_list);
rlist *remove_element(rlist *p_list, struct node *tmp);

/* channel.c / channel_func.c */

int is_channel_team_verif_id(char *team, char *channel, char *str, FILE *filed);
int is_channel_existing(char *channel);
int is_channel_team(char *channel, char *team);
void display_list_channel(info_t *info, char *team);
void display_channel(info_t *info);
void add_channel(info_t *info, char *buffer, rlist *list);
void channel_null(info_t *info);
void display_one_channel(info_t *info, char *id_channel);
void set_channel(info_t *info, char *id_channel);

/* thread.c */

void display_one_thread2(char *response, char *str, info_t *info);
int is_thread_channel_id(char *thread, char *channel, char *str, int ret);
void display_list_thread_2(char *buffer, info_t *info);
void thread_write(FILE *filed, char *buffer, char *title, char *body);
void thread_free(char *title, char *body, char *response, char *id);
char *norm_add_thread(info_t *info, char *id, char *title, char *body);
void set_thread_sec(info_t *info, char *title, char *body, char *str);
void thread_null(info_t *info);
int is_thread_existing(char *thread);
int is_thread_channel(char *thread, char *channel);
void display_list_thread(info_t *info, char *channel);
void display_one_thread(info_t *info, char *id_thread);
void create_thread(info_t *info, char *id, char *title, char *body);
void add_thread(info_t *info, char *buffer, rlist *list);
void set_thread(info_t *info, char *id_thread);

/* reply.c */

void get_response_list_reply(info_t *info, char *buffer);
char *get_buffer_list_reply(info_t *info, char *buffer);
void display_list_reply(info_t *info, char *thread);
void create_reply(info_t *info, char *body, char *thread);
void add_first_reply(info_t *info, char *buffer, char *thread);
void add_reply(info_t *info, char *buffer, rlist *list);

/* help.c */

void help(info_t *info, char *buf, rlist *list);

/* help_tab.c */

void display_tab(char **tab);
int length_tab(char **tab);
void free_tab(char **tab);

/* communicate.c */

char *new_read_communication(int fd, char *buffer);
char *read_communication(int fd);
int write_communication(int fd, char *buffer);

/* inic.c */

info_t *init_struct_info(int fd);
int init_server(struct sockaddr_in addr);

/* int_to_str.c */

char *int_to_str(int nb);

/* add_client.c */

int is_new_client(int fd);
rlist *add_client(int fd, struct sockaddr_in addr, rlist *list);

/* command.c */

int do_action(info_t *info, char *buffer, rlist *list);
char *check_if_command_error(int ret, struct node *tmp, char *buffer);
char *login(info_t *info, char *buffer, rlist *list);
void command_info(info_t *info, char *buffer, rlist *list);
void command_list(info_t *info, char *buffer, rlist *list);
void command_create(info_t *info, char *buffer, rlist *list);
void command_use(info_t *info, char *buffer, rlist *list);
int connect_command_first(info_t *info, char *buffer);
int check_if_connect(info_t *info, char *buffer, rlist *list);
int make_command(info_t *info, char *buffer, rlist *list);
rlist *check_if_command(rlist *list);

/* free.c */

void free_user(user_t *user);
void free_info(info_t *info);

/* gen_uuid.c */

char *generate_uuid(void);

/* get_element.c */

char *get_next_elem(char *command);
int get_one_port(char *buffer, int *i);
int get_port(char *buffer);
char *get_host(char *buffer);

/* message.c */

void create_private_message(info_t *info, char *buffer, rlist *list);
void display_list_message(info_t *info, char *buffer, rlist *list);
void create_message(info_t *info, char *id, char *timestamp, FILE *filed);
char *get_id_list_message(char *buffer);
int is_good_message(info_t *info, char *first, char *second, char *buffer);
char *send_one_message_list(info_t *info, char *str);
void end_list_message(info_t *info, char *str, char *id, FILE *filed);

/* client.c */

char *read_communication(int fd);
int write_communication(int fd, char *buffer);
int get_port(char *command);
char *get_next_elem(char *command);
void create_active_serv(char *str);
int client(int port);
int main(int argc, char **argv);

/* param_file.c */

char *get_param_file(char *buffer, int nb, char end);

/* param_buffer.c */

char *get_param_buffer(char *buffer, int nb);

/* subscribe.c */

void subscribed_team(info_t *info);
char *display_user_on_team(info_t *info, char *str, rlist *list);
void subscribed_user(info_t *info, char *team, rlist *list);
void while_func(info_t *info, char *team);
int is_already_subscribe(info_t *info, char *str, char *team, int write_fd);
int is_already_user_subscribe(char *user, char *str, char *team);
void write_link_in_file(char *team, FILE *filed, info_t *info, char *str);
void create_link(info_t *info, char *team, int write_fd);
void display_subscribed_team(info_t *info, char *str);
void subscribe(info_t *info, char *buffer, int write_fd, rlist *list);
void subscribed(info_t *info, char *buffer, rlist *list);
void unsubscribe(info_t *info, char *buffer, rlist *list);
int is_subscribe(info_t *info, char *team);
int is_user_subscribe(char *user, char *team);

/* unsubscribe.c */

void rewrite_file(info_t *info, int line);
void unsubscribe_team_user(info_t *info, char *buffer);

/* str_to_word_array.c */

int supress_space(char *str, int i);
int count_words(char *str);
void intern_while_one(int *i, int *y, int *x, int a);
char **str_to_word_array(char *str);
char **str_to_word_array_sec(char *str, char c);

/* team.c */

int search_team(info_t *info, char *id_team, char *str, FILE *filed);
void display_list_team_sec(info_t *info, char *buffer);
void send_notif_add_team(char *response, rlist *list);
void create_team(info_t *info, char *id, char *name, char *description);
void set_team_value(info_t *info, char *str, FILE *filed, char *id);
int is_team_existing(char *team);
void display_list_team(info_t *info);
void display_team(info_t *info);
void add_team(info_t *info, char *buffer, rlist *list);
void team_null(info_t *info);
void display_one_team(info_t *info, char *id_team);
void set_team(info_t *info, char *id_team);

/* use.c */

void use(info_t *info, char *buffer);
void use_main_thread(info_t *info, char *buffer);
void use_main_channel(info_t *info, char *buffer);
int check_use_channel(info_t *info, char *id_channel, char *id_team);
int check_use_team(info_t *info, char *id_team);
void free_thread(char *id_team, char *id_channel, char *id_thread,
char *response);
void free_channel(char *id_team, char *id_channel, char *response);
void free_team(char *id_team, char *response);
void use_main_team(info_t *info, char *buffer);
void use_thread(info_t *info, char *buffer);
void use_channel(info_t *info, char *buffer);
void use_team(info_t *info, char *buffer);
int check_use_thread(info_t *info, char *id_channel, char *id_team,
char *id_thread);

/* useful.c */

char *concat_str(char *src1, char *src2, char *src3);

/* user.c */

int is_good_user(char *buffer, char *str);
void display_user_read_end_line(char *str);
void display_list_user(info_t *info, char *buf, rlist *list);
void display_user(info_t *info, char *buffer, rlist *list);
int check_user(info_t *info);

#endif /* !INC_ */

#endif /* !SERVEUR_H_ */