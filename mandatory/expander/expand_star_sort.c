/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:05:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/15 10:31:17 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_token(t_token *token)
{
	t_token	*first;

	first = token->next;
	free(token->word);
	token->word = first->word;
	token->next = first->next;
	if (token->next)
		token->next->preveus = token;
	free(first);
}

static int	m_cmp(const char *s1, const char *s2)
{
    if (s1 && !s2)
        return (1);
	else if (!s1 && s2)
		return (-1);
	else if (!s1 && !s2)
		return (0);
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

static bool	unit_sort(int lvl, t_token *current_token)
{
	int		current_lvl;
	char	*temp_word;
	t_token	*compare_token;

	compare_token = current_token->next;
	current_lvl = 0;
	while (compare_token && current_lvl <= lvl)
	{
		if (m_cmp(compare_token->word, current_token->word) < 0)
		{
			temp_word = compare_token->word;
			compare_token->word = current_token->word;
			current_token->word = temp_word;
			return (false);
		}
		current_lvl++;
		compare_token = compare_token->next;
	}
	return (true);
}

void	star_sort(int lvl, t_token *token)
{
	t_token	*current_token;
	int		current_lvl;

	if (lvl == 0)
		return ;
	current_lvl = 0;
	current_token = token->next;
	while (current_token && current_lvl <= lvl)
	{
		current_lvl++;
		if (!unit_sort(current_lvl, current_token))
		{
			current_token = token->next;
			current_lvl = 0;
		}
		else
			current_token = current_token->next;
	}
	clean_token(token);
}
