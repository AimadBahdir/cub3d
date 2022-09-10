# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 13:08:02 by abahdir           #+#    #+#              #
#    Updated: 2020/11/18 09:28:28 by abahdir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	./cub3D
FLAGS	=	-Wall -Wextra -Werror
SRC		=	cub3d.c						\
			set_map.c					\
			error.c          			\
			setup.c						\
			events.c          			\
			setup_utils.c				\
			ft_sprtlist.c     			\
			sprite.c					\
			print_map_bonus.c 			\
			stepchecker.c				\
			raycasting.c      			\
			utils.c						\
			save.c						\
			utils/ft_atoi.c				\
			utils/ft_isdigit.c			\
			utils/ft_memcpy.c			\
			utils/ft_split.c			\
			utils/ft_strdup.c			\
			utils/ft_strjoin.c			\
			utils/ft_strlen.c			\
			utils/ft_strncmp.c			\
			utils/ft_strtrim.c			\
			utils/ft_substr.c			\
			utils/ft_tolower.c			\
			utils/ft_toupper.c			\
			utils/get_next_line.c		\
			utils/get_next_line_utils.c	\

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) $(FLAGS) -lmlx -framework appkit -framework opengl -o $(NAME)

bonus: $(NAME)

clean:
	rm -f cub3D

fclean: clean

re: fclean all

.PHONY: re clean fclean bonus