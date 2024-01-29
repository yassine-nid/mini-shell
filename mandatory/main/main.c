/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/25 11:09:04 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_vars(t_mini *mini)
{
	mini->exit_status = 0;
	mini->token = NULL;
	mini->env = NULL;
	mini->std_in = dup(STDIN_FILENO); // error protection needed
	mini->std_out = dup(STDOUT_FILENO); // error protection needed
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
	cleanup_exit(&mini, 0);
	return (0);
}
