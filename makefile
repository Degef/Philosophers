# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 16:23:00 by Degef             #+#    #+#              #
#    Updated: 2023/05/23 17:01:51 by Degef            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

SRCS = 	main.c init.c libft.c philo.c utils.c table_actions.c 

$(NAME) :
	cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(NAME)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all

.PHONY: all clean fclean re