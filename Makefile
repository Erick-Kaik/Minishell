# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2023/03/09 10:26:47 by ekaik-ne          #+#    #+#              #
# #    Updated: 2023/04/10 18:02:27 by ekaik-ne         ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
FT		= ./libft/libft.a
SRC		= main.c pipe.c utils.c utils2.c utils3.c list_var.c \
		  checkers.c redirector.c cd.c env.c pwd.c echo.c exit.c \
		  export.c unset.c exec.c split_line.c split_line2.c \
		  split_line3.c signal.c list_history.c
OBJSDIR	= obj
OBJS	= $(addprefix $(OBJSDIR)/, $(SRC:%.c=%.o))
.PHONY	= all clean fclean re

all: $(NAME)
	@clear
	
$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(FT) -o $@

$(OBJSDIR):
	mkdir -p $@

$(OBJSDIR)/%.o: src/%.c src/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

${OBJS}: | ${FT}

$(FT):
	$(MAKE) -C libft/ bonus

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all
