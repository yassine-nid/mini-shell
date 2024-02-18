/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redaractions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:04:51 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/18 15:34:32 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	token = token->next;
	file = token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), errno);
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


	token = token->next;
	t_token *test_new = token_new(mini, WORD, NULL);
	test_new->word = ft_strdup(token->word);
	expand_token(mini, test_new);
	if (!test_new->do_expand && test_new->next && !test_new->next->do_expand)
	{
		printf("bad red [%s]\n", token->word);
		return (1);
	}
	if (test_new->was_env && test_new->next && test_new->next->was_env)
	{
		printf("bad red env [%s]\n", token->word);
		return (1);
	}
	file = test_new->word;
	// free(test_new->word);
	// free(test_new);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_err(-1, file, 0, NULL), errno);
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
