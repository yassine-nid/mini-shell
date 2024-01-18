/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/18 10:23:14 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_token(t_mini *mini)
{
	token_cleanup(mini);
	mini->token = malloc(sizeof * mini->token);
	if (!mini->token)
		clean_exit(mini, NULL, errno);
	*mini->token = NULL;
}

static void	create_tokens(t_mini *mini, char *line)
{
	t_token	*new_token;
	t_type	delim_type;
	int		index;
	int		delim_check;

	init_token(mini);
	index = 0;
	while (line[index])
	{
		while (is_space(line[index]))
			index++;
		if (!line[index])
			break ;
		new_token = token_new(mini, WORD, NULL);
		if (!new_token)
			clean_exit(mini, NULL, errno);
		token_add_back(mini, new_token);
		delim_check = delimiter_check(&line[index], &delim_type, true);
		if (delim_check == 0 || line[index] == '"' || line[index] == '\'')
			index += token_word(mini, &line[index], new_token);
		else
		{
			new_token->type = delim_type;
			index += delim_check;
		}
	}
}

void	read_commands(t_mini *mini)
{
	char	*line;

	while (1)
	{
		line = readline("minishell:$ ");
		if (line == NULL)
			cleanup_exit(mini, 10);
		if (line[0] != '\0')
		{
			create_tokens(mini, line);
			print_tokens(mini);
			if (syntax_checker(*mini->token))
				printf("Syntax Error\n");
			else
				printf("Syntax Correct\n");
			// print env
			if (line[0] == 'e' && line[1] == 'n' && line[2] == 'v')
				print_envs(mini);
			expand_tokens(mini);
			print_tokens(mini);
			add_history(line);
		}
		free(line);
		line = NULL;
	}
}