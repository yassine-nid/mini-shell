/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:05:20 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/11 10:12:51 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_token(t_mini *mini)
{
	token_cleanup(mini);
	mini->token = malloc(sizeof * mini->token);
	if (!mini->token)
		clean_exit(mini, NULL, errno);
	*mini->token = NULL;
}

static int	get_word_len(char *line)
{
	int		size;
	bool	is_out;
	t_type	delim;
	char	quote;

	size = 0;
	is_out = true;
	while (*line)
	{
		if (!is_out && *line == quote)
			is_out = true;
		else if (is_out && (*line == '\'' || *line == '"'))
		{
			quote = '"';
			if (*line == '\'')
				quote = '\'';
			is_out = false;
		}
		if (is_out && delimiter_check(line, &delim, false))
			break ;
		size++;
		line++;
	}
	return (size);
}

static int	token_word(t_mini *mini, char *line, t_token *token)
{
	int	size;
	int	index;

	size = get_word_len(line);
	token->word = malloc(sizeof * token->word * (size + 1));
	if (!token->word)
		clean_exit(mini, NULL, errno);
	index = size;
	token->word[size] = '\0';
	while (--size >= 0)
		token->word[size] = line[size];
	return (index);
}

static int	populate_token(t_mini *mini, t_token *new_token, char *line)
{
	int		delim_check;
	t_type	delim_type;

	delim_check = delimiter_check(line, &delim_type, true);
	if (delim_check == 0 || *line == '"' || *line == '\'')
		return (token_word(mini, line, new_token));
	new_token->type = delim_type;
	return (delim_check);
}

void	create_tokens(t_mini *mini, char *line)
{
	t_token	*new_token;
	int		index;

	init_token(mini);
	index = 0;
	while (line[index])
	{
		while (is_space(line[index]))
			index++;
		if (!line[index])
			break ;
		new_token = token_new(mini, WORD, NULL);
		if (!new_token)
			clean_exit(mini, NULL, errno);
		new_token->do_expand = true;
		token_add_back(mini, new_token);
		index += populate_token(mini, new_token, &line[index]);
	}
}
