SRC_C		=	client/client.c

SRC_S		=	server/server.c

OBJ_C		=	$(SRC_C:.c=.o)

OBJ_S		=	$(SRC_S:.c=.o)

NAME_C		=	client

NAME_S		=	server

CC			=	cc

CFLAGS		=	-Wall -Werror	-Wextra -g -I includes
RM			=	rm -f


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
