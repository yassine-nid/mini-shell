/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:32:39 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:32:52 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

char	**get_paths(t_mini *mini)
{
	t_env	*env;
	char	*result;

	env = *mini->env;
	result = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH"))
		{
			result = env->value;
			break ;
		}
		env = env->next;
	}
	return (ft_split(result, ':'));
}
