# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: martincelavie <martincelavie@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 09:31:44 by hchauvin          #+#    #+#              #
#    Updated: 2023/11/14 23:01:44 by martincelav      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := 	libft.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
PRINT_LIBFT := 1

SRC :=	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		free_array.c ft_arraylen.c	print_err.c	\
		get_next_line_bonus.c	ft_strjoin_free.c	\
		ft_printf.c	ft_printf_utils.c	\

OBJ := ${SRC:.c=.o}

$(NAME):		${OBJ}
		@ar -rc ${NAME} ${OBJ} 

%.o:	%.c
		@if [ $(PRINT_LIBFT) -eq 1 ]; then echo -n "Libft : "; fi
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo -n "\033[32m✔\033[0m"
		@$(eval PRINT_LIBFT = 0)

all: ${NAME} 

clean:
		$(RM) ${OBJ}

fclean: clean
		$(RM) ${NAME}

re: fclean all
