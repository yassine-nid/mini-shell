/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:23 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/19 12:33:17 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <errno.h>
# include <signal.h>

# define DEFAULT_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
# define NOT_VALID "not a valid identifier"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	bool			is_exported;
}	t_env;

typedef enum s_type
{
	WORD,		// anything else
	PIPE,		// |
	OR,			// ||
	AND,		// &&
	OPEN_PAR,	// (
	CLOSE_PAR,	// )
	RED_IN,		// redirect input <
	RED_OUT,	// redirect ouput >
	RED_AP_OUT,	// redirect append output >>
	H_DOC		// herdoc <<
}	t_type;

typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*preveus;
	struct s_token	*next;
}	t_token;

typedef struct s_tree
{
    t_token			*node;
    struct s_tree	*left;
    struct s_tree	*right;
}	t_tree;

typedef struct s_mini
{
	t_env			**env;
	t_token			**token;
	int				exit_status;
}	t_mini;

// 1: ##################### Main #####################
void	listen_to_signals(t_mini *mini);

// 2: ################## Expander ####################
void	expand_token(t_mini *mini, t_token *token);
void	m_expand_word(t_mini *mini, t_token *token, int index);
void	m_remove_quotes(t_mini *mini, t_token *token);
void	m_expand_status(t_mini *mini, t_token *token, int index);

// 3: ############### Syntax Checker #################
int		syntax_checker(t_token *token);
int		check_word(t_token *token);
int		check_quoate(t_token *token);

// 4: ################ Commands reader ###############
void	read_commands(t_mini *mini);

// 5: ################ tokenizer #####################
void	create_tokens(t_mini *mini, char *line);
int		delimiter_check(char *line, t_type *delimiter, bool quotes);
t_token	*token_new(t_mini *mini, t_type type, char *word);
void	token_add_back(t_mini *mini, t_token *new);
void	remove_token(t_mini *mini, t_token *token);

// ##################### Env Handler #################
void	handle_env(t_mini *mini, char *env[]);
void	handle_defaults(t_mini *mini);
int		create_env(t_mini *mini, char *key, char *value, bool exported);
char	*env_atoi(char *old);
char	*get_key(char *str, bool *malloc_failed);
char	*get_value(char *str, bool *malloc_failed);


// ############################################### MODified ####################################
int		do_echo(t_token *token);
int		do_export(t_mini *mini, t_token *token);


// ############ Utils ###########
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(void *key, void *value);
void	ft_lstiter(t_env *lst, void (*f)());

bool    ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);

int		ft_putstr_fd(char *s, int fd);
bool    ft_strcmp_no_case(const char *s1, const char *s2);

bool	is_str_alpha_num(char *str);

// ############# Basic Libft ###############
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		is_alpha_num(int c);

// ############ Cleanup #############
void	clean_exit(t_mini *mini, char *error, int code);
void	cleanup_exit(t_mini *mini, int code);
void	clean_tree(t_mini *mini);
void	env_cleanup(t_mini *mini);
void	print_mini_error(t_mini *mini, char *command, char *arg, char *error);

// ########### Commands reader ###########
void	read_commands(t_mini *mini);
bool	is_space(char c);

void	token_cleanup(t_mini *mini);

// ############### TEST ################
void	print_tokens(t_mini *mini);
void	print_envs(t_mini *mini);
void	expand_tokens(t_mini *mini);
void 	printTokenTypeWithColor(t_token *token);

#endif