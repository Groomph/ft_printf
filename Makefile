WRITE_PATH	= converter_function/

SRCS	= ft_printf.c \
	  ft_printf_parsing.c \
	  ${WRITE_PATH}ft_printf_write.c \
	  ${WRITE_PATH}write_cs.c \
	  ${WRITE_PATH}write_p.c \
	  ${WRITE_PATH}write_iduxX.c \
	  ${WRITE_PATH}write_utils.c

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
