/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_helper_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:18:38 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:36:18 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	quoate_syntax(char *word)
{
	int		quoate_count;
	char	quoate;

	quoate_count = 0;
	if (!word)
		return (0);
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
		{
			quoate = *(word++);
			quoate_count++;
			while (*word && *word != quoate)
				word++;
			if (*word == quoate)
				quoate_count++;
		}
		if (*word)
			word++;
	}
	return (quoate_count % 2);
}

int	check_word(t_token *token)
{
	if (token->next == NULL)
		return (0);
	if (token->next->type == OPEN_PAR)
		return (1);
	return (0);
}

int	check_quoate(t_token *token)
{
	if (!token)
		return (0);
	while (token)
	{
		if (token->type == WORD)
			if (quoate_syntax(token->word))
				return (1);
		token = token->next;
	}
	return (0);
}

int	syntax_par(t_token *token)
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
