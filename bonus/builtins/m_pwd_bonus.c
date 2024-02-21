/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:25:03 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:31:50 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	pwd_options_check(t_token *token)
{
	if (!token || token->type != WORD || !token->word)
		return (0);
	if (token->word[0] != '-' || !token->word[1])
		return (0);
	ft_putstr_fd("minishell: pwd: -", 2);
	write(2, &token->word[1], 1);
	ft_putstr_fd(": invalid option\npwd: usage: pwd\n", 2);
	return (1);
}

int	do_pwd(t_mini *mini, t_token *token)
{
	if (token)
		token = get_next_arg(token->next);
	if (pwd_options_check(token) != 0)
		return (1);
	if (!mini->m_pwd)
		return (m_print_dir_error(true));
	ft_putstr_fd(mini->m_pwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
