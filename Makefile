# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkarosas <jkarosas@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 13:20:00 by jkarosas          #+#    #+#              #
#    Updated: 2023/01/12 14:42:37 by jkarosas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRt

SRC			=	src/main.c src/parser.c src/parser_utils.c src/get_next_line.c \
				src/get_next_line_utils.c src/free_scene.c src/parse_objects.c \
				src/parse_parameters.c src/parse_lighting.c 

OBJ			= ${SRC:.c=.o}

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
LFLAGS		= -L libft

INC			= -I ./inc -I ./libft
LIB			= libft/libft.a

all:		${NAME}

${NAME}:	${OBJ}
			make -s -C libft
			make bonus -s -C libft
			${CC} ${FLAGS} ${LFLAGS} ${OBJ} -o ${NAME} ${LIB} -lft

.c.o:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

clean:
			make clean -s -C libft
			rm -rf ${OBJ}

fclean:		clean
			make fclean -s -C libft
			rm -rf ${NAME}

re:			fclean all

.PHONY:		all clean fclean re