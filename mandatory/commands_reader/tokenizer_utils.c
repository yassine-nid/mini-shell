/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:05:55 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/14 17:21:21 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_new(t_mini *mini, t_type type, char *word)
{
	t_token	*result;

	result = malloc (sizeof * result);
	if (result == NULL)
		clean_exit(mini,  NULL, errno);
	result->next = NULL;
	result->preveus = NULL;
	result->type = type;
	result->word = word;
	return (result);
}

void	token_add_back(t_mini *mini, t_token *new)
{
	t_token	*temp_lst;

	temp_lst = *mini->token;
	if (temp_lst == NULL)
	{
		*mini->token = new;
		return ;
	}
	while (temp_lst->next != NULL)
		temp_lst = temp_lst->next;
	temp_lst->next = new;
	new->preveus = temp_lst;
}

int	delimiter_check(char *line, t_type *delimiter, bool quotes)
{
	*delimiter = WORD;
	if ((*line == '"' || *line == '\'') && quotes)
		return (1);
	if (is_space(*line))
		return (1);
	if (*line == '|' && line[1] == '|')
		return (*delimiter = OR, 2);
	if (*line == '|')
		return (*delimiter = PIPE, 1);
	if (*line == '&' && line[1] == '&')
		return (*delimiter = AND, 2);
	if (*line == '<' && line[1] == '<')
		return (*delimiter = H_DOC, 2);
	if (*line == '<')
		return (*delimiter = RED_IN, 1);
	if (*line == '>' && line[1] == '>')
		return (*delimiter = RED_AP_OUT, 2);
	if (*line == '>')
		return (*delimiter = RED_OUT, 1);
	if (*line == '(')
		return (*delimiter = OPEN_PAR, 1);
	if (*line == ')')
		return (*delimiter = CLOSE_PAR, 1);
	return (0);
}
