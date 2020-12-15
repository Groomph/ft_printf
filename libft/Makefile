SRCS	= init_zero.c \
	  is_double_signed.c \
	  shift_left_erase.c \
	  shift_right_add.c \
	  string_len.c \
	  strjoin_free.c \
	  substr_free.c \
	  utoa_base.c \
	  utoa_len.c \
	  is_infinite.c \
	  is_not_number.c

OBJS	= ${SRCS:.c=.o}

BOBJS	= ${BSRCS:.c=.o}


NAME	= libft.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -c ${SRCS}
			ar rc ${NAME} ${OBJS} libft.h

all:		${NAME}

clean:
		${RM} ${OBJS} ${BOBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

so:	
		gcc -shared -o libft.so -fpic *.c libft.h

.PHONY:		all clean fclean re
