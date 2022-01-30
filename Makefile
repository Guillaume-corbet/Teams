##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## program
##

SERVEUR	=	serveur.c	\
			add_to_list.c	\
			str_to_word_array.c		\
			help_tab.c		\
			add_client.c		\
			command.c		\
			command2.c		\
			communicate.c		\
			get_element.c		\
			help.c		\
			inic.c		\
			logout.c		\
			remove_client.c		\
			user.c		\
			user2.c		\
			int_to_str.c		\
			free.c		\
			message.c		\
			team.c		\
			team2.c		\
			team3.c		\
			gen_uuid.c		\
			subscribe.c		\
			subscribe2.c		\
			subscribe3.c		\
			param_file.c		\
			param_buffer.c		\
			use.c		\
			use2.c		\
			use3.c		\
			channel.c		\
			channel2.c		\
			thread.c		\
			thread2.c		\
			reply.c			\
			reply2.c			\
			useful_func.c		\
			channel_func.c		\
			message_send.c		\
			unsubscribe.c		\
			display_user.c		\
			thread_create.c	\
			thread_create2.c

CLIENT 	=	client.c		\
			client2.c		\
			client3.c		\
			communicate.c		\
			param_file.c		\
			client_log_unknown.c		\
			client_log_created.c		\
			client_log_prints.c		\
			client_log_print.c 		\
			client_log_user.c		\
			client_log_subscribe.c \
			client_command.c

NAMESERV	=	myteams_server

NAMECLIENT	=	myteams_cli

FLAGS	=	-W -Wall -Werror -Wextra -Wunused-macros -Wendif-labels -pedantic -Wcomment -Wmissing-braces -Wmissing-include-dirs -Wparentheses -Wsequence-point -ansi -ggdb -Wunused -Wduplicated-branches -Wmisleading-indentation

LIB		=	-Llib/my/. -lmy

.PHONY: lib serveur client

all:	lib serveur client

lib:
		(cd ./lib/my/ && make)

client:
		gcc -o $(NAMECLIENT) $(CLIENT) $(LIB) -g3 -Llib/myteams/. -lmyteams

serveur:
		gcc -o $(NAMESERV) $(SERVEUR) $(LIB) -luuid -g3 -Llib/myteams/. -lmyteams

clean:
		rm -f $(NAMESERV)
		rm -f $(NAMECLIENT)

fclean:
		rm -f $(NAMESERV)
		rm -f $(NAMECLIENT)
		rm -f *~
		rm -f *#

re:		fclean all
