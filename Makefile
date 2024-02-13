# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:26:27 by yzirri            #+#    #+#              #
#    Updated: 2024/02/13 13:39:55 by yzirri           ###   ########.fr        #
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

#	-Expander
EXPAND_FILES = expand_star.c expander_quotes.c expander_word.c expander.c expand_getcmd.c
EXPAND_DIR = ./mandatory/expander/

#	-Syntax Checker
SYNTAX_FILES = syntax_checker.c syntax_checker_helper.c
SYNTAX_DIR = ./mandatory/syntax_checker/

#	-Commands_Reader
READER_FILES = read_commands.c
READER_DIR = ./mandatory/commands_reader/

#	-Tokenizer
TOKENIZER_FILES = tokenizer_utils.c tokenizer.c
TOKENIZER_DIR = ./mandatory/tokenizer/

#	-Build Tree
TREE_FILES = build_tree.c build_tree_helpers.c
TREE_DIR = ./mandatory/build_tree/

########################################
#	-Utils
UTILS_FILES = utils_lst.c basic_libft.c str_utils.c basic_libft2.c ft_split.c ft_split_utiles.c
UTILS_DIR = ./mandatory/utils/

#	-Cleanup
CLEANUP_FILES = cleanup.c
CLEANUP_DIR = ./mandatory/cleanup/

#	-Env Handler
ENV_FILES = env_handler.c env_defaults.c env_utils.c
ENV_DIR = ./mandatory/env_handler/

#	-builtins
BUILTIN_FILES = builtins_utils.c m_cd.c m_echo.c m_env.c m_exit.c m_export.c \
				m_pwd_init.c m_pwd.c m_unset.c
BUILTIN_DIR = ./mandatory/builtins/

#	-Execution
EXECUTION_FILES =	execute_and.c  execute_cmd.c  execute_or.c   execute_pipe.c execute_tree.c \
					redaractions.c child_exe.c execute_helpers.c here_doc.c excution_utils.c
EXECUTION_DIR = ./mandatory/execution/


OBJ_FILES = $(SRC_FILES:.c=.o) $(UTILS_FILES:.c=.o) $(CLEANUP_FILES:.c=.o) \
			$(READER_FILES:.c=.o) $(SYNTAX_FILES:.c=.o) \
			$(ENV_FILES:.c=.o) $(EXPAND_FILES:.c=.o) $(BUILTIN_FILES:.c=.o) \
			$(TOKENIZER_FILES:.c=.o) $(TREE_FILES:.c=.o) $(EXECUTION_FILES:.c=.o)
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

$(OBJ_DIR)%.o: $(ENV_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(EXPAND_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(TOKENIZER_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(TREE_DIR)%.c $(TREE_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(EXECUTION_DIR)%.c $(EXECUTION_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean