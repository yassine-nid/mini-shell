/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:40:42 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 09:35:27 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_here_doc(int sig, t_mini *mini)
{
	static t_mini	*m_mini;

	if (sig == 99292)
		m_mini = mini;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		m_mini->hd_signal = 1;
		close (0);
	}
}

char	*create_hd_name_file(t_mini *mini)
{
	char	*index;
	char	*file_name;

	index = ft_itoa(mini->hd_index);
	if (!index)
		clean_exit(mini, NULL, errno);
	file_name = ft_strjoin("/tmp/.mini_tmp_", index);
	if (!file_name)
		return (free(index), clean_exit(mini, NULL, errno), NULL);
	free(index);
	mini->hd_index++;
	return (file_name);
}

static int	read_here_d(char *limiter, t_mini *mini)
{
	char	*line;
	char	*file;
	int		fd;

	signal(SIGINT, (void (*)(int))signal_here_doc);
	signal(SIGQUIT, (void (*)(int))signal_here_doc);
	file = create_hd_name_file(mini);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(file), ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	free(file);
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

void	read_here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*limiter;

	signal_here_doc(99292, mini);
	if (mini->hd_signal)
		return ;
	token = token->next;
	m_remove_quotes(mini, token);
	limiter = token->word;
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	fd = read_here_d(limiter, mini);
	reset_std_in_out(mini);
}

int	here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*file;

	token = token->next;
	file = create_hd_name_file(mini);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(file), ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		free(file);
		clean_exit(mini, NULL, errno);
	}
	ft_err(unlink(file), NULL, 0, NULL);
	return (free(file), close(fd), 0);
}
