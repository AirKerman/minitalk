SRC_C		=	clients/client.c utils/utils.c

SRC_S		=	servers/server.c servers/utils_s.c utils/utils.c

OBJ_C		=	$(SRC_C:.c=.o)

OBJ_S		=	$(SRC_S:.c=.o)

NAME_C		=	client

NAME_S		=	server

CC			=	cc

CFLAGS		=	-Wall -Werror	-Wextra -g -I includes
RM			=	rm -f



.PHONY:		all
all:		client server

.PHONY:		client
client:		$(OBJ_C)
			$(CC) $(CFLAGS) $(OBJ_C) -o $(NAME_C)

.PHONY:		server
server:		$(OBJ_S)
			$(CC) $(CFLAGS) $(OBJ_S) -o $(NAME_S)

.PHONY:		clean
clean:
			$(RM) $(OBJ_S) $(OBJ_C)

.PHONY:		fclean
fclean:		clean
			$(RM) $(NAME_C) $(NAME_S)

.PHONY:		re
re:			fclean client server
