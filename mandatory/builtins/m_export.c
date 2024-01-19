/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:22:01 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/19 10:12:55 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_export(t_mini *mini)
{
	t_env	*env;

	if (write(1, "", 0) < 0)
		return (errno);
	env = *mini->env;
	while (env)
	{
		if (env->is_exported)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->key, 1);
			if (env->value)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(env->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}

static int	add_to_env(t_mini *mini, char *word)
{
	bool	m_failed;
	char	*key;
	char	*value;
	t_env	*env;

	if (!mini || !mini->env || !word || !word[0])
		return (0);
	key = get_key(word, &m_failed);
	if (m_failed)
		return (errno);
	value = get_value(word, &m_failed);
	if (m_failed)
		return (free(key), errno);
	if (!key)
		key = ft_strdup(word);
	if (!key)
		return (free(value), errno);
	env = *mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, key))
		{
			if (env->value && env->value[0] && (!value || !value[0]))
				return (free(key), free(value), 0);
			free(env->value);
			free(key);
			env->value = value;
			return (0);
		}
		env = env->next;
	}
	return (create_env(mini, key, value, true));
}

int	do_export(t_mini *mini, t_token *token)
{
	int	status;
	int	index;

	if (!token->next)
		return (print_export(mini));
	token = token->next;
	while (token)
	{
		if (token->type != WORD)
			return (0);
		index = 0;
		while (is_space(token->word[index]))
			index++;
		if (!is_alpha_num(token->word[index]))
			return (print_mini_error(mini, "export", token->word, NOT_VALID), 1);
		while (token->word[index])
		{
			if (token->word[index] == '=')
				break ;
			if (!is_alpha_num(token->word[index++]))
				return (print_mini_error(mini, "export", token->word, NOT_VALID), 1);
		}
		if (token->word[0] <= '9' && token->word[0] >= '0')
			return (print_mini_error(mini, "export", token->word, NOT_VALID), 1);
		status = add_to_env(mini, token->word);
		if (status != 0)
			return (status);
		token = token->next;
	}
	return (0);
}