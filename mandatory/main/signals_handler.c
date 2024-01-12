/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:08:16 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/12 16:28:31 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sigint_count;

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
		sigint_count++;
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
	if (register_signal(SIGINT) == -1)
		clean_exit(mini, "sigaction error");
}