# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/01/27 18:23:58 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= Minishell
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRC				= src/1folder/11file.c src/1folder/12file.c src/2folder/21file.c src/2folder/22file.c src/main.c
SRC_FILES		= 
SRC_DIR			= src

OBJ				= $(FILES:.c=.o)
OBJ_DIR			= obj

ALL_FILES		= $(notdir $(SRC))
FILES			= $(addprefix $(OBJ_DIR)/, $(ALL_FILES))

all:			obj_dir $(NAME)
				
$(NAME):		$(OBJ)
				$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJ)
				@$(RM) -r $(OBJ_DIR)
				@echo "cleaned $(NAME)"

fclean:			
				@make clean
				@$(RM) $(NAME)
				@echo "fcleaned $(NAME)"

re:
				@make fclean
				@make all

obj_dir:
				@mkdir -p $(OBJ_DIR)

.PHONY:			all clean fclean re obj_dir

test:
				@echo $(OBJ)
				@echo $(FILES)
				
GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

#				@echo $(LGREEN)Compiling$(DEFAULT) $<
#				@echo $(GREEN)Compiled$(DEFAULT) $@
