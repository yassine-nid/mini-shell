/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:33:43 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 08:34:28 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_exit_two(t_mini *mini, char **error, int code)
{
	if (!*error)
		perror("minishell");
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*error, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	token_cleanup(mini);
	free_tree(&mini->tree);
	close(mini->std_in);
	close(mini->std_out);
	free(error);
	exit(code);
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
