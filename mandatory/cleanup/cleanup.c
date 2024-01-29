/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:11:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/28 08:34:17 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_cleanup(t_mini *mini)
{
	t_token	*token;
	t_token	*tmp;

	if (!mini || !mini->token)
		return ;
	token = *mini->token;
	while (token)
	{
		tmp = token->next;
		free(token->word);
		free(token);
		token = tmp;
	}
	free(mini->token);
	mini->token = NULL;
}

void	env_cleanup(t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	if (!mini || !mini->env)
		return ;
	env = *mini->env;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
	free(mini->env);
	mini->env = NULL;
}

void	cleanup_exit(t_mini *mini, int code)
{
	token_cleanup(mini);
	free_tree(&mini->tree);
	exit(code);
}

void	free_tree(t_tree **tree)
{
	if (!*tree)
		return;
	if ((*tree)->left)
		free_tree(&(*tree)->left);
	if ((*tree)->right)
		free_tree(&(*tree)->right);
	free(*tree);
	*tree = NULL;
}

void	clean_exit(t_mini *mini, char *error, int code)
{
	token_cleanup(mini);
	free_tree(&mini->tree);
	if (!error)
		perror("minishell");
	else
		ft_putstr_fd(error, 2);
	close(mini->std_in);
	close(mini->std_out);
	system("leaks minishell");
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
