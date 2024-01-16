/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:34:49 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/16 08:19:38 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	update_pwd(t_mini *mini)
// {
// 	(void)mini;
// 	printf("Not Implemeted\n");
// }

static void	update_defaults(t_mini *mini, bool p_ex, bool shl_ex)
{
	if (!p_ex)
		create_env(mini, ft_strdup("PATH"), ft_strdup(DEFAULT_PATH), false);
	if (!shl_ex)
		create_env(mini, ft_strdup("SHLVL"), ft_strdup("1"), true);
}

void	handle_defaults(t_mini *mini)
{
	bool	path_exists;
	bool	shlvl_exists;
	t_env	*env;
	char	*old_val;

	path_exists = false;
	shlvl_exists = false;
	env = *mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH"))
			path_exists = true;
		if (ft_strcmp(env->key, "SHLVL") && !shlvl_exists)
		{
			shlvl_exists = true;
			old_val = env->value;
			env->value = env_atoi(old_val);
			free(old_val);
			if (env->value == NULL)
				clean_exit(mini, NULL, errno);
		}
		env = env->next;
	}
	update_defaults(mini, path_exists, shlvl_exists);
}
