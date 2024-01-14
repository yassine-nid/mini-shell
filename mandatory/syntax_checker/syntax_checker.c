/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:59:31 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/14 19:01:45 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	syntax_par(t_token *token)
{
	int	par_count;

	par_count = 0;
	while (token)
	{
		if (token->type == OPEN_PAR)
			par_count++;
		else if (token->type == CLOSE_PAR)
			par_count--;
		if (par_count < 0)
			return (1);
		token = token->next;
	}
	if (par_count == 0)
		return (0);
	else
		return (1);
}

static int	check_pipe_or(t_token *token)
{
	if (token->preveus == NULL)
		return (1);
	if (token->next == NULL || token->next->type == AND
		|| token->next->type == OR || token->next->type == PIPE
		|| token->next->type == CLOSE_PAR)
		return (1);
	return (0);
}

static int	check_open_par(t_token *token)
{
	if (token->next == NULL || token->next->type == AND
		|| token->next->type == OR || token->next->type == PIPE
		|| token->next->type == CLOSE_PAR)
		return (1);
	return (0);
}

static int	check_close_par(t_token *token)
{
	if (token->preveus == NULL)
		return (1);
	if (token->next == NULL)
		return (0);
	if (token->next->type == OPEN_PAR || token->next->type == WORD)
		return (1);
	return (0);
}

static int	check_all_red(t_token *token)
{
	if (token->next == NULL)
		return (1);
	if (token->next->type != WORD)
		return (1);
	return (0);
}

static int	check_word(t_token *token)
{
	if (token->next == NULL)
		return (0);
	if (token->next->type == OPEN_PAR)
		return (1);
	return (0);
}

int	syntax_checker(t_token *token)
{
	int	is_valid;

	is_valid = 0;
	if (!token)
		return (0);
	if (syntax_par(token))
		return (1);
	while (token)
	{
		if (token->type == PIPE || token->type == OR || token->type == AND)
			is_valid = check_pipe_or(token);
		else if (token->type == OPEN_PAR)
			is_valid = check_open_par(token);
		else if (token->type == CLOSE_PAR)
			is_valid = check_close_par(token);
		else if (token->type != WORD)
			is_valid = check_all_red(token);
		else if (token->type == WORD)
			is_valid = check_word(token);
		if (is_valid)
			return (1);
		token = token->next;
	}
	return (0);
}
