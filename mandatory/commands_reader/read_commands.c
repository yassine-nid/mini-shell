/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/13 14:41:53 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool is_delimiter(char *line, t_type *delimiter)
{
	if (*line == '|' && *(line++) == '|')
		return (*delimiter = OR, true);
	if (*line == '|')
		return (*delimiter = PIPE, true);
	return (false);
}

static t_token *get_next_token(t_mini *mini, char *line, int *index)
{
	t_token	*token;

	token = malloc(sizeof * token);
	if (!token)
		clean_exit(mini, "malloc");
	
	// if token the create a token
	return (NULL);
}

static void tokenize(t_mini *mini, char *line)
{
	printf("%s\n", line);
	int index = 0;
	while(line[index])
		get_next_token(mini, line, &index);
}

static void	new_prompt(t_mini *mini)
{
	char *line = readline("minishell:$ ");
	if (line == NULL)
		clean_exit(mini, "test");
	if (line[0] != '\0')
	{
		tokenize(mini, line);
		add_history(line);
	}
	free(line);
	line = NULL;
}

void	read_commands(t_mini *mini)
{
	(void)mini;
	while (1)
		new_prompt(mini);
}