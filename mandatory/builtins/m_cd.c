/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:15:44 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 10:30:44 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_env_by_key(t_mini *mini, t_env **result, char *key)
{
	t_env	*env;

	env = *mini->env;
	*result = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, key))
		{
			*result = env;
			return ;
		}
		env = env->next;
	}
}

static void	set_oldpwd(t_mini *mini, t_env *old_pwd_env, char *new_val)
{
	free(old_pwd_env->value);
	old_pwd_env->value = NULL;
	if (!new_val)
		return ;
	old_pwd_env->value = ft_strdup(new_val);
	if (!old_pwd_env->value)
		clean_exit(mini, NULL, errno);
}

static void	update_oldpwd(t_mini *mini)
{
	static bool	source_env;
	t_env		*old_pwd_env;
	t_env		*pwd_env;

	get_env_by_key(mini, &old_pwd_env, "OLDPWD");
	get_env_by_key(mini, &pwd_env, "PWD");
	if (!old_pwd_env)
		return ;
	if (pwd_env)
	{
		set_oldpwd(mini, old_pwd_env, pwd_env->value);
		source_env = true;
	}
	else
	{
		if (source_env)
			set_oldpwd(mini, old_pwd_env, "");
		else
			set_oldpwd(mini, old_pwd_env, mini->m_pwd);
		source_env = false;
	}
}

static void	path_append(t_mini *mini, char *append, int index, int indexj)
{
	int		new_size;
	char	*new;

	if (!append || !mini->m_pwd)
		return ;
	new_size = ft_strlen(mini->m_pwd);
	new_size += ft_strlen(append);
	new = malloc(sizeof * new * (new_size + 2));
	if (!new)
		clean_exit(mini, NULL, errno);
	index = 0;
	while (mini->m_pwd[index])
	{
		new[index] = mini->m_pwd[index];
		index++;
	}
	new[index++] = '/';
	indexj = 0;
	while (append[indexj])
		new[index++] = append[indexj++];
	new[index] = '\0';
	free(mini->m_pwd);
	mini->m_pwd = new;
	update_env_pwd(mini);
}

int	do_cd(t_mini *mini, t_token *token)
{
	char	*mpath;

	update_oldpwd(mini);
	if (token)
		token = token->next;
	if (!get_next_arg(token))
	{
		ft_putstr_fd("minishell: invalid usage\n", 2);
		ft_putstr_fd("cd: usage: export [relative or absolute path]\n", 2);
		return (1);
	}
	mpath = get_next_arg(token)->word;
	if (chdir(mpath) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(mpath);
		return (1);
	}
	if (update_pwd(mini, false) != 0)
		path_append(mini, mpath, 0, 0);
	return (0);
}
