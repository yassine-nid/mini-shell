/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:34:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/13 11:12:03 by yzirri           ###   ########.fr       */
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

bool	trim_start(char **token, char **dir)
{
	while (**token && **dir && **token == **dir)
	{
		if (**token == '*')
			break ;
		(*dir)++;
		(*token)++;
	}
	if (**token != '*')
		return (false);
	return (true);
}

bool	trim_end(char **token, char **dir)
{
	int indt = ft_strlen(*token) - 1;
	int indd = ft_strlen(*dir) - 1;

	while (indt >= 0 && indd >= 0 && (*token)[indt] == (*dir)[indd])
	{
		if ((*token)[indt] == '*')
			break ;
		indt--;
		indd--;
	}
	(*token)[indt + 1] = '\0';
	(*dir)[indd + 1] = '\0';
	if ((*token)[indt] != '*')
		return (false);
	return (true);
}

void	skip_asteric(char **token, char **dir)
{
	if (**token != '*')
		return ;
	while (**token == '*')
		(*token)++;
	while (!**token && **dir)
		(*dir)++;
	while (**dir)
	{
		int index = 0;
		while (dir[0][index] && dir[0][index] == token[0][index])
			index++;
		if (token[0][index] == '*' || !token[0][index])
			break ;
		(*dir)++;
	}
}

static bool	is_match(t_mini *mini, char *token, char *dir)
{
	char	*tmp_t;
	char	*tmp_d;
	bool	matched;

	tmp_t = ft_strdup(token);
	tmp_d = ft_strdup(dir);
	if (!tmp_t || !tmp_d)
	{
		free(tmp_t);
		free(tmp_d);
		clean_exit(mini, NULL, errno);
	}
	token = tmp_t;
	dir = tmp_d;
	while (1)
	{
		if (!trim_start(&token, &dir))
			break ;
		if (!trim_end(&token, &dir))
			break ;
		skip_asteric(&token, &dir);
	}
	matched = !*token && !*dir;
	return (free(tmp_t), free(tmp_d), matched);
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
    while (entry != NULL)
	{
		if (*entry->d_name != '.' && is_match(mini, token->word, entry->d_name))
		{
			t_token *new_token = token_new(mini, WORD, NULL);
			new_token->do_expand = false;
			new_token->word = ft_strdup(entry->d_name);
			if (!new_token->word)
				clean_exit(mini, NULL, errno);
			token_insert(new_token, token, level);
			level++;
		}
		entry = readdir(dir);
    }
	if (level != 0)
		token->word[0] = '\0';
    closedir(dir);
}