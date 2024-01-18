/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:06 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/16 09:24:51 by yzirri           ###   ########.fr       */
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

static void	remove_space(char **old)
{
	while (**old && is_space(**old))
		*old = *old + 1;
}

char	*env_atoi(char *old)
{
	int		result;
	bool	negative;

	if (!old || !*old)
		return (ft_itoa(1));
	remove_space(&old);
	negative = *old == '-';
	if (*old == '+' || *old == '-')
		old++;
	result = 0;
	while (*old && *old <= '9' && *old >= '0')
	{
		result = result * 10 + (*old - '0');
		if (result > 0 && negative)
			return (ft_itoa(0));
		if (result >= 1000)
			return (ft_itoa(1));
		old++;
	}
	remove_space(&old);
	if (*old)
		return (ft_itoa(1));
	if (result == 999)
		return (ft_strdup(""));
	return (ft_itoa(result + 1));
}
