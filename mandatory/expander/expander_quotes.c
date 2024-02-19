/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:09:07 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/19 08:48:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	remove_quote(int index, int start_index, t_token *token)
{
	int	save_index;

	while (start_index + 1 < index)
	{
		token->word[start_index] = token->word[start_index + 1];
		start_index++;
	}
	index++;
	save_index = index - 2;
	while (token->word[index])
		token->word[start_index++] = token->word[index++];
	token->word[start_index] = '\0';
	return (save_index);
}

void	m_remove_quotes(t_mini *mini, t_token *token)
{
	char	c_quote;
	int		index;
	int		start_index;

	(void)mini;
	c_quote = '\0';
	index = 0;
	while (token->word && token->word[index])
	{
		if (c_quote && token->word[index] == c_quote)
		{
			c_quote = '\0';
			index = remove_quote(index, start_index, token);
			continue ;
		}
		else if (!c_quote && (token->word[index] == '\''
				|| token->word[index] == '"'))
		{
			c_quote = token->word[index];
			start_index = index;
		}
		index++;
	}
}
