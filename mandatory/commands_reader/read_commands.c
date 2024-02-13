/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/12 14:04:19 by ynidkouc         ###   ########.fr       */
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
			// print_tokens(mini);
			if (syntax_checker(*mini->token))
				printf("Syntax Error\n");
			// else
			// 	printf("Syntax Correct\n");
			// print env
			// if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't')
			// 	clean_exit(mini, "test", 69);
			// if (line[0] == 'l' && line[1] == 'e' && line[2] == 'a' && line[3] == 'k')
			// 	system("leaks minishell");
			// if (line[0] == 'e' && line[1] == 'n' && line[2] == 'v')
			// 	print_envs(mini);
			// expand_tokens(mini);
			// print_tokens(mini);
			add_history(line);

			// bool reseted = true;
			// t_token *token = *mini->token;
			// while (token)
			// {
			// 	if (token->type == WORD && reseted)
			// 	{
			// 		if (ft_strcmp_no_case(token->word, "echo"))
			// 			mini->exit_status = do_echo(token);
			// 		if (ft_strcmp(token->word, "export"))
			// 			mini->exit_status = do_export(mini, token);
			// 		reseted = false;
			// 	}
			// 	if (token->type != WORD)
			// 		reseted = true;
			// 	token = token->next;
			// }
			t_token *tokens = *mini->token;
			mini->tree = build_tree(mini->token, mini, 0);
			*mini->token = tokens;
			// print_tree(mini->tree, 0);
			execute_tree(mini);
			free_tree(&mini->tree);
		}
		free(line);
		line = NULL;
	}
}
