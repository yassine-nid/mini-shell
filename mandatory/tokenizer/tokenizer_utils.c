/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:05:55 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/18 11:19:10 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*token_new(t_mini *mini, t_type type, char *word)
{
	t_token	*result;

	result = malloc (sizeof * result);
	if (result == NULL)
		clean_exit(mini, NULL, errno);
	result->next = NULL;
	result->preveus = NULL;
	result->type = type;
	result->word = word;
	result->is_empty = false;
	result->do_expand = true;
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

void	token_insert(t_token *new, t_token *preveus, int level)
{
	while (preveus && level-- > 0)
		preveus = preveus->next;
	if (!preveus)
		return ;
	new->preveus = preveus;
	new->next = preveus->next;
	preveus->next = new;
	if (new->next)
		new->next->preveus = new;
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

void	remove_token(t_mini *mini, t_token *token)
{
	if (!mini || !mini->token || !token)
		return ;
	if (*mini->token == token)
	{
		*mini->token = token->next;
		if (token->next)
			token->next->preveus = NULL;
		free(token->word);
		free(token);
		return ;
	}
	if (token->preveus)
		token->preveus->next = token->next;
	if (token->next)
		token->next->preveus = token->preveus;
	free(token->word);
	free(token);
}
