/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:32:53 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/12 16:46:17 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int sigint_count;

static void	new_prompt()
{
	static int old_sig;
	char *inpt = readline("minishell:$ ");

	if (old_sig != sigint_count)
	{
		old_sig = sigint_count;
		write(1, "\n", 1);
	}
	else
		printf("%s\n", inpt);
	// if (inpt != NULL)
	// 	printf("%s\n", inpt);
	// else
		
	free(inpt);
	inpt = NULL;
}

void	read_commands(t_mini *mini)
{
	(void)mini;
	while (1)
		new_prompt();
}