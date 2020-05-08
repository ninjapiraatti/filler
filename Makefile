# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 14:57:04 by tlouekar          #+#    #+#              #
#    Updated: 2020/05/08 12:37:15 by tlouekar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = resources/players/tlouekar.filler

SRCS = 	srcs/main.c \
		srcs/readinput.c \
		srcs/initfiller.c \
		srcs/definepiece.c \
		srcs/placepiece.c \
		srcs/fizzylogic.c \
		srcs/helpers.c \

OBJS = 	main.o \
		readinput.o \
		initfiller.o \
		definepiece.o \
		placepiece.o \
		fizzylogic.o \
		helpers.o \

INCS = -I ./srcs -I ./libft/includes/

CFLAGS = -g

LIB = -L./libft -lft

HEADER	= includes/

all: $(NAME)

$(NAME):
	make -C libft
	gcc $(CFLAGS) -c $(SRCS) $(INCS)
	gcc $(CFLAGS) $(INCS) $(OBJS) $(LIB) -o $(NAME)

debug:

.PHONY: clean fclean re all

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
