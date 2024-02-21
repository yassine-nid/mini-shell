/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_ismatch_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:34:08 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:33:27 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static bool	trim_start(char **token, char **dir)
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

static bool	trim_end(char **token, char **dir)
{
	int	indt;
	int	indd;

	indt = ft_strlen(*token) - 1;
	indd = ft_strlen(*dir) - 1;
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

static void	skip_asteric(char **token, char **dir)
{
	int	index;

	if (**token != '*')
		return ;
	while (**token == '*')
		(*token)++;
	while (!**token && **dir)
		(*dir)++;
	while (**dir)
	{
		index = 0;
		while (dir[0][index] && dir[0][index] == token[0][index])
			index++;
		if (token[0][index] == '*' || !token[0][index])
			break ;
		(*dir)++;
	}
}

bool	is_match(t_mini *mini, char *token, char *dir)
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
