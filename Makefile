# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 13:11:02 by ekaik-ne          #+#    #+#              #
#    Updated: 2023/03/06 20:56:29 by ekaik-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
GCC =  $(CC) $(CFLAGS)

LIBFT = libft/libft.a
NAME = minishell
SRC = main.c utils.c echo.c cd.c pwd.c env.c redirection.c unset.c export.c list_var.c list_history.c history.c signal.c
OBJ = ${SRC:.c=.o}

.PHONY = all bonus clean fclean re

all: $(NAME)

${NAME}: $(OBJ)
	$(GCC) $(OBJ) $(LIBFT) -o $(NAME)

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
