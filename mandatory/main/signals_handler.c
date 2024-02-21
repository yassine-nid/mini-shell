/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:08:16 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 08:39:52 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int sig, t_mini *mini)
{
	static t_mini	*m_mini;

	if (sig == 269)
	{
		m_mini = mini;
		return ;
	}
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		m_mini->sig_int_recived = 0;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
