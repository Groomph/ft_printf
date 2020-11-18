SRCS	= ft_printf.c \
	  ft_printf_parsing.c \
	  ft_printf_print.c \
	  ft_printf_print2.c \

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -c ${SRCS}
			ar rc ${NAME} ${OBJS} ft_printf.h

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
