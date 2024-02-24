/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_export_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:22:01 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 13:10:48 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	print_export(t_mini *mini)
{
	t_env	*env;

	if (write(1, "", 0) < 0)
		return (errno);
	env_sort(mini, NULL, NULL);
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

static char	*m_get_key(char *word)
{
	char	*key;
	bool	m_failed;
	int		index;

	key = get_key(word, &m_failed);
	if (m_failed)
		return (NULL);
	if (!key)
		key = ft_strdup(word);
	index = 0;
	while (key[index])
	{
		if (key[index] == '+')
		{
			key[index] = '\0';
			break ;
		}
		index++;
	}
	return (key);
}

static int	add_to_env(t_mini *mini, char *word, bool append)
{
	bool	m_failed;
	char	*key;
	char	*value;
	t_env	*env;

	if (!mini || !mini->env || !word || !word[0])
		return (0);
	key = m_get_key(word);
	if (!key)
		return (errno);
	value = get_value(word, &m_failed);
	if (m_failed)
		return (free(key), errno);
	env = *mini->env;
	while (env)
	{
		if (ft_strcmp(env->key, key))
		{
			if (env->value && !value)
				return (free(key), free(value), 0);
			return (free(key), export_add(env, value, append));
		}
		env = env->next;
	}
	return (create_env(mini, key, value, true));
}

static int	is_valid_name(t_mini *mini, t_token *token, int *indx, bool *apend)
{
	*apend = false;
	if (!is_alpha_num(token->word[*indx]))
		return (print_mini_error(mini, "export", token->word, INVALID), 1);
	while (token->word[*indx])
	{
		if (token->word[*indx] == '+' && token->word[*indx + 1] == '=')
		{
			*apend = true;
			break ;
		}
		if (token->word[*indx] == '=')
			break ;
		if (!is_alpha_num(token->word[*indx]))
			return (print_mini_error(mini, "export", token->word, INVALID), 1);
		*indx = *indx + 1;
	}
	if (token->word[0] <= '9' && token->word[0] >= '0')
		return (print_mini_error(mini, "export", token->word, INVALID), 1);
	return (0);
}

int	do_export(t_mini *mini, t_token *token)
{
	int		exit_stat;
	int		index;
	bool	append;

	if (token)
		token = get_next_arg(token->next);
	if (!token)
		return (print_export(mini));
	exit_stat = 0;
	while (token)
	{
		if (token->type != WORD)
			break ;
		index = 0;
		if (is_valid_name(mini, token, &index, &append) != 0)
			exit_stat = 1;
		else if (add_to_env(mini, token->word, append) != 0)
			exit_stat = 1;
		token = get_next_arg(token->next);
	}
	return (exit_stat);
}
