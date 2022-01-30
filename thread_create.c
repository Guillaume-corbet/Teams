/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread_create
*/

#include "serveur.h"

void thread_free(char *title, char *body, char *response, char *id)
{
    free(title);
    free(body);
    free(response);
    free(id);
}

char *norm_add_thread(info_t *info, char *id, char *title, char *body)
{
    char *response = malloc(sizeof(char) * 1024);

    create_thread(info, id, title, body);
    server_event_thread_created(info->channel->id, id, info->user->id, body);
    response[sprintf(response, "%s%s;%s;%li;%s;%s\n", THREAD_CREATED,
    id, info->user->id, time(NULL), title, body)] = 0;
    return (response);
}

void add_thread(info_t *info, char *buffer, rlist *list)
{
    char *response;
    char *title;
    char *body;
    char *id = malloc(sizeof(char) * 1024);
    struct node *tmp = list->p_head;

    id = generate_uuid();
    title = get_param_buffer(buffer, 1);
    body = get_param_buffer(buffer, 2);
    response = norm_add_thread(info, id, title, body);
    memset(title, '\0', 1024);
    title[sprintf(title, "/create \"%s\"\n", body)] = 0;
    add_first_reply(info, title, id);
    while (tmp) {
        if (tmp->info->user->id != NULL && tmp->info->fd != info->fd
            && is_user_subscribe(tmp->info->user->id, info->team->id) == TRUE)
            write_communication(tmp->info->fd, response);
        tmp = tmp->p_next;
    } write_communication(info->fd, response);
    thread_free(title, body, response, id);
}

void set_thread_sec(info_t *info, char *title, char *body, char *str)
{
    title = get_param_file(str, 4, ';');
    body = get_param_file(str, 5, ';');
    info->thread->title = strdup(title);
    info->thread->body = strdup(body);
    free(title);
    free(body);
    free(str);
    return;
}

void set_thread(info_t *info, char *id_thread)
{
    char *str = malloc(sizeof(char) * 1024);
    char *id;
    char *title;
    char *body;
    size_t bufs = 1024;
    FILE *filed = fopen("thread", "a+");

    memset(str, '\0', 1024);
    while (getline(&str, &bufs, filed) > 0) {
        id = get_param_file(str, 1, ';');
        if (strcmp(id, id_thread) == 0) {
            info->thread->id = strdup(id);
            set_thread_sec(info, title, body, str);
            fclose(filed);
            return;
        }
        memset(str, '\0', 1024);
        free(id);
    }
    free(str);
    fclose(filed);
}