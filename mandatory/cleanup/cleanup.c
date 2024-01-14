/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:49:15 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/14 17:25:45 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_exit(t_mini *mini, char *error, int code)
{
	(void)error;
	(void)mini;
	if (!error)
		perror("minishell");
	else
		printf("%s", error);
	exit(code);
}

void	token_cleanup(t_mini *mini)
{
	(void)mini;	
	mini->token = NULL;
}

void	cleanup_exit(t_mini *mini, int code)
{
	(void)mini;
	exit(code);
}
