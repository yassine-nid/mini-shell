/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:34:49 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/15 15:26:32 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	update_pwd(t_mini *mini)
// {
	
// }

void	handle_defaults(t_mini *mini)
{
	bool	path_exists;
	bool	shlvl_exists;
	t_env	*env;
	char	*old_val;

	path_exists = false;
	shlvl_exists = false;
	env = *mini->env;
	while(env)
	{
		if (ft_strcmp(env->key, "PATH"))
			path_exists = true;
		if (ft_strcmp(env->key, "SHLVL") && !path_exists)
		{
			shlvl_exists = true;
			old_val = env->value;
			env->value = env_atoi(mini, old_val);
			free(old_val);
		}
		env = env->next;
	}
	if (!path_exists)
		create_env(mini, ft_strdup("PATH"), ft_strdup(DEFAULT_PATH), false);
	if (!shlvl_exists)
		create_env(mini, ft_strdup("SHLVL"), ft_strdup("1"), true);


	printf("\n\n");
	t_env *sss = *mini->env;
	while (sss)
	{
		if (sss->is_exported)
			printf("%s=%s\n", sss->key, sss->value);
		sss = sss->next;
	}
	printf("\n\n");
}