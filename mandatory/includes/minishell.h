/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:23 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/15 11:15:45 by ynidkouc         ###   ########.fr       */
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

typedef struct s_env
{
	char			*origin;
	char			*key;
	char			*value;
	struct s_env	*next;
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

typedef struct s_mini
{
	t_env			**env;
	t_token			**token;
}	t_mini;

void	main_init(t_mini *mini, char *env[]);
void	listen_to_signals(t_mini *mini);

// ########## Utils #########
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(void *key, void *value, void *origin);
void	ft_lstiter(t_env *lst, void (*f)());

// Basic Libft
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);

// ########## Cleanup #########
void	clean_exit(t_mini *mini, char *error, int code);
void	cleanup_exit(t_mini *mini, int code);

// ######### Commands reader #########
void	read_commands(t_mini *mini);
t_token	*token_new(t_mini *mini, t_type type, char *word);
void	token_add_back(t_mini *mini, t_token *new);
bool	is_space(char c);

void	token_cleanup(t_mini *mini);
int		delimiter_check(char *line, t_type *delimiter, bool quotes);
int		token_word(t_mini *mini, char *line, t_token *token);

// ############### Syntax Checker ################
int		syntax_checker(t_token *token);
int		check_word(t_token *token);
int		check_quoate(t_token *token);

// ############### TEST ################
void	print_tokens(t_mini *mini);

#endif