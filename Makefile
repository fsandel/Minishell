# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/28 12:08:40 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = Minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR			=	src/
SRC_FILES		=	main.c

HDR				=	$(addprefix $(HDR_DIR), $(HDR_DIR))
HDR_DIR			=	include/
HDR_FILES		=	minishell.h

1FOLDER			=	$(addprefix $(1FOLDER_DIR), $(1FOLDER_FILES))
1FOLDER_DIR		=	src/1folder/
1FOLDER_FILES	=	11file.c 12file.c

2FOLDER			=	$(addprefix $(2FOLDER_DIR), $(2FODLER_FILES))
2FOLDER_DIR		=	src/2folder/
2FODLER_FILES	=	21file.c 22file.c

ALL_SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES)) $(1FOLDER) $(2FOLDER)

LIBFT			=	libft.a

OBJ_DIR = obj/

ALL_OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))

all: mkdir submodules $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR) $(CFLAGS)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ)
	@$(CC) $^ -o $@ -I $(HDR_DIR) $(CFLAGS)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"cleaned"$(DEFAULT)

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo $(RED)"fcleaned"$(DEFAULT)

re:	fclean all

mkdir:
	@mkdir -p $(dir $(ALL_OBJ))

$(LIBFT):
	@make -C lib/libft

libft: $(LIBFT)

submodules:
	@git submodule init
	@git submodule update
	@make libft

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"