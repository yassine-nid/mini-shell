# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:26:27 by yzirri            #+#    #+#              #
#    Updated: 2024/01/12 10:46:52 by yzirri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = ./objects/

# -----------------------------------------
# Mandatory
# -----------------------------------------
#	-Shared Varriables
NAME = minishell
HEAD_DIR = ./mandatory/includes/minishell.h

#	-Main
SRC_FILES = main.c
SRC_DIR = ./mandatory/main/

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))


all: $(NAME)

$(NAME): $(OBJ) $(GET_NEXT_LINE_OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# -----------------------------------------
#	Mandatory
# -----------------------------------------
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)%.o: $(NEXT_LINE_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)%.o: $(VALIDATOR_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(OBJ_DIR)%.o: $(GAME_LOOP_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)

bonus: $(BONUS_NAME)

re: fclean all

.PHONY: clean