/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:19:35 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/15 14:20:24 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key(char *str)
{
	int		index;
	char	*result;

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
		return (result);
	result[index] = '\0';
	while (index-- > 0)
		result[index] = str[index];
	return (result);
}

char	*get_value(char *str)
{
	int		index;
	int		end_index;
	char	*result;

	index = 0;
	end_index = 0;
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
		return (result);
	result[end_index] = '\0';
	while (--end_index >= 0)
		result[end_index] = str[end_index + index];
	return (result);
}

static void	init_envs(t_mini *mini, char *env[])
{
	int		index;

	mini->env = malloc(sizeof * mini->env);
	if (!mini->env)
		clean_exit(mini, NULL, errno);
	mini->env[0] = NULL;
	index = 0;
	while (env[index])
	{
		create_env(mini, get_key(env[index]), get_value(env[index]), true);
		index++;
	}
}

void	handle_env(t_mini *mini, char *env[])
{
	if (env == NULL)
		clean_exit(mini, "Invalid env", 24);
	init_envs(mini, env);
	handle_defaults(mini);
}
