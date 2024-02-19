/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:08:16 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/19 08:56:48 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	
	if (waitpid(-1, NULL, 0) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static int	register_signal(int sig)
{
	struct sigaction	sign;

	ft_bzero(&sign, sizeof(sign));
	sign.sa_sigaction = handle_signal;
	sign.sa_flags = SA_SIGINFO;
	return (sigaction(sig, &sign, NULL));
}

void	listen_to_signals(t_mini *mini)
{
	rl_catch_signals = 0;
	if (register_signal(SIGINT) == -1)
		clean_exit(mini, "sigaction error", EXIT_FAILURE);
	if (register_signal(SIGQUIT) == -1)
		clean_exit(mini, "sigaction error", EXIT_FAILURE);
}
