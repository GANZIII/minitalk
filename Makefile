NAME1 = server
NAME2 = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME1) $(NAME2)

$(NAME1): server.c
	$(CC) $(CFLAGS) $^ -o $(NAME1)

$(NAME2): client.c
	$(CC) $(CFLAGS) $^ -o $(NAME2)

clean:
	$(RM) client
	$(RM) server

fclean: clean
	$(RM) $(NAME1)
	$(RM) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
