/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:11:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/16 14:45:56 by yzirri           ###   ########.fr       */
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

void	clean_tree(t_mini *mini)
{
	(void)mini;
}
