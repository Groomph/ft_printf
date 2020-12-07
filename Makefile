# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romain <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 06:05:16 by romain            #+#    #+#              #
#    Updated: 2020/12/07 07:05:48 by romain           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

FLAGSHARD = -Weverything

LIBFT = libft

DIR_S = sources

DIR_PARS = parsing_compo

DIR_CONV = converters

DIR_FLO = float_parsing

DIR_O = temporary

HEADER = includes

SOURCES = ft_printf.c \
	  buffer.c \
	  $(DIR_PARS)/printf_parsing.c \
	  $(DIR_PARS)/parsing_utils.c \
	  $(DIR_CONV)/lobby_write.c \
	  $(DIR_CONV)/write_cspct.c \
	  $(DIR_CONV)/write_diuxx.c \
	  $(DIR_CONV)/write_nopcol.c \
	  $(DIR_CONV)/write_efg.c \
	  $(DIR_FLO)/float_parsing.c \
	  $(DIR_FLO)/float_operations.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)/
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)
	mkdir -p $(DIR_O)/$(DIR_PARS)
	mkdir -p $(DIR_O)/$(DIR_CONV)
	mkdir -p $(DIR_O)/$(DIR_FLO)
	$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette libft/
	@echo
	norminette $(HEADER)/
	@echo
	norminette $(DIR_S)/

run:
	gcc -o runtest -I $(HEADER) $(SRCS) main.c libft/*.[ch]

runhardmode:
	$(CC) $(FLAGSHARD) -I $(HEADER) $(SRCS) main.c libft/*.[ch]

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(LIBFT).a
	rm -f runtesthardmode
	rm -f runtest

re: fclean all

.PHONY:		all clean fclean re
