/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:34:49 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/14 10:47:14 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_defaults_path(t_mini *mini)
{
	char	*t_key;
	char	*t_value;

	t_key = ft_strdup("PATH");
	t_value = ft_strdup(DEFAULT_PATH);
	if (!t_key || !t_value)
	{
		free(t_key);
		free(t_value);
		clean_exit(mini, NULL, errno);
	}
	if (create_env(mini, t_key, t_value, false) != 0)
	{
		free(t_key);
		free(t_value);
		clean_exit(mini, NULL, errno);
	}
}

static void	add_defaults_shlvl(t_mini *mini)
{
	char	*t_key;
	char	*t_value;

	t_key = ft_strdup("SHLVL");
	t_value = ft_strdup("1");
	if (!t_key || !t_value)
	{
		free(t_key);
		free(t_value);
		clean_exit(mini, NULL, errno);
	}
	if (create_env(mini, t_key, t_value, true) != 0)
	{
		free(t_key);
		free(t_value);
		clean_exit(mini, NULL, errno);
	}
}

static void	add_defaults(t_mini *mini, bool p_ex, bool shl_ex, bool	oldpwd_ex)
{
	char	*t_key;

	if (!p_ex)
		add_defaults_path(mini);
	if (!shl_ex)
		add_defaults_shlvl(mini);
	// return ;
	if (!oldpwd_ex)
	{
		t_key = ft_strdup("OLDPWD");
		if (!t_key)
			clean_exit(mini, NULL, errno);
		if (create_env(mini, t_key, NULL, true) != 0)
		{
			free(t_key);
			clean_exit(mini, NULL, errno);
		}
	}
}

static void	update_shlvl(t_mini *mini, t_env *env)
{
	char	*old_val;

	old_val = env->value;
	env->value = env_atoi(old_val);
	free(old_val);
	if (env->value == NULL)
		clean_exit(mini, NULL, errno);
}

void	handle_defaults(t_mini *mini)
{
	bool	path_exists;
	bool	shlvl_exists;
	bool	oldpwd_exists;
	t_env	*env;

	path_exists = false;
	shlvl_exists = false;
	oldpwd_exists = false;
	env = *mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH"))
			path_exists = true;
		if (ft_strcmp(env->key, "OLDPWD"))
			oldpwd_exists = true;
		if (ft_strcmp(env->key, "SHLVL") && !shlvl_exists)
		{
			shlvl_exists = true;
			update_shlvl(mini, env);
		}
		env = env->next;
	}
	add_defaults(mini, path_exists, shlvl_exists, oldpwd_exists);
	update_pwd(mini, true);
}
