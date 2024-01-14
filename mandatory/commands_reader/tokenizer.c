/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:05:20 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/14 17:47:27 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_word_len(char *line)
{
	int		size;
	bool	is_out;
	t_type	delim;
	char	end;

	size = 0;
	is_out = true;
	while (*line)
	{
		if (!is_out && *line == end)
			is_out = true;
		else if (is_out && (*line == '\'' || *line == '"'))
		{
			end = '"';
			if (*line == '\'')
				end = '\'';
			is_out = false;
		}
		if (is_out && delimiter_check(line, &delim, false))
			break ;
		size++;
		line++;
	}
	return (size);
}

int	token_word(t_mini *mini, char *line, t_token *token)
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

