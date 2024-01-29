/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:10 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/29 10:07:28 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_pip(t_mini *mini, t_tree *root, int level)
{
	int		status;
	int		pip[2];
	pid_t	pid;
	pid_t	pid2;
	(void)	mini;

	status = 0;
	pipe(pip);
	pid = fork();
	if (pid < 0)
		clean_exit(mini, NULL, errno);
	else if (pid == 0)
	{
		dup2(pip[1], STDOUT_FILENO); // protection
		close(pip[1]);
		close(pip[0]);
		status = execute_type(mini ,root->left, level);
		cleanup_exit(mini, status);
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			exit(1); // err exit !!!
		else if (pid2 == 0)
		{
			dup2(pip[0], STDIN_FILENO); //protection
			close(pip[1]);
			close(pip[0]);
			status = execute_type(mini, root->right, level);
			cleanup_exit(mini, status);
		}
		else
		{
			close(pip[1]);
			close(pip[0]);
			waitpid(pid, &status, 0);
			waitpid(pid2, &status, 0);
		}
	}
	return (WEXITSTATUS(status));
}
