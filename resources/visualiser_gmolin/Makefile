# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmolin <gmolin@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 14:47:06 by gmolin            #+#    #+#              #
#    Updated: 2020/02/05 16:26:08 by gmolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual

SRCS =	srcs/main.c \
		srcs/drawing_mode.c \
		srcs/drawing_mode_2.c \
		srcs/input_scan.c \
		srcs/tools.c	   

FLAGS = -Wall -Werror -Wextra -I./includes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L../includes/mlx/ -lmlx -framework OpenGL -framework AppKit ../libftprintf/libftprintf.a
	echo "visualiser done"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
