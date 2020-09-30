# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlouekar <tlouekar@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/01 14:57:04 by tlouekar          #+#    #+#              #
#    Updated: 2020/07/14 11:11:47 by tlouekar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tlouekar.filler

SRCS = 	srcs/main.c \
		srcs/handle_input.c \
		srcs/writedata.c \
		srcs/initfiller.c \
		srcs/define_piece.c \
		srcs/search_place.c \
		srcs/placepiece.c \
		srcs/fizzylogic.c \
		srcs/helpers.c \
		srcs/heatmap.c

OBJS = 	main.o \
		handle_input.o \
		writedata.o \
		initfiller.o \
		define_piece.o \
		search_place.o \
		placepiece.o \
		fizzylogic.o \
		helpers.o \
		heatmap.o \

INCS = -I ./srcs -I ./libft/includes/

CFLAGS = -g -Wall -Wextra -Werror

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
