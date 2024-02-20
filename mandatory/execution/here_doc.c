/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:40:42 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/20 10:13:13 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_here_d(char *limiter)
{
	char	*line;
	int		fd;

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
	return (0);
}


void	signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		// write(1, "\n", 1);
		// close (0);
	}
}

int	here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*limiter;

	signal(SIGINT, (void (*)(int))signal_here_doc);
	token = token->next;
	m_remove_quotes(mini, token);
	limiter = token->word;
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	fd = read_here_d(limiter);
	if (fd)
		return (fd);
	fd = open("/tmp/.minishell_tmp", O_RDONLY);
	if (fd < 0)
		return (ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		clean_exit(mini, NULL, errno);
	}
	ft_err(unlink("/tmp/.minishell_tmp"), NULL, 0, NULL);
	// reset_std_in_out(mini);
	return (close(fd), 0);
}
