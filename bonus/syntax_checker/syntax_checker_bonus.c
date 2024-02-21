/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:59:31 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:36:13 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

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

static int	check_all_red(t_token *token, t_mini *mini)
{
	(void)mini;
	if (token->next == NULL)
		return (1);
	if (token->next->type != WORD)
		return (1);
	return (0);
}

int	syntax_checker(t_token *token, t_mini *mini)
{
	int	is_valid;

	is_valid = 0;
	mini->hd_index = 0;
	if (!token)
		return (0);
	if (syntax_par(token) || check_quoate(token))
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
			is_valid = check_all_red(token, mini);
		else if (token->type == WORD)
			is_valid = check_word(token);
		if (is_valid)
			return (is_valid);
		token = token->next;
	}
	return (0);
}
