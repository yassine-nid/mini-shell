/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 11:49:06 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_vars(t_mini *mini)
{
	mini->exit_status = 0;
	mini->token = NULL;
	mini->env = NULL;
	mini->m_pwd = NULL;
	mini->tree = NULL;
	mini->hd_index = 0;
	mini->hd_signal = 0;
	mini->std_in = dup(STDIN_FILENO);
	mini->std_out = dup(STDOUT_FILENO);
	if (mini->std_in == -1 || mini->std_out == -1)
		clean_exit(mini, NULL, errno);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	if (!isatty(0))
		return (write(1, "tty is required\n", 16), 1);
	init_vars(&mini);
	handle_env(&mini, envp);
	read_commands(&mini);
	cleanup_exit(&mini, 0);
	return (0);
}
