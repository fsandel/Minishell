# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/28 14:31:53 by fsandel          ###   ########.fr        #
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

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/

READLINE_VERSION = readline-8.1.2
READLINE_LIB	=	libreadline.a
READLINE_DIR	=	lib/$(READLINE_VERSION)/
READLINE		=	$(READLINE_DIR)$(READLINE_LIB)


OBJ_DIR = obj/

ALL_OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))

all: mkdir submodules $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR) $(CFLAGS)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ)
	@$(CC) $^ -o $@ -I $(HDR_DIR) $(CFLAGS) $(READLINE) $(LIBFT)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"cleaned"$(DEFAULT)
	@rm -rf lib/$(READLINE_VERSION)
	@rm -f lib/$(READLINE_VERSION).tar.gz
	@make -C lib/libft clean

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo $(RED)"fcleaned"$(DEFAULT)
	@rm -rf lib/$(READLINE_VERSION)
	@rm -f lib/$(READLINE_VERSION).tar.gz
	@make -C lib/libft fclean

re:	fclean all

mkdir:
	@mkdir -p $(dir $(ALL_OBJ))

$(LIBFT):
	@make -C lib/libft

libft: $(LIBFT)


readline: $(READLINE)

$(READLINE):
	@echo $(GREEN)"making readline"$(DEFAULT)
	@mkdir -p lib
	@curl -s https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz --output lib/$(READLINE_VERSION).tar.gz
	@tar xfz lib/$(READLINE_VERSION).tar.gz -C lib
	@cd lib/$(READLINE_VERSION); ./configure >/dev/null 2>&1; cd ../..
	@make -C lib/$(READLINE_VERSION) >/dev/null 2>&1

submodules:
	@git submodule init
	@git submodule update
	@make libft
	@make readline

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"




.SILENT:

.PHONY: