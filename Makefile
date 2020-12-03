
SRCS	= ft_printf.c \
	  ft_print_buffer.c \
	  parsing_compo/ft_printf_parsing.c \
	  parsing_compo/parsing_functions.c \
	  converter_functions/lobby_write.c \
	  converter_functions/write_utils.c \
	  converter_functions/write_cspct.c \
	  converter_functions/write_diuxx.c \
	  converter_functions/write_efg.c \
	  converter_functions/write_nop.c \
	  float_parsing/float_parsing.c \
	  float_parsing/float_operation.c \
	  float_parsing/float_utils.c

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -c ${SRCS}
			ar rc ${NAME} ${OBJS} ft_printf.h float_parsing/float_parsing.h \

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
