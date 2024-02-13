/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/13 11:08:40 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_vars(t_mini *mini)
{
	mini->exit_status = 0;
	mini->token = NULL;
	mini->env = NULL;
	mini->std_in = dup(STDIN_FILENO);
	if (mini->std_in == -1)
		clean_exit(mini, NULL, errno);
	mini->std_out = dup(STDOUT_FILENO);
	if (mini->std_out == -1)
		clean_exit(mini, NULL, errno);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	if (!isatty(0))
		return (printf("tty is required\n"), errno);
	init_vars(&mini);
	handle_env(&mini, envp);
	listen_to_signals(&mini);
	read_commands(&mini);
	cleanup_exit(&mini, 0);
	return (0);
}
