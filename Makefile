WRITE_PATH	= converter_functions/

SRCS	= ft_printf.c \
	  ft_print_buffer.c \
	  ft_printf_parsing.c \
	  parsing_functions.c \
	  ${WRITE_PATH}lobby_write.c \
	  ${WRITE_PATH}write_utils.c \
	  ${WRITE_PATH}write_cspct.c \
	  ${WRITE_PATH}write_p.c \
	  ${WRITE_PATH}write_di.c \
	  ${WRITE_PATH}write_ouxx.c \
	  ${WRITE_PATH}write_n.c \
	  ${WRITE_PATH}write_float.c \
	  ${WRITE_PATH}/float_parsing/float_parsing.c \
	  ${WRITE_PATH}/float_parsing/float_operation.c \
	  ${WRITE_PATH}/float_parsing/float_utils.c \
	  ${WRITE_PATH}/float_parsing/write_e.c \
	  ${WRITE_PATH}/float_parsing/write_f.c \
	  ${WRITE_PATH}/float_parsing/write_gE.c \
	  ${WRITE_PATH}/float_parsing/write_gF.c 

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -c ${SRCS}
			ar rc ${NAME} ${OBJS} ft_printf.h ${WRITE_PATH}/float_parsing/float_parsing.h \

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
