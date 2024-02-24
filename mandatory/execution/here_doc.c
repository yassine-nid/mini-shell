/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:40:42 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/24 21:38:10 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_hd_name_file(t_mini *mini, t_token *token)
{
	char	*index;
	char	*file_name;

	index = ft_itoa((int) token % 100000);
	if (!index)
		clean_exit(mini, NULL, errno);
	file_name = ft_strjoin("/tmp/.mini_tmp_", index);
	if (!file_name)
		return (free(index), clean_exit(mini, NULL, errno), NULL);
	free(index);
	mini->hd_index++;
	return (file_name);
}

void	signal_here_doc(int sig, t_mini *minis)
{
	static t_mini	*m_mini;
	t_token			*token;
	char			*file;

	if (sig == 99292)
		m_mini = minis;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		m_mini->hd_signal = 1;
		m_mini->hd_index = 0;
		token = *m_mini->token;
		while (token)
		{
			if (token->type == H_DOC && token->next)
			{
				token = token->next;
				file = create_hd_name_file(m_mini, token);
				unlink(file);
				free(file);
			}
			token = token->next;
		}
		close (0);
	}
}

static int	read_here_d(char *lm, t_mini *mini, bool do_expand, t_token *token)
{
	char	*file;

	file = create_hd_name_file(mini, token);
	mini->hd_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (mini->hd_fd < 0)
		return (free(file), ft_err(-1, ".minishell_tmp", 0, NULL), errno);
	free(file);
	clean_t_token(mini);
	mini->herdoc_t = token_new(mini, WORD, NULL);
	mini->herdoc_t->word = readline("> ");
	while (mini->herdoc_t->word && !ft_strcmp(mini->herdoc_t->word, lm))
	{
		if (do_expand)
			expand_token(mini, mini->herdoc_t);
		ft_putendl_fd(mini->herdoc_t->word, mini->hd_fd);
		free(mini->herdoc_t->word);
		mini->herdoc_t->word = readline("> ");
	}
	clean_t_token(mini);
	return (close(mini->hd_fd), mini->hd_fd = -1, 0);
}

void	read_here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*limiter;
	int		index;
	bool	do_expand;

	signal_here_doc(99292, mini);
	signal(SIGINT, (void (*)(int))signal_here_doc);
	signal(SIGQUIT, (void (*)(int))signal_here_doc);
	if (mini->hd_signal)
		return ;
	token = token->next;
	do_expand = true;
	index = 0;
	while (token && token->word[index])
	{
		if (token->word[index] == '\'' || token->word[index] == '\"')
			do_expand = false;
		index++;
	}
	m_remove_quotes(mini, token);
	limiter = token->word;
	if (dup2(mini->std_in, STDIN_FILENO) == -1)
		clean_exit(mini, NULL, errno);
	fd = read_here_d(limiter, mini, do_expand, token);
	reset_std_in_out(mini);
}

int	here_doc(t_token *token, t_mini *mini)
{
	int		fd;
	char	*file;

	token = token->next;
	file = create_hd_name_file(mini, token);
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
