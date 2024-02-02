# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 10:33:00 by lsabatie          #+#    #+#              #
#    Updated: 2023/10/19 18:15:05 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER  := pipex.h
NAME	:= pipex
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror
SRCS	:=	main.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_strdup.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strcmp.c \
			ft_putstr_fd.c \
			pipex_utils.c \
                          
OBJS	:= $(SRCS:.c=.o)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

RM		    := rm -f

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re