# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabel <aabel@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 10:59:45 by arthurabel        #+#    #+#              #
#    Updated: 2023/08/07 15:53:12 by aabel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	src/philosopher.c \
		src/utils/init.c \
		src/utils/utils.c \
		src/utils/threads.c \
		src/utils/actions.c \

FLAGS = -Wall -Wextra -Werror -fsanitize=thread

OBJ = $(SRC:%.c=%.o)

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all