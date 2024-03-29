# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 15:00:41 by smagdela          #+#    #+#              #
#    Updated: 2022/06/03 16:05:07 by ajearuth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
#	VARIABLES	#
#################

#	Binary Name

NAME	=	cub3D

#	Directories Management

LIBSD	=	libs/
LIBFTD	=	${addprefix ${LIBSD},libft/}
MLXD	=	${addprefix ${LIBSD},mlx_linux/}
INCD	=	includes/
SRCD	=	sources/
OBJD	=	objects/
BONUSD	=	bonus/
BONUSSD	=	${BONUSD}sources/
BONUSOD	=	${BONUSD}objects/

#	Libraries Management

LIBFT	:=	${addprefix ${LIBFTD},libft.a}
MLX		:=	${addprefix ${MLXD},libmlx_Linux.a}
LIBS	:=	${LIBFT} ${MLX}

#	Source Files

SRCS	=	main.c				error_messages.c \
			get_next_line.c 	get_next_line_utils.c \
			open_file.c 		map_init.c \
			textures.c			textures_2.c 		cube_map.c			cube_map2.c \
			free_and_destroy.c	parsing_utils.c \
			events.c 			player_moves.c		player_moves2.c		draw.c \
			rc_utils.c			raycast_engine.c	raycast_engine2.c	texturizer.c \

BONUS 	=	main_bonus.c			error_messages_bonus.c \
			get_next_line_bonus.c 	get_next_line_utils_bonus.c \
			open_file_bonus.c 		map_init_bonus.c \
			textures_bonus.c		textures_2_bonus.c 			cube_map_bonus.c			cube_map2_bonus.c \
			free_and_destroy_bonus.c	parsing_utils_bonus.c \
			events_bonus.c 			player_moves_bonus.c		player_moves2_bonus.c		draw_bonus.c \
			rc_utils_bonus.c		raycast_engine_bonus.c		raycast_engine2_bonus.c	texturizer_bonus.c \
			cub2d_bonus.c			utils_bonus.c \
			mouse_events_bonus.c	bad_guys_bonus.c sound_bonus.c	doors_bonus.c	\
			bad_guys2_bonus.c 	player_mooves_utils_bonus.c	bad_guys_norm_bonus.c \

#	Object Files

DEPS	:=	${addprefix ${OBJD},${SRCS:.c=.d}} ${addprefix ${BONUSOD},${BONUS:.c=.d}}
OBJS	:=	${addprefix ${OBJD},${SRCS:.c=.o}}
SRCS	:=	${addprefix ${SRCD},${SRCS}}
BONUSO	:=	${addprefix ${BONUSOD},${BONUS:.c=.o}}
BONUS	:=	${addprefix ${BONUSSD},${BONUS}}

#	Commands and Flags

CC	=	clang -g
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS	=	-lX11 -lXext -lm -lz
MKDIR	=	mkdir -p
LINK	=	ar rcs
LIBSMK	=	make -C

###################
#	FANCY STUFF   #
###################

#	Colors

GREY	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
WHITE	=	\033[0;37m
CYAN	=	\033[0;96m

S_GREY	=	\033[1;30m
S_RED	=	\033[1;31m
S_GREEN	=	\033[1;32m
S_YELLOW	=	\033[1;33m
S_BLUE	=	\033[1;34m
S_PURPLE	=	\033[1;35m
S_WHITE	=	\033[1;37m
S_CYAN	=	\033[1;96m

BOLD	=	\033[1m
NC		=	\033[0m

#	Logos

WHALE	=	"\n${GREEN}       ::: \n     ___:____     |^\/^| \n   ,'        '.    \  / \n   |  O        \___/  | \n ~^~^~^~^~^~^~^~^~^~^~^~^~\n \n Compilation Successful!	${NC}\n"
NUKE	=	"\n${S_RED}     _.-^^---....,,--       \n _--                  --_  \n<                        >)\n|                         | \n \._                   _./  \n    '''--. . , ; .--'''       \n          | |   |             \n       .-=||  | |=-.   \n       '-=£€%&%€£=-'   \n          | ;  :|     \n _____.,-£%&€@%£&£~,._____${NC}\n\n"

#############
#	RULES	#
#############

#	Mandatory

all:	${NAME}

${NAME}:	${LIBS} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${MLXFLAGS} ${LIBS} -o ${NAME}
	@echo ${WHALE}

${OBJD}%.o:	${SRCD}%.c
	mkdir -p ${OBJD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -I${LIBFTD} -I${MLXD} -MMD $<

${LIBS}:
	${LIBSMK} ${LIBFTD} bonus
	${LIBSMK} ${MLXD} all

bonus:	${NAME}_bonus

${NAME}_bonus : ${LIBS} ${BONUSO}
	${CC} ${CFLAGS} ${BONUSO} ${MLXFLAGS} ${LIBS} -o ${NAME}_bonus
	@echo ${WHALE}

${BONUSOD}%.o:	${BONUSSD}%.c
	mkdir -p ${BONUSOD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -I${LIBFTD} -I${MLXD} -MMD $<

clean:
	-rm -rf ${OBJD} ${BONUSOD}
	${LIBSMK} ${LIBFTD} clean
	${LIBSMK} ${MLXD} clean

fclean:	clean
	-rm ${NAME} ${NAME}_bonus
	${LIBSMK} ${LIBFTD} fclean
	${LIBSMK} ${MLXD} clean
	@echo ${NUKE}

re:		fclean all

#	Developpment-helping Rules

norm:
	@norminette ${SRCS} ${BONUS} ${INCD}*.h ${LIBFTD}*.c ${LIBFTD}*.h | grep 'Error' ; true

leak:	${NAME}
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}

.PHONY : re all bonus clean fclean norm leak

-include ${DEPS}
