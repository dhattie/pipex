# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhattie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 20:41:00 by dhattie           #+#    #+#              #
#    Updated: 2021/08/06 20:41:02 by dhattie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC		= gcc
HEADER	= pipex.h

LIBFT	= libft.a

SRCS	=  pipex.c \
           ft_pipex_utils_bonus_part_1.c \
           ft_pipex_utils_bonus_part_2.c \
           ft_pipex_utils_bonus_part_3.c \
           ft_pipex_utils_bonus_part_4.c \

SRCS_B	=	pipex_bonus.c \
			ft_pipex_utils_bonus_part_1.c \
			ft_pipex_utils_bonus_part_2.c \
			ft_pipex_utils_bonus_part_3.c \
			ft_pipex_utils_bonus_part_4.c \

RM		= rm -rf
CFLAGS	= -Wall -Werror -Wextra
OBJS	= pipex.o \
          ft_pipex_utils_bonus_part_1.o \
          ft_pipex_utils_bonus_part_2.o \
          ft_pipex_utils_bonus_part_3.o \
          ft_pipex_utils_bonus_part_4.o \

OBJS_B	=	pipex_bonus.o \
          	ft_pipex_utils_bonus_part_1.o \
          	ft_pipex_utils_bonus_part_2.o \
          	ft_pipex_utils_bonus_part_3.o \
          	ft_pipex_utils_bonus_part_4.o \

all: $(NAME)
$(NAME):	$(SRCS) $(HEADER)
			$(CC) $(CFLAGS) -c  $(SRCS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

bonus:		$(SRCS_B) $(HEADER)
			@$(MAKE) SRCS="$(SRCS_B)" OBJS="$(OBJS_B)"

clean:
			${RM} ${OBJS} ${OBJS_B}
fclean:		clean
			${RM} ${NAME}
re:			clean all
.PHONY:		all clean fclean re

1arg:$(NAME)
	./pipex infile "wc -c" outfile

2arg:
	./pipex infile "cat" "cat" outfile

2_arg:
	./pipex infile "wc -w" "wc -W" outfile

2_1arg:
	./pipex infile "cat" outfile

2_2arg:
	./pipex here_doc LIMITER "cat" "cat" outfile

3arg:$(NAME)
	./pipex infile "wc -l" "wc -w" "wc -m" outfile

4arg:$(NAME)
	./pipex infile "wc -l" "wc -w" "wc -m" "wc -m" outfile

5arg:$(NAME)
	./pipex infile "wc -l" "wc -w" "wc -m" "wc -m" "wc -m" outfile

.PHONY : all clean fclean re test