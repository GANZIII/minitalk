NAME = minitalk.a

SERVER = server
CLIENT = client

SRC_SERVER = server.c
SRC_CLIENT = client.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rc

OBJ_SERVER = ${SRC_SERVER:.c=.o}
OBJ_CLIENT = ${SRC_CLIENT:.c=.o}

${NAME}: ${SERVER} ${CLIENT}
	${AR} $@ $?

${SERVER}: ${OBJ_SERVER}
	${CC} ${CFLAGS} ${OBJ_SERVER} -o ${SERVER}

${CLIENT}: ${OBJ_CLIENT}
	${CC} ${CFLAGS} ${OBJ_CLIENT} -o ${CLIENT}

all: $(NAME)

clean:
	${RM} ${OBJ_CLIENT}
	${RM} ${OBJ_SERVER}

fclean: clean
	${RM} ${SERVER}
	${RM} ${CLIENT}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
