/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:33:43 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 16:53:25 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

void	clean_exit_two(t_mini *mini, char **error, int errn)
{
	struct stat	file;

	if (!*error)
		perror("minishell");
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*error, 2);
		if (stat(*error, &file) == 0 && S_ISDIR(file.st_mode))
			(ft_putstr_fd(": is a directory\n", 2), errn = 126);
		else
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
	}
	free(error);
	if (errn == 13)
		errn = 126;
	else if (errn == 2)
		errn = 127;
	cleanup_exit(mini, errn);
}

void	print_mini_error(t_mini *mini, char *command, char *arg, char *error)
{
	(void)mini;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_free(char **p)
{
	int	i;

	if (!p)
		return ;
	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
	p = NULL;
}

void	ft_err(int err_nb, char *str, int ext, char **to_free)
{
	if (err_nb == -1)
	{
		if (str)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		else
			perror("minishell");
		if (to_free)
			ft_free(to_free);
		if (ext)
			exit(ext);
	}
}

void	clean_t_token(t_mini *mini)
{
	if (mini->herdoc_t)
	{
		free(mini->herdoc_t->word);
		free(mini->herdoc_t);
		mini->herdoc_t = NULL;
	}
}
