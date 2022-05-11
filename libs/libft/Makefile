# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 11:59:39 by smagdela          #+#    #+#              #
#    Updated: 2021/09/16 10:32:04 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =    libft.a

CC        =    gcc -c -o
LINKER    =    ar rcs
RM        =    rm -rf

SRCS    =   ft_bzero.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
            ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
			ft_atoi.c ft_itoa.c \
			ft_calloc.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_split.c \

OBJS    =    ${SRCS:.c=.o}

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

BONUSO	=	${BONUS:.c=.o}

CFLAGS	=    -Wall -Wextra -Werror
LDFLAGS	=    

${NAME}:	${OBJS}
	${LINKER} $@ ${LDFLAGS} ${OBJS}

all: ${NAME}

${OBJD}%.o:    ${SRCD}%.c
	${CC} $@ ${CFLAGS} $<

bonus:	${OBJS} ${BONUSO}
	${LINKER} ${LDFLAGS} ${NAME} ${OBJS} ${BONUSO}

clean:
	${RM} ${OBJS} ${BONUSO}

fclean:
	${RM} ${OBJS} ${BONUSO} ${NAME}

re:    fclean all

.PHONY: re all clean fclean