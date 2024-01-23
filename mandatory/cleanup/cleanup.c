/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:11:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/23 11:15:04 by ynidkouc         ###   ########.fr       */
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

void	clean_tree(t_mini *mini)
{
	// if (!mini || !mini->env);
	(void)mini;
}

void	cleanup_exit(t_mini *mini, int code)
{
	clean_tree(mini);
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
	clean_tree(mini);
	token_cleanup(mini);
	free_tree(&mini->tree);
	if (!error)
		perror("minishell");
	else
		ft_putstr_fd(error, 2);
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
