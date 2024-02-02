# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 10:33:00 by lsabatie          #+#    #+#              #
#    Updated: 2024/02/02 09:23:47 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER  := incs/pipex.h
NAME	:= pipex
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror
SRCS	:=	src/main.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/ft_strdup.c \
			src/ft_split.c \
			src/ft_strjoin.c \
			src/ft_strcmp.c \
			src/ft_putstr_fd.c \
			src/pipex_utils.c \
                          
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