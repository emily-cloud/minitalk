SERVER = server
CLIENT = client
CC	=	cc
RM	=	rm -rf
CFLAGS	=	-Wall -Wextra -Werror

all: 		$(SERVER)	$(CLIENT)

$(SERVER):	server.c
		@$(CC) $(FLAGS) $<  -o $@
$(CLIENT):	client.c
		@$(CC) $(FLAGS) $<  -o $@

clean:
		@$(RM) $(SERVER) $(CLIENT)
fclean: clean
		$(RM)

re:		fclean all

.PHONY:		all clen fclean re libft
