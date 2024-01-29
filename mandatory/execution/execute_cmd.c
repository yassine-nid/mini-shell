/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:23:59 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/29 10:04:02 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(t_token *token)
{
	int nb_words;

	nb_words = 0;
	while (token && token->type != AND && token->type != OR
		&& token->type != PIPE && token->type != OPEN_PAR
		&& token->type != CLOSE_PAR)
	{
		while (token && token->type == WORD)
		{
			nb_words++; 								
			token = token->next;
		}
		if (token && (token->type == RED_IN || token->type == RED_OUT
			|| token->type == RED_AP_OUT || token->type == H_DOC))
		{
			token = token->next;
			if (token)
				token = token->next;
		}
	}
	return (nb_words);
}

static char	**get_cmd(t_token *token)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char **) malloc((count_words(token) + 1) * sizeof (char *));
	if (!cmd)
		return (cmd);
	while (token && token->type != AND && token->type != OR
		&& token->type != PIPE && token->type != OPEN_PAR
		&& token->type != CLOSE_PAR)
	{
		while (token && token->type == WORD)
		{
			cmd[i++] = token->word;								
			token = token->next;
		}
		if (token && (token->type == RED_IN || token->type == RED_OUT
			|| token->type == RED_AP_OUT || token->type == H_DOC))
		{
			token = token->next;
			if (token)
				token = token->next;
		}
	}
	cmd[i] = NULL;
	return (cmd);
}

// ###################### Red_Handle ######################

int	red_in(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;

	token = token->next;
	file = token->word;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), errno);
	if (dup2(fd, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	close(fd);
	return (0);
}
int	red_out(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;

	token = token->next;
	file = token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), errno);
	if (dup2(fd, STDOUT_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	close(fd);
	return (0);
}
int	red_ap_out(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;

	token = token->next;
	file = token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), errno);
	if (dup2(fd, STDOUT_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	close(fd);
	return (0);
}
int	here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*limiter;
	char	*line;

	token = token->next;
	limiter = token->word;
	fd = open("/tmp/.minishell_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	line = readline("> ");
	while (line && !ft_strcmp(line, limiter))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = open("/tmp/.minishell_tmp", O_RDONLY);
	if (fd < 0)
		return (ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	if (dup2(fd, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	ft_err(unlink("/tmp/.minishell_tmp"), NULL, 0, NULL);
	return (close(fd), 0);
}

int	red_handle(t_token *token, t_mini *mini)
{
	int	status;

	status = 0;
	while (token && token->type != AND && token->type != OR
		&& token->type != PIPE && token->type != OPEN_PAR
		&& token->type != CLOSE_PAR)
	{
		if (token->type == RED_IN)
			status = red_in(token, mini);
		else if (token->type == RED_OUT)
			status = red_out(token, mini);
		else if (token->type == RED_AP_OUT)
			status = red_ap_out(token, mini);
		else if (token->type == H_DOC)
			status = here_doc(token, mini);
		if (status)
			return (status);
		token = token->next;
	}
	return (status);
}

// ########################################################

void reset_std_in_out(t_mini *mini)
{
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	if (dup2(mini->std_out, STDOUT_FILENO) == -1)
		clean_exit(mini, NULL, errno);
}
// ################# child exe #################

char	**get_paths(t_mini *mini)
{
	t_env	*env;
	char	*result;

	env = *mini->env;
	result = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH"))
		{
			result = env->value;
			break ;
		}
		env = env->next;
	}
	return (ft_split(result, ':'));
}

char	*cmd_access(char **cmd, t_mini *mini)
{
	char	*path_cmd;
	char	**paths;
	char	*tmp;
	int		i;

	path_cmd = NULL;
	if (!access(*cmd, X_OK))
		return (*cmd);
	cmd[0] = ft_strjoin("/", cmd[0]); // free cmd[0] and cmd
	if (!cmd[0])
		clean_exit(mini, NULL, errno);
	paths = get_paths(mini);
	if (!paths)
		return (NULL);
	i = -1;
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
	ft_free(paths);
	return (path_cmd);
}

char	**get_env(t_mini *mini)
{
	t_env	*env;
	char	**env_s;
	int		i;

	env = *mini->env;
	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	if (!i)
		return (0);
	env = *mini->env;
	env_s = (char **) malloc ((i + 1) * sizeof (char *));
	if (!env_s)
		clean_exit(mini, NULL, errno);
	i = 0;
	while (env)
	{
		env_s[i++] = ft_strjoin(env->key, env->value);
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

	cmd = get_cmd(root->node);
	if (!cmd)
		clean_exit(mini, NULL, errno);
	cmd_path = cmd_access(cmd, mini);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0] + 1, 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_exit(mini, 127);
	}
	env = get_env(mini);
	execve(cmd_path, cmd, env);
	free(cmd[0]);
	free(cmd);
	clean_exit(mini, NULL, errno);
}

// ###############################################

int	execute_exev(t_tree *root, t_mini *mini)
{
	pid_t	pid;
	int		state;

	pid = fork();
	state = 0;
	if (pid < 0)
		clean_exit(mini, NULL, errno);
	if (pid == 0)
		child_exe(root, mini);
	else
		waitpid(pid, &state, 0);
	return (WEXITSTATUS(state));
}

int	execute_cmd(t_mini *mini, t_tree *root, int level)
{
	int		state;
	(void)	level;

	if (!root)
		return (0);
	state = red_handle(root->node, mini);
	if (state)
		return (state);
	// if (is_built_in(mini, root->node))
	// {
	// 	state = excute_builtin(mini, root->node, level);
	// 	return (reset_std_in_out(mini), state);
	// }
	// else
		state = execute_exev(root, mini);
	reset_std_in_out(mini);
	return (state);
}
