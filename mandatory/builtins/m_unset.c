/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:24:44 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 13:12:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_name(t_mini *mini, t_token *token, int *index)
{
	if (!is_alpha_num(token->word[*index]))
		return (print_mini_error(mini, "unset", token->word, INVALID), 1);
	while (token->word[*index])
	{
		if (token->word[*index] == '=')
			break ;
		if (!is_alpha_num(token->word[*index]))
			return (print_mini_error(mini, "unset", token->word, INVALID), 1);
		*index = *index + 1;
	}
	if (token->word[0] <= '9' && token->word[0] >= '0')
		return (print_mini_error(mini, "unset", token->word, INVALID), 1);
	return (0);
}

static void	unset_single(t_mini *mini, char *word)
{
	t_env	*env;
	t_env	*perv;

	env = *mini->env;
	perv = NULL;
	while (env)
	{
		if (ft_strcmp(word, env->key))
		{
			if (*mini->env == env)
				*mini->env = env->next;
			else if (perv)
				perv->next = env->next;
			free(env->value);
			free(env->key);
			free(env);
			break ;
		}
		perv = env;
		env = env->next;
	}
}

int	do_unset(t_mini *mini, t_token *token)
{
	int	exit_stat;
	int	index;

	exit_stat = 0;
	if (token)
		token = get_next_arg(token->next);
	if (!token)
		return (exit_stat);
	while (token)
	{
		if (token->type != WORD)
			break ;
		index = 0;
		while (is_space(token->word[index]))
			index++;
		if (is_valid_name(mini, token, &index) != 0)
			exit_stat = 1;
		else
			unset_single(mini, token->word);
		token = get_next_arg(token->next);
	}
	return (exit_stat);
}
