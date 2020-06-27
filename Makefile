# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/27 15:59:43 by mli               #+#    #+#              #
#    Updated: 2020/06/27 20:51:37 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mlibasm.a

CC = clang

CFLAGS = -Wall -Wextra -Werror -I./

SRCS_FILES = test.c utils.c lstutils.c
SRCS_PATH = ./srcs/
SRCS = ${addprefix ${SRCS_PATH}, ${SRCS_FILES}}

OBJ_PATH = ./obj/
OBJS = ${addprefix ${OBJ_PATH}, ${SRCS:.c=.o}}

${NAME}: ${OBJ_PATH} ${OBJS}
	@ar rcs ${NAME} ${OBJS}

${OBJ_PATH}:
	@mkdir -p ${OBJ_PATH}/${SRCS_PATH}

${OBJ_PATH}%.o:%.c
	@${CC} ${CFLAGS} -c $< -o $@

all : ${NAME}

clean:
	@rm -rf ${OBJ_PATH}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
