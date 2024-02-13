/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_pwd_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:48:26 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/26 13:14:49 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	update_env_pwd(t_mini *mini)
{
	t_env	*env;

	env = *mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD"))
		{
			free(env->value);
			env->value = ft_strdup(mini->m_pwd);
			if (!env->value)
				clean_exit(mini, NULL, errno);
			return (true);
		}
		env = env->next;
	}
	return (false);
}

int	update_pwd(t_mini *mini, bool is_init)
{
	char	buff[PATH_MAX + 1];
	char	*res;
	char	*key;

	res = getcwd(buff, PATH_MAX + 1);
	if (!res)
		return (m_print_dir_error(!is_init), 1);
	free(mini->m_pwd);
	mini->m_pwd = ft_strdup(buff);
	if (!mini->m_pwd)
		clean_exit(mini, NULL, errno);
	if (!update_env_pwd(mini) && is_init)
	{
		key = ft_strdup("PWD");
		if (!key)
			clean_exit(mini, NULL, errno);
		if (create_env(mini, key, NULL, true) != 0)
		{
			free(key);
			clean_exit(mini, NULL, errno);
		}
	}
	return (update_env_pwd(mini), 0);
}
