/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:06 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/15 15:15:41 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_env(t_mini *mini, char *key, char *value, bool exported)
{
	t_env	*new_env;

	new_env = ft_lstnew(NULL, NULL);
	if (!new_env || !key || !value)
	{
		free(key);
		free(value);
		free(new_env);
		clean_exit(mini, NULL, errno);
	}
	new_env->key = key;
	new_env->value = value;
	new_env->is_exported = exported;
	ft_lstadd_back(mini->env, new_env);
}

static char	*create_str(t_mini *mini, int val)
{
	char	*return_val;
	int		backup;
	int		size;

	if (val == -1)
		return_val = ft_strdup("");
	else
	{
		size = 1;
		backup = val;
		while (backup > 0)
		{
			backup /= 10;
			size++;
		}
		return_val = malloc(sizeof * return_val * (size + 1));
		if (!return_val)
			clean_exit(mini, NULL, errno);
		size = 0;
		backup = val;
		while (backup > 0)
		{
			return_val[size] = (backup % 10) + '0';
			backup /= 10;
			size++;
		}
		return_val[size] = '\0';
	}
	if (!return_val)
		clean_exit(mini, NULL, errno);
	return (return_val);
}

static	void remove_space(char **old)
{
	while (**old && is_space(**old))
		*old = *old + 1;
}

char	*env_atoi(t_mini *mini, char *old)
{
	int		result;
	bool	negative;

	if (!old || !*old)
		return (create_str(mini, 1));
	remove_space(&old);
	negative = *old == '-';
	if (*old == '+' || *old == '-')
		old++;
	result = 0;
	while (*old && *old <= '9' && *old >= '0')
	{
		result = result * 10 + (*old - '0');
		if (result > 0 && negative)
			return (create_str(mini, 0));
		if (result >= 1000)
			return (create_str(mini, 1));
		old++;
	}
	remove_space(&old);
	if (*old)
		return (create_str(mini, 1));
	if (result == 999)
		return (create_str(mini, -1));
	return (create_str(mini, ++result));
}