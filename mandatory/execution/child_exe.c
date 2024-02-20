/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:20:03 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/19 10:56:33 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*path_access(char **paths, char **cmd, t_mini *mini)
{
	char	*tmp;
	char	*path_cmd;
	int		i;

	i = -1;
	path_cmd = NULL;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], *cmd);
		if (!tmp)
			clean_exit(mini, NULL, errno);
		if (!access(tmp, X_OK))
		{
			path_cmd = tmp;
			break ;
		}
		free(tmp);
	}
	return (path_cmd);
}

static char	*cmd_access(char **cmd, t_mini *mini)
{
	char	*path_cmd;
	char	**paths;

	if (!**cmd)
		return (NULL);
	cmd[0] = ft_strjoin("/", cmd[0]);
	if (!cmd[0])
		clean_exit(mini, NULL, errno);
	paths = get_paths(mini);
	if (!paths)
		return (NULL);
	path_cmd = path_access(paths, cmd, mini);
	ft_free(paths);
	return (path_cmd);
}

static int	count_env(t_mini *mini)
{
	t_env	*env;
	int		i;

	env = *mini->env;
	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static char	**get_env(t_mini *mini)
{
	t_env	*env;
	char	**env_s;
	char	*tmp;
	int		i;

	i = count_env(mini);
	if (!i)
		return (0);
	env = *mini->env;
	env_s = (char **) malloc ((i + 1) * sizeof (char *));
	if (!env_s)
		clean_exit(mini, NULL, errno);
	i = 0;
	while (env)
	{
		env_s[i] = ft_strjoin(env->key, "=");
		tmp = ft_strjoin(env_s[i], env->value);
		free(env_s[i]);
		env_s[i] = tmp;
		i++;
		env = env->next;
	}
	env_s[i] = NULL;
	return (env_s);
}

void	child_exe(t_tree *root, t_mini *mini)
{
	char	**cmd;
	char	*cmd_path;
	char	**env;

	cmd = get_cmd(mini, root->node);
	if (!cmd)
		cleanup_exit(mini, 0);
	if (ft_strchr(*cmd, '/'))
		cmd_path = *cmd;
	else
		cmd_path = cmd_access(cmd, mini);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		if (**cmd)
			ft_putstr_fd(cmd[0] + 1, 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_exit(mini, 127);
	}
	env = get_env(mini);
	execve(cmd_path, cmd, env);
	ft_free(env);
	clean_exit_two(mini, cmd, errno);
}
