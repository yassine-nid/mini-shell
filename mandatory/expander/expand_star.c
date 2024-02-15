/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:34:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/15 10:48:09 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_skip(t_token *token)
{
	int	index;

	index = 0;
	if (!token || !token->word)
		return (true);
	while (token->word[index] && token->word[index] != '*')
		index++;
	return (token->word[index] != '*');
}

static void	remove_empty_stars(t_token *token)
{
	int	index;
	int	index_j;

	index = -1;
	while (token->word[++index])
	{
		if (token->word[index] == '$' && token->word[index + 1] == '*')
		{
			index_j = index;
			index += 2;
			while (token->word[index_j])
			{
				token->word[index_j] =  token->word[index];
				index_j++;
				index++;
			}
			index = -1;
		}
	}
}

void	m_expand_star(t_mini *mini, t_token *token)
{
	DIR				*dir;
	struct dirent	*entry;

	if (is_skip(token))
		return ;
	remove_empty_stars(token);
	dir = opendir(".");
	if (dir == NULL)
		return ;
	entry = readdir(dir);
	int level = 0;
	t_token *first = NULL;
    while (entry != NULL)
	{
		if (*entry->d_name != '.' && is_match(mini, token->word, entry->d_name))
		{
			t_token *new_token = token_new(mini, WORD, NULL);
			new_token->do_expand = false;
			new_token->word = ft_strdup(entry->d_name);
			if (!new_token->word)
				clean_exit(mini, NULL, errno);
			token_insert(new_token, token, level++);
			if (!first)
				first = new_token;
		}
		entry = readdir(dir);
    }
	star_sort(level, token);
	closedir(dir);
}