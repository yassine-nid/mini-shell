/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:34:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/26 12:28:57 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_exit(t_mini *mini, t_token *token, int lvl)
{
	if (token)
		token = token->next;
	if (token && token->type == WORD && token->word)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (lvl == 0)
		ft_putstr_fd("exit\n", 1);
	cleanup_exit(mini, 0);
	return (0);
}
