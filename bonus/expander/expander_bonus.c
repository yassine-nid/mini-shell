/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:44:02 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 22:10:22 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static bool	expand_varriable(t_mini *mini, t_token *token, int index, int *d_in)
{
	char	*word;

	word = token->word;
	if (word[index] == '$' && !is_inside_quote(word, index, single_q))
	{
		*d_in = index;
		if (is_alpha_num(word[index + 1]))
		{
			token->was_env = true;
			return (m_expand_word(mini, token, index), true);
		}
		else if (word[index + 1] == '?')
			return (m_expand_status(mini, token, index), true);
	}
	return (false);
}

static void	get_range(t_token *token, int *index, int *s_index, int *e_index)
{
	while (is_space(token->word[*index]))
		*index = *index + 1;
	*s_index = *index;
	while (token->word[*index])
	{
		if (!is_inside_quote(token->word, *index, any_q)
			&& is_space(token->word[*index]))
		{
			break ;
		}
		*index = *index + 1;
	}
	*e_index = *index;
}

static void	remove_first_expanded(t_token *token)
{
	t_token	*temp;

	temp = token->next;
	free(token->word);
	token->word = token->next->word;
	if (token->next->next)
		token->next->next->preveus = token;
	token->next = token->next->next;
	token->was_env = true;
	free(temp);
}

static void	token_separate(t_mini *mini, t_token *token, int lvl, int start_i)
{
	t_token	*new_token;
	int		end_index;
	int		index;
	int		alloc_size;
	int		new_index;

	index = 0;
	lvl = 0;
	while (token->word[index])
	{
		get_range(token, &index, &start_i, &end_index);
		new_token = token_new(mini, WORD, NULL);
		token_insert(new_token, token, lvl++);
		alloc_size = end_index - start_i;
		new_token->word = malloc(sizeof * new_token->word * (alloc_size + 1));
		if (!new_token->word)
			clean_exit(mini, NULL, errno);
		new_token->was_env = true;
		new_index = 0;
		while (start_i < end_index)
			new_token->word[new_index++] = token->word[start_i++];
		new_token->word[new_index++] = '\0';
	}
	if (lvl != 0)
		remove_first_expanded(token);
}

void	expand_token(t_mini *mini, t_token *token, bool exp_star, bool seperte)
{
	int	index;
	int	dollar_loca;

	if (token->type != WORD || !token->word || !token->do_expand)
		return ;
	index = 0;
	dollar_loca = 0;
	while (token->word[index])
	{
		if (expand_varriable(mini, token, index, &dollar_loca))
		{
			index = dollar_loca;
			continue ;
		}
		index++;
	}
	if (seperte)
		token_separate(mini, token, 0, 0);
	flag_empty_tokens(token);
	remove_empty_quotes(token);
	if (exp_star)
		m_expand_star(mini, token);
	m_remove_quotes(mini, token);
	restore_token(token);
}
