# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/28 15:54:41 by pgorner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif

NAME = Minishell

CC = cc
CFLAGS = -Wall -Wextra #-Werror
LINKFLAGS = 

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

LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a
LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/

READLINE_VERSION = readline-8.1.2
READLINE_LIB	=	libreadline.a
READLINE_DIR	=	lib/readline/
READLINE		=	$(READLINE_DIR)$(READLINE_LIB)


OBJ_DIR = obj/

ALL_OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))

all: mkdir submodules $(NAME)

lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ)
	@$(CC) $^ -o $@ -I $(HDR_DIR) $(LINK_FLAGS) $(READLINE) $(LIBFT)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"cleaned"$(DEFAULT)
	@rm -rf lib/readline
	@make -C lib/libft clean

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo $(RED)"fcleaned"$(DEFAULT)
	@rm -rf lib/readline
	@make -C lib/libft fclean

re:	fclean all

mkdir:
	@mkdir -p $(dir $(ALL_OBJ))

$(LIBFT):
	@make -C lib/libft

libft: $(LIBFT)

test:
	bash ./spinner.sh "make readline" "Minishell" "Spinner_Braille"

readline: $(READLINE)

$(READLINE):
	@echo $(GREEN)"making readline"$(DEFAULT)
	@mkdir -p lib
	@curl -s https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz --output lib/$(READLINE_VERSION).tar.gz
	@tar xfz lib/$(READLINE_VERSION).tar.gz -C lib
	@mv lib/$(READLINE_VERSION) lib/readline
	@cd lib/readline; ./configure >/dev/null 2>&1; cd ../..
	@make -C lib/readline >/dev/null 2>&1
	@rm -f lib/$(READLINE_VERSION).tar.gz

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