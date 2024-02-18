/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_getcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:39:37 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/18 14:35:36 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(t_mini *mini, t_token *token)
{
	int	nb_words;

	nb_words = 0;
	while (1)
	{
		token = get_next_arg(token);
		if (!token)
			break ;
		if (!token->is_empty)
			nb_words++;
		expand_token(mini, token);
		token = token->next;
	}
	return (nb_words);
}

char	**get_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;
	size_t	alloc_size;

	i = 0;
	alloc_size = count_words(mini, token) + 1;
	cmd = malloc(sizeof * cmd * alloc_size);
	if (!cmd)
		clean_exit(mini, NULL, errno);
	while (1)
	{
		token = get_next_arg(token);
		if (!token)
			break ;
		if (!token->is_empty)
			cmd[i++] = token->word;
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
