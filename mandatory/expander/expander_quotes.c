/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:09:07 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/18 13:32:33 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	m_remove_quotes(t_mini *mini, t_token *token)
{
	(void)mini;
	(void)token;
	int	index = 0;

	char current_quote = '\0';
	int	start_index;

	while (token->word && token->word[index])
	{
		if (current_quote && token->word[index] == current_quote)
		{
			current_quote = '\0';
			printf("string 1 [%s]\n", token->word);
			while (start_index + 1 < index)
			{
				printf("copying Index [%d->%c], to [%d->%c]\n",
				(start_index + 1), token->word[start_index + 1], start_index, token->word[start_index]);
				token->word[start_index] = token->word[start_index + 1];
				start_index++;
			}
			printf("string 2 [%s]\n", token->word);
			printf("string 2.1 index <%c>\n", token->word[index]);
			index++;
			printf("string 2.2 index++ <%c>\n", token->word[index]);
			int save_index = index - 2;
			printf("string 2.3 savedindex <%c>\n", token->word[save_index]);
			while (token->word[index])
				token->word[start_index++] = token->word[index++];
			token->word[start_index] = '\0';
			printf("string 2.4 savedindex <%c>\n", token->word[save_index]);
			printf("string 3 [%s]\n", token->word);
			index = save_index;
			continue ;
		}
		else if (!current_quote && (token->word[index] == '\'' || token->word[index] == '"'))
		{
			current_quote = token->word[index];
			start_index = index;
		}
		index++;
	}
	
}
