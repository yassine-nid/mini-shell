/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:11:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/18 17:10:07 by yzirri           ###   ########.fr       */
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
	exit(code);
}

void	clean_exit(t_mini *mini, char *error, int code)
{
	clean_tree(mini);
	token_cleanup(mini);
	if (!error)
		perror("minishell");
	else
		printf("%s", error);
	system("leaks minishell");
	exit(code);
}
