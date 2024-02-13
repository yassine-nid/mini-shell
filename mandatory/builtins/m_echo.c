/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:33:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/11 16:27:47 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_print(t_token *next_token)
{
	next_token = get_next_arg(next_token);
	while (next_token)
	{
		ft_putstr_fd(next_token->word, 1);
		next_token = get_next_arg(next_token->next);
		if (next_token)
			ft_putstr_fd(" ", 1);
	}
}

static bool	is_arg(t_token *token)
{
	int	index;

	if (!token || !token->word)
		return (false);
	index = 0;
	if (token->word[index++] == '-' && token->word[index])
	{
		while (token->word[index] == 'n')
			index++;
		if (!token->word[index])
			return (true);
	}
	return (false);
}

int	do_echo(t_token *token)
{
	bool	no_new_line;

	if (write(1, "", 0) < 0)
		return (errno);
	token = token->next;
	if (!get_next_arg(token))
		return (ft_putstr_fd("\n", 1), 0);
	no_new_line = true;
	while (is_arg(get_next_arg(token)))
	{
		no_new_line = false;
		token = token->next;
	}
	do_print(token);
	if (no_new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
