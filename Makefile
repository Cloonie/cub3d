# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliew <mliew@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 14:32:28 by mliew             #+#    #+#              #
#    Updated: 2023/08/28 14:32:28 by mliew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

B_GREEN=	\033[38;5;121m
B_RED	=	\033[38;5;204m
C_GREEN	=	\033[1;32m
C_RED	=	\033[1;31m
C_BLUE	=	\033[1;34m
C_END 	=	\033[0m

NAME		=	cub3d
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
LIBFT		=	libft
LIBFLAGS	=	-Llibft -lft
# INC 		=	-lmlx -lGL -lX11 -lXext
MLXFLAG		=	-I/usr/include -Imlx_linux -O3
# LNX_MLXFLAG	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
# MAC_MLXFLAG =	-lmlx -framework OpenGL -framework AppKit
SANITIZE	=	-fsanitize=address -g3

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	MLXFLAGS2	= -Lmlx_linux -lmlx_Linux -L/usr/lib -I/usr/include -Imlx_linux -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME), Darwin)
	MLXFLAGS2	= -lmlx -framework OpenGL -framework AppKit -Imlx
endif

INCLUDES	=	./includes
SRC_PATH	=	./src
OBJ_PATH	=	./obj

SRCS	=	$(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*, .c*)))
OBJS	=	$(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) $(MLXFLAGS2) -I $(INCLUDES) -o $(NAME)
	@echo "$(B_GREEN)Compiling $(C_END)"
	@echo "$(C_GREEN)Makefile for minishell completed.$(C_END)"

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c*
					@mkdir -p $(OBJ_PATH)
					@echo "$(B_GREEN)Creating object file: $<$(C_ENDR)"
					@$(CC) $(CFLAGS) $(MLXFLAG) -I $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(B_RED)Removing $(NAME) object files$(C_END)"

fclean:	clean
	@$(RM) $(NAME) 
	@echo "$(C_RED)Removing $(NAME)$(C_END)"

lclean:
	@make fclean -s -C libft

re:	lclean fclean all