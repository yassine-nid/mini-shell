/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:10 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:32:59 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static void	execute_left_pipe(t_mini *mini, int *pip, t_tree *root, int level)
{
	int	status;

	if (dup2(pip[1], STDOUT_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	close(pip[1]);
	close(pip[0]);
	status = execute_type(mini, root->left, level);
	cleanup_exit(mini, status);
}

static void	execute_right_pipe(t_mini *mini, int *pip, t_tree *root, int level)
{
	int	status;

	if (dup2(pip[0], STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	close(pip[1]);
	close(pip[0]);
	status = execute_type(mini, root->right, level);
	cleanup_exit(mini, status);
}

static void	close_and_wait(int *pip, pid_t pid, pid_t pid2, int *status)
{
	close(pip[1]);
	close(pip[0]);
	waitpid(pid, status, 0);
	waitpid(pid2, status, 0);
}

int	execute_pip(t_mini *mini, t_tree *root, int level)
{
	int		status;
	int		pip[2];
	pid_t	pid;
	pid_t	pid2;

	status = 0;
	if (pipe(pip) == -1)
		clean_exit(mini, NULL, errno);
	pid = fork();
	if (pid < 0)
		clean_exit(mini, NULL, errno);
	else if (pid == 0)
		execute_left_pipe(mini, pip, root, level);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			clean_exit(mini, NULL, errno);
		else if (pid2 == 0)
			execute_right_pipe(mini, pip, root, level);
		else
			close_and_wait(pip, pid, pid2, &status);
	}
	return (WEXITSTATUS(status));
}
