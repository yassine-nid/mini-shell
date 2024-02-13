/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:44:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/11 12:54:21 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_inside_single_quote(char *str, int index)
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
			return (curr_quote && curr_quote == '\'');
		ind++;
	}
	return (false);
}

// static void	remove_empty_words(t_mini *mini)
// {
// 	t_token	*token;

// 	if (!mini || !mini->token)
// 		return ;
// 	token = *mini->token;
// 	while (token)
// 	{
// 		if (token->type == WORD && (!token->word || !token->word[0]))
// 		{
// 			remove_token(mini, token);
// 			token = *mini->token;
// 			continue ;
// 		}
// 		token = token->next;
// 	}
// }

static bool	expand_varriable(t_mini *mini, t_token *token, int index, int *d_in)
{
	char	*word;

	word = token->word;
	if (word[index] == '$' && !is_inside_single_quote(word, index))
	{
		*d_in = index;
		if (is_alpha_num(word[index + 1]))
			return (m_expand_word(mini, token, index), true);
		else if (word[index + 1] == '?')
			return (m_expand_status(mini, token, index), true);
	}
	return (false);
}

void	expand_token(t_mini *mini, t_token *token)
{
	int	index;
	int	dollar_loca;

	if (token->type != WORD || !token->word || !token->do_expand)
		return ;
	index = 0;
	dollar_loca = 0;
	m_expand_star(mini, token);
	while (token->word[index])
	{
		if (expand_varriable(mini, token, index, &dollar_loca))
		{
			index = dollar_loca;
			continue ;
		}
		index++;
	}
	m_remove_quotes(mini, token);
	// remove_empty_words(mini);
}
