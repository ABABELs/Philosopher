# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arthurabel <arthurabel@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 10:59:45 by arthurabel        #+#    #+#              #
#    Updated: 2023/06/26 11:51:03 by arthurabel       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	src/philosopher.c \
		src/utils/init.c \

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all