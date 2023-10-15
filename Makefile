# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 10:33:00 by lsabatie          #+#    #+#              #
#    Updated: 2023/10/15 15:46:27 by lsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER  := pipex.h
NAME	:= pipex
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -g3
SRCS	:=	main.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_strdup.c \
			ft_split.c \
			ft_strjoin.c \
                          
OBJS	:= $(SRCS:.c=.o)

%.o:%.c $(HEADER)
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

RM		    := rm -f

${NAME}:	${OBJS} ${HEADER}
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re