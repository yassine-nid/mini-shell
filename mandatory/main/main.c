/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:47:59 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/12 18:15:53 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	main_init(&mini, envp);
	listen_to_signals(&mini);
	read_commands(&mini);
	return (0);
}