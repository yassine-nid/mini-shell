/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:09:07 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/18 12:57:11 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*alloc_new_word(t_mini *mini, char *str)
{
	char	curr_quote;
	int		ind;
	int		alloc_size;
	char	*new_str;

	alloc_size = 0;
	curr_quote = '\0';
	ind = -1;
	while (str[++ind])
	{
		if (curr_quote && str[ind] == curr_quote)
			curr_quote = '\0';
		else if (!curr_quote && (str[ind] == '\'' || str[ind] == '"'))
			curr_quote = str[ind];
		else
			alloc_size++;
	}
	new_str = malloc(sizeof * new_str * (alloc_size + 1));
	if (!new_str)
		clean_exit(mini, NULL, errno);
	new_str[alloc_size] = '\0';
	return (new_str);
}

static void	replace(t_token *token, int ind, char *new_word)
{
	new_word[ind] = '\0';
	free(token->word);
	token->word = new_word;
}

void	m_remove_quotes(t_mini *mini, t_token *token)
{
	char	*new_word;
	int		index;
	int		ind;
	char	quote;
	char	word;

	index = 0;
	ind = 0;
	quote = '\0';
	new_word = alloc_new_word(mini, token->word);
	while (token->word[index])
	{
		word = token->word[index];
		if (quote && word == quote)
			quote = '\0';
		else if (!quote && (word == '\'' || word == '"'))
			quote = word;
		else
		{
			new_word[ind] = word;
			ind++;
		}
		index++;
	}
	replace(token, ind, new_word);
}
