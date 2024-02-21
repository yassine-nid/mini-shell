/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:15:06 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:32:31 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static void	remove_space(char **old)
{
	while (**old && is_space(**old))
		*old = *old + 1;
}

int	create_env(t_mini *mini, char *key, char *value, bool exported)
{
	t_env	*new_env;

	new_env = ft_lstnew(NULL, NULL);
	if (!new_env)
		return (1);
	new_env->key = key;
	new_env->value = value;
	new_env->is_exported = exported;
	ft_lstadd_back(mini->env, new_env);
	return (0);
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

char	*get_key(char *str, bool *malloc_failed)
{
	int		index;
	char	*result;

	*malloc_failed = false;
	index = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] != '=')
		return (result);
	result = malloc(sizeof * result * (index + 1));
	if (!result)
		return (*malloc_failed = true, result);
	result[index] = '\0';
	while (index-- > 0)
		result[index] = str[index];
	return (result);
}

char	*get_value(char *str, bool *malloc_failed)
{
	int		index;
	int		end_index;
	char	*result;

	index = 0;
	end_index = 0;
	*malloc_failed = false;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] != '=')
		return (result);
	index++;
	while (str[end_index + index])
		end_index++;
	result = malloc(sizeof * result * (end_index + 1));
	if (!result)
		return (*malloc_failed = true, result);
	result[end_index] = '\0';
	while (--end_index >= 0)
		result[end_index] = str[end_index + index];
	return (result);
}
