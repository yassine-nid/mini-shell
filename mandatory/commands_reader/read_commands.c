/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/13 10:55:35 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	new_prompt(t_mini *mini)
{
	char *inpt = readline("minishell:$ ");
	if (inpt == NULL)
		clean_exit(mini, "test");
	printf("%s", inpt);
	free(inpt);
	inpt = NULL;
}

void	read_commands(t_mini *mini)
{
	(void)mini;
	while (1)
		new_prompt(mini);
}