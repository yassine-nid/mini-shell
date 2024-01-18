/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/18 17:33:09 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_vars(t_mini *mini)
{
	mini->exit_status = 0;
	mini->token = NULL;
	mini->env = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	init_vars(&mini);
	handle_env(&mini, envp);
	listen_to_signals(&mini);
	read_commands(&mini);
	return (0);
}
