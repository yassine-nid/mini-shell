# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:26:27 by yzirri            #+#    #+#              #
#    Updated: 2024/01/16 08:10:11 by yzirri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = ./objects/

# -----------------------------------------
# Mandatory Varriables
# -----------------------------------------
#	-Varriables
NAME = minishell

#	-Header
HEAD_DIR = ./mandatory/includes/minishell.h

#	-Main
SRC_FILES = main.c signals_handler.c
SRC_DIR = ./mandatory/main/

#	-Utils
UTILS_FILES = utils_lst.c basic_libft.c str_utils.c basic_libft2.c
UTILS_DIR = ./mandatory/utils/

#	-Cleanup
CLEANUP_FILES = cleanup.c
CLEANUP_DIR = ./mandatory/cleanup/

#	-Commands_Reader
READER_FILES = read_commands.c tokenizer.c tokenizer_utils.c
READER_DIR = ./mandatory/commands_reader/

#	-Syntax Checker
SYNTAX_FILES = syntax_checker.c syntax_checker_helper.c
SYNTAX_DIR = ./mandatory/syntax_checker/

#	-Env Handler
ENV_FILES = env_handler.c env_defaults.c env_utils.c
ENV_DIR = ./mandatory/env_handler/

#	-Tests
TESTS_FILES = tests.c
TESTS_DIR = ./mandatory/tests/


OBJ_FILES = $(SRC_FILES:.c=.o) $(UTILS_FILES:.c=.o) $(CLEANUP_FILES:.c=.o) \
			$(READER_FILES:.c=.o) $(TESTS_FILES:.c=.o) $(SYNTAX_FILES:.c=.o) \
			$(ENV_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib -o $(NAME)

# -----------------------------------------
#	Mandatory Creating Object Files
# -----------------------------------------
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(CLEANUP_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(READER_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(SYNTAX_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(TESTS_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(ENV_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean