/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:44:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/18 15:00:48 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_token(t_mini *mini, t_token *token)
{
	int	index;

	if (token->type != WORD || !token->word)
		return ;
	index = 0;
	while (token->word[index])
	{
		if (token->word[index] == '$' && !is_s_quote(token->word, index))
		{
			if (is_alpha_num(token->word[index + 1]))
			{
				expand_word(mini, token, index);
				index = 0;
				continue ;
			}
			else if (token->word[index + 1] == '?')
			{
				expand_status(mini, token, index);
				index = 0;
				continue ;
			}
		}
		index++;
	}
	remove_quotes(mini, token);
}
