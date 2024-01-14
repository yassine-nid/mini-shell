/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:19:35 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/13 15:00:03 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: may contain acess of invalid memory, needs to be verified
char	*get_key(char *str)
{
	int		index;
	char	*result;

	index = 0;
	result = NULL;
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] != '=')
		return (result);
	result = malloc(sizeof * result * (index + 1));
	if (!result)
		return (result);
	result[index] = '\0';
	while (index-- > 0)
		result[index] = str[index];
	return (result);
}

// TODO: may contain acess of invalid memory, needs to be verified
char	*get_value(char *str)
{
	int		index;
	int		end_index;
	char	*result;

	index = 0;
	end_index = 0;
	result = NULL;
	while (str[index] && str[index] != '=')
		index++;
	if (str[index] != '=' || !str[++index])
		return (result);
	while (str[end_index + index])
		end_index++;
	result = malloc(sizeof * result * (end_index + 1));
	if (!result)
		return (result);
	result[end_index] = '\0';
	while (--end_index >= 0)
		result[end_index] = str[end_index + index];
	return (result);
}

void	free_temps(t_mini *mini, char *key, char *origin, char *value)
{
	free(key);
	free(origin);
	free(value);
	clean_exit(mini, "malloc", 20);
}

void	create_env(t_mini *mini, char *env[])
{
	int	index;

	mini->env = malloc(sizeof * mini->env);
	if (!mini->env)
		clean_exit(mini, "Malloc", 22);
	index = 0;
	while (env[index])
	{
		char *key = get_key(env[index]);
		char *origin = ft_strdup(env[index]);
		char *value = get_value(env[index]);
		if (!key || !origin || !value)
			free_temps(mini, key, origin, value);
		t_env *new_env = ft_lstnew(key, value, origin);
		if (!new_env)
			free_temps(mini, key, origin, value);
		ft_lstadd_back(mini->env, new_env);
		index++;
	}
}

void	main_init(t_mini *mini, char *env[])
{
	if (env == NULL)
		clean_exit(mini, "Invalid env", 24);
	create_env(mini, env);
}