/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:40:42 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/16 14:46:18 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int a = 0;

static int	read_here_d(char *limiter)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.minishell_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	line = readline("> ");
	while (line && !ft_strcmp(line, limiter) && !a)
	{
	printf("%d", a);
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
		write(1, "\n", 1);
		a = 1;
	}
}

int	here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*limiter;
	struct	sigaction sa;

	sa.sa_handler = signal_here_doc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
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
	return (close(fd), 0);
}
