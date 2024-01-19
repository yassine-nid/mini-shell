/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:19:35 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/19 12:22:19 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_key_val(t_mini *mini, char *env, char **key, char **val)
{
	bool	m_f;

	*key = get_key(env, &m_f);
	if (m_f)
		clean_exit(mini, NULL, errno);
	*val = get_value(env, &m_f);
	if (m_f)
	{
		free(key);
		clean_exit(mini, NULL, errno);
	}
}

static void	init_envs(t_mini *mini, char *env[])
{
	int		index;
	char	*key;
	char	*val;

	mini->env = malloc(sizeof * mini->env);
	if (!mini->env)
		clean_exit(mini, NULL, errno);
	mini->env[0] = NULL;
	index = 0;
	while (env[index])
	{
		get_key_val(mini, env[index], &key, &val);
		if (create_env(mini, key, val, true) != 0)
		{
			free(key);
			free(val);
			clean_exit(mini, NULL, errno);
		}
		index++;
	}
}

void	handle_env(t_mini *mini, char *env[])
{
	if (env == NULL)
		clean_exit(mini, "Invalid env", 24);
	init_envs(mini, env);
	handle_defaults(mini);
}
