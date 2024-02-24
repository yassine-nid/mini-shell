/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 21:44:12 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	listen_to_signales(void)
{
	signal(SIGQUIT, (void (*)(int))handle_signal);
	signal(SIGINT, (void (*)(int))handle_signal);
}

static void	handle_line(t_mini *mini, char *line)
{
	t_token	*tokens;

	create_tokens(mini, line);
	add_history(line);
	if (syntax_checker(*mini->token, mini))
	{
		printf("minishell: Syntax Error\n");
		mini->exit_status = 258;
		syntax_checker_hd(*mini->token, mini);
	}
	else
	{
		syntax_checker_hd(*mini->token, mini);
		mini->hd_index = 0;
		tokens = *mini->token;
		mini->tree = build_tree(mini->token, mini, 0);
		*mini->token = tokens;
		if (!mini->hd_signal)
			execute_tree(mini);
		else
			mini->exit_status = 1;
		free_tree(&mini->tree);
	}
}

void	read_commands(t_mini *mini)
{
	char	*line;

	while (1)
	{
		listen_to_signales();
		line = readline("minishell:$ ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			cleanup_exit(mini, mini->exit_status);
		}
		token_cleanup(mini);
		if (line[0] != '\0')
			handle_line(mini, line);
		free(line);
		line = NULL;
		mini->hd_signal = 0;
	}
}
