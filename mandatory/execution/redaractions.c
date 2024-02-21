/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redaractions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:04:51 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 11:37:38 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ambiguous_red(t_token *token, char *old)
{
	if (!(!token->do_expand && token->next && !token->next->do_expand)
		&& !(token->was_env && token->next && token->next->was_env)
		&& !(token->was_env && token->is_empty))
	{
		return (0);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(old, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (1);
}

int	red_in(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;
	char	*old;

	token = token->next;
	old = ft_strdup(token->word);
	expand_token(mini, token, true);
	if (ambiguous_red(token, old))
		return (free(old), 1);
	file = token->word;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		clean_exit(mini, NULL, errno);
	}
	close(fd);
	return (0);
}

int	red_out(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;
	char	*old;

	token = token->next;
	old = ft_strdup(token->word);
	expand_token(mini, token, true);
	if (ambiguous_red(token, old))
		return (free(old), 1);
	file = token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		clean_exit(mini, NULL, errno);
	}
	close(fd);
	return (0);
}

int	red_ap_out(t_token *token, t_mini *mini)
{
	char	*file;
	int		fd;
	char	*old;

	token = token->next;
	old = ft_strdup(token->word);
	expand_token(mini, token, true);
	if (ambiguous_red(token, old))
		return (free(old), 1);
	file = token->word;
	free(old);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		clean_exit(mini, NULL, errno);
	}
	close(fd);
	return (0);
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
