/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:33:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/19 08:12:07 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_print(t_token	*next_token)
{
	while (next_token)
	{
		if (next_token->type != WORD)
			break ;
		ft_putstr_fd(next_token->word, 1);
		if (next_token->next != NULL && next_token->type == WORD)
			ft_putstr_fd(" ", 1);
		next_token = next_token->next;
	}
}

int	do_echo(t_token *token)
{
	bool	no_new_line;
	t_token	*next_token;

	if (write(1, "", 0) < 0)
		return (errno);
	next_token = token->next;
	if (next_token == NULL)
		return (ft_putstr_fd("\n", 1), 0);
	no_new_line = true;
	if (ft_strcmp(next_token->word, "-n"))
	{
		no_new_line = false;
		next_token = next_token->next;
	}
	do_print(next_token);
	if (no_new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
