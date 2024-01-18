/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:33:19 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/18 18:50:23 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_echo(t_mini *mini, t_token *token)
{
	bool	no_new_line;
	t_token	*next_token;

	next_token = token->next;
	if (next_token == NULL)
	{
		ft_putstr_fd("\n", 1);
		mini->exit_status = 0;
		return ;
	}
	no_new_line = false;
	if (ft_strcmp(next_token->word, "-n"))
	{
		no_new_line = true;
		next_token = next_token->next;
	}
	while (next_token)
	{
		ft_putstr_fd(next_token->word, 1);
		next_token = next_token->next;
	}
	if (no_new_line)
		ft_putstr_fd("\n", 1);
}
