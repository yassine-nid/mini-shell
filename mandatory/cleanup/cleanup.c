/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:11:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 17:07:37 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	token_cleanup(t_mini *mini)
{
	t_token	*token;
	t_token	*tmp;

	clean_t_token(mini);
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
	free(mini->m_pwd);
	close(mini->std_in);
	close(mini->std_out);
	exit(code);
}

void	free_tree(t_tree **tree)
{
	if (!*tree)
		return ;
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
	free(mini->m_pwd);
	if (!error)
		perror("minishell");
	else
		ft_putstr_fd(error, 2);
	close(mini->std_in);
	close(mini->std_out);
	if (mini->hd_fd != -1)
		close(mini->hd_fd);
	exit(code);
}
