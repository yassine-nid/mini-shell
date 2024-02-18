/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:21:52 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/18 11:44:53 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_empty_quotes(t_token *t)
{
	int		index;
	char	cu_qou;
	int		start_index;

	index = -1;
	cu_qou = '\0';
	while (t->word[++index])
	{
		if (cu_qou && t->word[index] == cu_qou)
		{
			cu_qou = '\0';
			if (index - start_index == 1)
			{
				while (t->word[++index])
					t->word[start_index++] = t->word[index];
				t->word[start_index] = 0;
				index = -1;
			}
		}
		else if (!cu_qou && (t->word[index] == '\'' || t->word[index] == '"'))
		{
			cu_qou = t->word[index];
			start_index = index;
		}
	}
}

void	flag_empty_tokens(t_token *token)
{
	bool	is_empty;
	int		index;

	while (token)
	{
		is_empty = true;
		index = 0;
		while (!token->is_empty && token->word[index])
		{
			if (!is_space(token->word[index]))
			{
				is_empty = false;
				break ;
			}
			index++;
		}
		token->is_empty = is_empty;
		token = token->next;
	}
}

bool	is_inside_quote(char *str, int index, t_quote_type type)
{
	char	curr_quote;
	int		ind;

	ind = 0;
	curr_quote = '\0';
	while (str[ind])
	{
		if (curr_quote && str[ind] == curr_quote)
			curr_quote = '\0';
		else if (!curr_quote && (str[ind] == '\'' || str[ind] == '"'))
			curr_quote = str[ind];
		if (ind == index)
		{
			if (type == double_q)
				return (curr_quote == '"');
			if (type == single_q)
				return (curr_quote == '\'');
			return (curr_quote == '"' || curr_quote == '\'');
		}
		ind++;
	}
	return (false);
}
