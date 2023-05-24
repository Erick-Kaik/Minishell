# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 10:26:47 by ekaik-ne          #+#    #+#              #
#    Updated: 2023/04/10 18:02:27 by ekaik-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
GCC =  $(CC) $(CFLAGS)

LIBFT = libft/libft.a
NAME = minishell
SRC = main.c utils.c list_var.c checkers.c redirector.c cd.c env.c pwd.c echo.c exit.c export.c unset.c exec.c split_line.c signal.c list_history.c
OBJ = ${SRC:.c=.o}

.PHONY = all bonus clean fclean re

all: $(NAME)

${NAME}: $(OBJ)
	$(GCC) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

${OBJ}: | $(LIBFT)

${LIBFT}:
	$(MAKE) bonus -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all