# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 17:48:19 by prebeca           #+#    #+#              #
#    Updated: 2021/07/03 14:49:10 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

C_DIR	=	src

O_DIR	=	obj

SRCS	=	${patsubst %, ${C_DIR}/%, ${C_FILES}}

C_FILES	=	main.c\
			handle_args.c\
			set_table.c\
			life_cycle.c\
			utils.c

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${SRCS:.c=.o}}

CC		=	clang

CFLAGS	=	-I./inc/ -g -Wall -Wextra -Werror -pthread #-fsanitize=thread

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -rf ${O_DIR}

fclean:		clean
			rm -f ${NAME}

re:			fclean all
