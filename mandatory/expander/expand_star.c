/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:34:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/16 14:31:06 by yzirri           ###   ########.fr       */
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
	int	old_index;

	index = -1;
	while (token->word[++index])
	{
		if (token->word[index] == '$' && token->word[index + 1] == '*')
		{
			old_index = index;
			index_j = index;
			index += 2;
			while (token->word[index_j])
			{
				token->word[index_j] = token->word[index];
				index_j++;
				index++;
			}
			index = old_index;
		}
	}
}

static void	read_directory(t_mini *mini, t_token *token, DIR *dir, int *level)
{
	struct dirent	*entry;
	t_token			*new_token;

	*level = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			return ;
		if (*entry->d_name == '.')
			continue ;
		if (!is_match(mini, token->word, entry->d_name))
			continue ;
		new_token = token_new(mini, WORD, NULL);
		new_token->do_expand = false;
		new_token->word = ft_strdup(entry->d_name);
		if (!new_token->word)
		{
			closedir(dir);
			clean_exit(mini, NULL, errno);
		}
		token_insert(new_token, token, *level);
		*level = *level + 1;
	}
}

void	m_expand_star(t_mini *mini, t_token *token)
{
	int				level;
	DIR				*dir;

	if (is_skip(token))
		return ;
	remove_empty_stars(token);
	dir = opendir(".");
	if (dir == NULL)
		return ;
	read_directory(mini, token, dir, &level);
	star_sort(level, token);
	closedir(dir);
}
