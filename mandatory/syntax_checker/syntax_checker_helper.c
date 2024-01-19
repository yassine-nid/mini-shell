/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:18:38 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/19 11:37:48 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
