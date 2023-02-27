# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/02/25 17:58:04 by pgorner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LINKFLAGS		=
REDIRECT		=	2> /dev/null 1> /dev/null

################################################################################
################################################################################

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_DIR			=	src/
SRC_FILES		=	main.c minishell.c

EXECUTOR		=	$(addprefix $(EXECUTOR_DIR), $(EXECUTOR_FILES))
EXECUTOR_DIR	=	src/executor/
EXECUTOR_FILES	=	executor.c duping.c builtin.c builtin_in_exec.c builtin_no_exec.c path.c export.c cd.c

EXPANDER		=	$(addprefix $(EXPANDER_DIR), $(EXPANDER_FILES))
EXPANDER_DIR	=	src/expander/
EXPANDER_FILES	=	expander.c

LEXER			=	$(addprefix $(LEXER_DIR), $(LEXER_FILES))
LEXER_DIR		=	src/lexer/
LEXER_FILES		=	lexer.c lexercheck.c

PARSER			=	$(addprefix $(PARSER_DIR), $(PARSER_FILES))
PARSER_DIR		=	src/parser/
PARSER_FILES	=	parser.c redirect.c parser_utils.c parser_setup.c heredoc.c heredoc_utils.c

UTILS			=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))
UTILS_DIR		=	src/utils/
UTILS_FILES		=	utils.c split_special.c sp_utils.c print_utils.c array_handling.c

INPUT			=	$(addprefix $(INPUT_DIR), $(INPUT_FILES))
INPUT_DIR		=	src/input/
INPUT_FILES		=	input.c

SIGNAL			=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_FILES))
SIGNAL_DIR		=	src/signal/
SIGNAL_FILES	=	signal.c echo.c

HDR				=	$(addprefix $(HDR_DIR), $(HDR_DIR))
HDR_DIR			=	include/
HDR_FILES		=	minishell.h

ALL_SRC			=	$(SRC) $(EXECUTOR) $(EXPANDER) $(LEXER) $(PARSER) $(REST) $(UTILS) $(INPUT) $(SIGNAL)

################################################################################
################################################################################

OBJ_DIR			=	obj/
ALL_OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))
ALL_OBJ_DIR		=	$(sort $(dir $(ALL_OBJ)))

################################################################################
################################################################################

all: libft readline $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_DIR) $(READLINE_INCLUDE) $(LIBFT_INCLUDE)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ_DIR) $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) -o $(NAME) $(LINK_FLAGS) $(LIBFT) $(READLINE_FLAG)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@echo $(RED)"cleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR))
	@echo "cleaned"$(DEFAULT)

fclean:
	@echo $(RED)"fcleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR)) $(NAME)
	@echo "fcleaned"$(DEFAULT)

re:	fclean all

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

################################################################################
################################################################################

ffclean: fclean
	@echo $(RED)
	@echo "deleted readline"
	@echo "deleted libft"
	@rm -rf lib
	@echo $(DEFAULT)

env:
	make all && env -i ./minishell

tester:
	make re
	cd tests && bash tester.sh m

################################################################################
################################################################################

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/
LIBFT_INCLUDE	=	-I ./lib/libft

$(LIBFT):
	@git submodule init $(REDIRECT)
	@git submodule update $(REDIRECT)
	@make -C lib/libft

libft: $(LIBFT)

################################################################################
################################################################################

READLINE_VERSION=	readline-8.1.2
READLINE_LIB	=	libreadline.a
READLINE_DIR	=	lib/readline/
READLINE		=	lib/readline_out/lib/libreadline.a
READLINE_FLAG	=	-Llib/readline_out/lib -lreadline -lhistory
READLINE_INCLUDE=	-I ./lib/readline_out/include/

readline: $(READLINE)

$(READLINE):
	@echo $(LGREEN)"building readline"$(DEFAULT)
	@mkdir -p lib
	@curl -s https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz --output lib/$(READLINE_VERSION).tar.gz
	@tar xfz lib/$(READLINE_VERSION).tar.gz -C lib
	@cd lib/$(READLINE_VERSION); ./configure --prefix=$(PWD)/lib/readline_out $(REDIRECT)
	@make -C lib/$(READLINE_VERSION) $(REDIRECT)
	@make install -C lib/$(READLINE_VERSION) $(REDIRECT)
	@rm -rf lib/$(READLINE_VERSION)
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
	git clone https://github.com/mhahnFr/LeakSanitizer.git $(REDIRECT)
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer $(REDIRECT)

################################################################################
################################################################################

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

################################################################################
################################################################################

.PHONY: all clean fclean ffclean re libft readline lsan tester env
