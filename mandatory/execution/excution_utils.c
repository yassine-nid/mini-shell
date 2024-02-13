/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:53:40 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/13 12:00:23 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(t_token *token)
{
	if (ft_strcmp_no_case(token->word, "echo"))
		return (true);
	if (ft_strcmp(token->word, "export"))
		return (true);
	if (ft_strcmp(token->word, "unset"))
		return (true);
	if (ft_strcmp_no_case(token->word, "env"))
		return (true);
	if (ft_strcmp(token->word, "exit"))
		return (true);
	if (ft_strcmp_no_case(token->word, "pwd"))
		return (true);
	if (ft_strcmp(token->word, "cd"))
		return (true);
	return (false);
}

int	excute_builtin(t_mini *mini, t_token *token, int level)
{
	if (ft_strcmp_no_case(token->word, "echo"))
		return (do_echo(token));
	if (ft_strcmp(token->word, "export"))
		return (do_export(mini, token));
	if (ft_strcmp(token->word, "unset"))
		return (do_unset(mini, token));
	if (ft_strcmp_no_case(token->word, "env"))
		return (do_env(mini, token));
	if (ft_strcmp(token->word, "exit"))
		return (do_exit(mini, token, level));
	if (ft_strcmp_no_case(token->word, "pwd"))
		return (do_pwd(mini, token));
	if (ft_strcmp(token->word, "cd"))
		return (do_cd(mini, token));
	return (70);
}