/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:53:40 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/13 15:35:08 by yzirri           ###   ########.fr       */
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
	t_token *tmp = token;
	while (1)
	{
		token = get_next_arg(token);
		if (!token)
			break ;
		expand_token(mini, token);
		token = token->next;
	}
	token = tmp;
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