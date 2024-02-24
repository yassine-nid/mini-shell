/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:23:59 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/24 22:18:42 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reset_std_in_out(t_mini *mini)
{
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	if (dup2(mini->std_out, STDOUT_FILENO) == -1)
		clean_exit(mini, NULL, errno);
}

static void	reset_terminal(t_mini *mini)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		clean_exit(mini, NULL, errno);
	term.c_iflag = ICRNL;
	term.c_oflag = OPOST | ONLCR;
	term.c_cflag = CS8 | CREAD;
	term.c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		clean_exit(mini, NULL, errno);
}

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
	if (WIFSIGNALED(state))
	{
		if (state == 2)
			write(1, "\n", 1);
		else if (state == 3)
		{
			reset_terminal(mini);
			write(1, "Quit: 3\n", 8);
		}
		return (state + 128);
	}
	return (WEXITSTATUS(state));
}

int	execute_cmd(t_mini *mini, t_tree *root, int lvl)
{
	int		state;

	if (!root)
		return (0);
	state = red_handle(root->node, mini);
	if (state)
		return (reset_std_in_out(mini), state);
	if (is_builtin(root->node))
		state = excute_builtin(mini, root->node, lvl);
	else
		state = execute_exev(root, mini);
	reset_std_in_out(mini);
	return (state);
}
