##
## Makefile for my_irc in /srv/http
## 
## Made by Adolfo Flores
## Login   <flores_a@epitech.eu>
## 
## Started on  Sat Mar 21 14:44:31 2015 
## Last update Thu Apr 16 11:49:56 2015 
##

#CLNT_SRC =		clnt/
SRVR_SRC =		srvr/hashtbl.c \
				srvr/actions.c \
				srvr/listen.c \
				srvr/handlers.c \
				srvr/main.c \
				srvr/read_actions.c \

CLNT_OBJ =		$(CLNT_SRC:.c=.o)

SRVR_OBJ =		$(SRVR_SRC:.c=.o)

DEPS =		include/defs.h

SRVR =		server

CLNT =		client

CC =		gcc

CFLAGS =	-Wall -Werror -Wextra -pedantic -g

RM =		rm -f

all:		$(SRVR) $(CLNT)

$(SRVR):	$(SRVR_OBJ) $(DEPS)
			gcc $(CFLAGS) -o $(SRVR) $(SRVR_OBJ)

$(CLNT):	$(CLNT_OBJ) $(DEPS)
			gcc $(CFLAGS) -o $(CLNT) $(CLNT_OBJ)
clean:
			$(RM) $(SRVR_OBJ) $(CLNT_OBJ)

fclean:		clean
			$(RM) $(SRVR) $(CLNT)

re:			fclean $(SRVR)

.PHONY:			all clean fclean re
