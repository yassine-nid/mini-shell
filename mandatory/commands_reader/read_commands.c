/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/19 08:55:36 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_commands(t_mini *mini)
{
	char	*line;

	while (1)
	{
		line = readline("minishell:$ ");
		if (line == NULL)
			cleanup_exit(mini, 10);
		token_cleanup(mini);
		if (line[0] != '\0')
		{
			create_tokens(mini, line);
			add_history(line);
			if (syntax_checker(*mini->token))
			{
				printf("minishell: Syntax Error\n");
				mini->exit_status = 258;
			}
			else
			{
				t_token *tokens = *mini->token;
				mini->tree = build_tree(mini->token, mini, 0);
				*mini->token = tokens;
				execute_tree(mini);
				free_tree(&mini->tree);
			}
		}
		free(line);
		line = NULL;
	}
}
