/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:23:59 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/13 09:35:57 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(t_token *token)
{
	int	nb_words;

	nb_words = 0;
	while (token && !(token->type >= PIPE && token->type <= CLOSE_PAR))
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

char	**get_cmd(t_token *token)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char **) malloc((count_words(token) + 1) * sizeof (char *));
	if (!cmd)
		return (cmd);
	while (token && !(token->type >= PIPE && token->type <= CLOSE_PAR))
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

void	reset_std_in_out(t_mini *mini)
{
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	if (dup2(mini->std_out, STDOUT_FILENO) == -1)
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
		return (reset_std_in_out(mini), state);
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
