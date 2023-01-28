# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/28 18:28:14 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

CC = cc
CFLAGS = -Wall -Wextra #-Werror
LINKFLAGS = 

################################################################################
################################################################################

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


################################################################################
################################################################################

OBJ_DIR = obj/
ALL_OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))


################################################################################
################################################################################

all: mkdir submodules $(LIBFT) $(NAME)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ)
	@$(CC) $^ -o $@ -I $(HDR_DIR) $(LINK_FLAGS) $(READLINE) $(LIBFT)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"cleaned"$(DEFAULT)
	@make -C lib/libft clean

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo $(RED)"fcleaned"$(DEFAULT)
	@rm -rf $(READLINE_DIR)
	@make -C lib/libft fclean

re:	fclean all

mkdir:
	@mkdir -p $(dir $(ALL_OBJ))


################################################################################
################################################################################

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/

$(LIBFT):
	@make -C lib/libft

libft: $(LIBFT)

################################################################################
################################################################################

submodules:
	@git submodule init
	@git submodule update
	@make libft
	@make ani_readline

################################################################################
################################################################################


READLINE_VERSION=	readline-8.1.2
READLINE_LIB	=	libreadline.a
READLINE_DIR	=	lib/readline/
READLINE		=	$(READLINE_DIR)$(READLINE_LIB)

ani_readline:
	bash ./spinner.sh "make readline" "building readline" "Spinner_Braille"

readline: $(READLINE)

$(READLINE):
	@mkdir -p lib
	@curl -s https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz --output lib/$(READLINE_VERSION).tar.gz
	@tar xfz lib/$(READLINE_VERSION).tar.gz -C lib
	@cd lib/$(READLINE_VERSION); ./configure >/dev/null 2>&1; cd ../..
	@make -C lib/$(READLINE_VERSION) >/dev/null 2>&1
	@mv -f lib/$(READLINE_VERSION) lib/readline
	@rm -f lib/$(READLINE_VERSION).tar.gz




################################################################################
################################################################################



LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a



UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif


lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer


################################################################################
################################################################################


GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"


.SILENT:

.PHONY: