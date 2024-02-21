# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 15:26:27 by yzirri            #+#    #+#              #
#    Updated: 2024/02/21 16:21:18 by ynidkouc         ###   ########.fr        #
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
EXPAND_FILES = expander_quotes.c expander_word.c expander.c expand_getcmd.c \
				expander_utils.c
EXPAND_DIR = ./mandatory/expander/

#	-Syntax Checker
SYNTAX_FILES = syntax_checker.c syntax_checker_helper.c syntax_hd.c
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
UTILS_FILES = utils_lst.c basic_libft.c str_utils.c basic_libft2.c ft_split.c ft_split_utiles.c \
				basic_libft_3.c
UTILS_DIR = ./mandatory/utils/

#	-Cleanup
CLEANUP_FILES = cleanup.c cleanup_2.c
CLEANUP_DIR = ./mandatory/cleanup/

#	-Env Handler
ENV_FILES = env_handler.c env_defaults.c env_utils.c
ENV_DIR = ./mandatory/env_handler/

#	-builtins
BUILTIN_FILES = builtins_utils.c m_cd.c m_echo.c m_env.c m_exit.c m_export.c \
				m_pwd_init.c m_pwd.c m_unset.c
BUILTIN_DIR = ./mandatory/builtins/

#	-Execution
EXECUTION_FILES =	execute_cmd.c  execute_pipe.c execute_tree.c \
					redaractions.c child_exe.c execute_helpers.c here_doc.c excution_utils.c
EXECUTION_DIR = ./mandatory/execution/


