# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 14:01:46 by mliew             #+#    #+#              #
#    Updated: 2023/05/13 01:15:35 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

B_GREEN=	\033[38;5;121m
B_RED	=	\033[38;5;204m
C_GREEN	=	\033[1;32m
C_RED	=	\033[1;31m
C_BLUE	=	\033[1;34m
C_END 	=	\033[0m
C_ENDR	=	\033[0m\r

NAME		=	libft.a
OBJS		=	$(SRCS:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror -I ./
CC			=	gcc
RM			=	rm -rf
AR			=	ar rcs

INCLUDES	= ./includes
SRC_PATH	= ./src
OBJ_PATH	= ./obj

SRCS	= $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*/*,.c*)))
OBJS	= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

# $(foreach)	- replaces var1 with var2 and creates a different path for each var1.
# $(notdir)		- takes away the directory path from the file name	e.g lib42/src/main.c
# $(basename)	- takes away the extension type of the file name	e.g main.c -> main

all: $(NAME)

$(NAME):			$(OBJ_PATH)	$(OBJS)
					@$(AR) $(NAME) $(OBJS)
					@echo "$(B_GREEN)Compiling $@$(C_ENDR)"
					@echo "$(C_GREEN)Makefile for lib42 completed.$(C_ENDR)"

$(OBJ_PATH)/%.o:	$(SRC_PATH)/*/%.c*
					@echo "$(B_GREEN)Creating object file: $<$(C_ENDR)"
					@$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH):
					@echo "$(C_GREEN)Creating libft object directory$(C_END)"
					@mkdir -p $(OBJ_PATH)

clean:
					@echo "$(B_RED)Removing libft object directory$(C_END)"
					@$(RM) $(OBJ_PATH)

fclean:				clean
					@echo "$(C_RED)Removing $(NAME)$(C_END)"
					@$(RM) $(NAME)

re:					fclean all