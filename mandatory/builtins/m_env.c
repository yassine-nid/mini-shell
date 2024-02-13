/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:39:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/28 09:49:51 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_env_error(void)
{
	ft_putstr_fd("minishell: env: too many arguments\n", 2);
	ft_putstr_fd("usage: env\n", 2);
}

int	do_env(t_mini *mini, t_token *token)
{
	t_env	*env;

	env = *mini->env;
	if (!env || !token)
		return (1);
	if (get_next_arg(token->next))
	{
		print_env_error();
		return (1);
	}
	while (env)
	{
		if (env->is_exported && env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