OBJ_FILES = $(SRC_FILES:.c=.o) $(UTILS_FILES:.c=.o) $(CLEANUP_FILES:.c=.o) \
			$(READER_FILES:.c=.o) $(SYNTAX_FILES:.c=.o) \
			$(ENV_FILES:.c=.o) $(EXPAND_FILES:.c=.o) $(BUILTIN_FILES:.c=.o) \
			$(TOKENIZER_FILES:.c=.o) $(TREE_FILES:.c=.o) $(EXECUTION_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# -----------------------------------------
# BONUS Varriables
# -----------------------------------------
#	-Varriables

NAME_BONUS = minishell_bonus

#	-Header
HEAD_DIR_BONUS = ./bonus/includes/minishell_bonus.h

#	-Main
SRC_FILES_BONUS = main_bonus.c signals_handler_bonus.c
SRC_DIR_BONUS = ./bonus/main/

#	-Expander
EXPAND_FILES_BONUS = expand_star_bonus.c expander_quotes_bonus.c expander_word_bonus.c expander_bonus.c expand_getcmd_bonus.c \
				expand_star_ismatch_bonus.c expand_star_sort_bonus.c expander_utils_bonus.c
EXPAND_DIR_BONUS = ./bonus/expander/

#	-Syntax Checker
SYNTAX_FILES_BONUS = syntax_checker_bonus.c syntax_checker_helper_bonus.c syntax_hd_bonus.c
SYNTAX_DIR_BONUS = ./bonus/syntax_checker/

#	-Commands_Reader
READER_FILES_BONUS = read_commands_bonus.c
READER_DIR_BONUS = ./bonus/commands_reader/

#	-Tokenizer
TOKENIZER_FILES_BONUS = tokenizer_utils_bonus.c tokenizer_bonus.c
TOKENIZER_DIR_BONUS = ./bonus/tokenizer/

#	-Build Tree
TREE_FILES_BONUS = build_tree_bonus.c build_tree_helpers_bonus.c
TREE_DIR_BONUS = ./bonus/build_tree/

########################################
#	-Utils
UTILS_FILES_BONUS = utils_lst_bonus.c basic_libft_bonus.c str_utils_bonus.c basic_libft2_bonus.c ft_split_bonus.c ft_split_utiles_bonus.c \
				basic_libft_3_bonus.c
UTILS_DIR_BONUS = ./bonus/utils/

#	-Cleanup
CLEANUP_FILES_BONUS = cleanup_bonus.c cleanup_2_bonus.c
CLEANUP_DIR_BONUS = ./bonus/cleanup/

#	-Env Handler
ENV_FILES_BONUS = env_handler_bonus.c env_defaults_bonus.c env_utils_bonus.c
ENV_DIR_BONUS = ./bonus/env_handler/

#	-builtins
BUILTIN_FILES_BONUS = builtins_utils_bonus.c m_cd_bonus.c m_echo_bonus.c m_env_bonus.c m_exit_bonus.c m_export_bonus.c \
				m_pwd_init_bonus.c m_pwd_bonus.c m_unset_bonus.c
BUILTIN_DIR_BONUS = ./bonus/builtins/

#	-Execution
EXECUTION_FILES_BONUS =	execute_and_bonus.c  execute_cmd_bonus.c  execute_or_bonus.c   execute_pipe_bonus.c execute_tree_bonus.c \
					redaractions_bonus.c child_exe_bonus.c execute_helpers_bonus.c here_doc_bonus.c excution_utils_bonus.c
EXECUTION_DIR_BONUS = ./bonus/execution/


OBJ_FILES_BONUS = $(SRC_FILES_BONUS:_bonus.c=_bonus.o) $(UTILS_FILES_BONUS:_bonus.c=_bonus.o) $(CLEANUP_FILES_BONUS:_bonus.c=_bonus.o) \
			$(READER_FILES_BONUS:_bonus.c=_bonus.o) $(SYNTAX_FILES_BONUS:_bonus.c=_bonus.o) \
			$(ENV_FILES_BONUS:_bonus.c=_bonus.o) $(EXPAND_FILES_BONUS:_bonus.c=_bonus.o) $(BUILTIN_FILES_BONUS:_bonus.c=_bonus.o) \
			$(TOKENIZER_FILES_BONUS:_bonus.c=_bonus.o) $(TREE_FILES_BONUS:_bonus.c=_bonus.o) $(EXECUTION_FILES_BONUS:_bonus.c=_bonus.o)
OBJ_BONUS = $(addprefix $(OBJ_DIR), $(OBJ_FILES_BONUS))

PRJ_MAME = "\n"\
	"███╗   ███╗ █████╗ ███████╗██╗      █████╗ ██████╗  █████╗       ███████╗██╗  ██╗███████╗██╗     ██╗     \n"\
	"████╗ ████║██╔══██╗╚════██║██║     ██╔══██╗██╔══██╗██╔══██╗      ██╔════╝██║  ██║██╔════╝██║     ██║     \n"\
	"██╔████╔██║███████║    ██╔╝██║     ███████║██████╔╝███████║█████╗███████╗███████║█████╗  ██║     ██║     \n"\
	"██║╚██╔╝██║██╔══██║   ██╔╝ ██║     ██╔══██║██╔══██╗██╔══██║╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     \n"\
	"██║ ╚═╝ ██║██║  ██║   ██║  ███████╗██║  ██║██████╔╝██║  ██║      ███████║██║  ██║███████╗███████╗███████╗\n"\
	"╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝  ╚══════╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝      ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"\

PRJ_MAME_BONUS = "\n"\
	"███╗   ███╗ █████╗ ███████╗██╗      █████╗ ██████╗  █████╗       ███████╗██╗  ██╗███████╗██╗     ██╗     \n"\
	"████╗ ████║██╔══██╗╚════██║██║     ██╔══██╗██╔══██╗██╔══██╗      ██╔════╝██║  ██║██╔════╝██║     ██║     \n"\
	"██╔████╔██║███████║    ██╔╝██║     ███████║██████╔╝███████║█████╗███████╗███████║█████╗  ██║     ██║     \n"\
	"██║╚██╔╝██║██╔══██║   ██╔╝ ██║     ██╔══██║██╔══██╗██╔══██║╚════╝╚════██║██╔══██║██╔══╝  ██║     ██║     \n"\
	"██║ ╚═╝ ██║██║  ██║   ██║  ███████╗██║  ██║██████╔╝██║  ██║      ███████║██║  ██║███████╗███████╗███████╗\n"\
	"╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝  ╚══════╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝      ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ BONUS\n"\


all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	@echo $(PRJ_MAME)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
	@echo $(PRJ_MAME_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -lreadline -L ~/.brew/opt/readline/lib -o $(NAME_BONUS)
	
# -----------------------------------------
#	BONUS Creating Object Files
# -----------------------------------------
$(OBJ_DIR)%_bonus.o: $(SRC_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(UTILS_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(CLEANUP_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(READER_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(SYNTAX_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(ENV_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(BUILTIN_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(EXPAND_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(TOKENIZER_DIR_BONUS)%_bonus.c $(HEAD_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(TREE_DIR_BONUS)%_bonus.c $(TREE_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%_bonus.o: $(EXECUTION_DIR_BONUS)%_bonus.c $(EXECUTION_DIR_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include
# -----------------------------------------
#	Mandatory Creating Object Files
# -----------------------------------------
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(CLEANUP_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(READER_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(SYNTAX_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(ENV_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(EXPAND_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(TOKENIZER_DIR)%.c $(HEAD_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(TREE_DIR)%.c $(TREE_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

$(OBJ_DIR)%.o: $(EXECUTION_DIR)%.c $(EXECUTION_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ~/.brew/opt/readline/include

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean