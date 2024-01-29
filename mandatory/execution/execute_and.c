/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:48 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/28 09:42:04 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_and(t_mini *mini, t_tree *root, int level)
{
	int	status;
	(void)	mini;

	status = execute_type(mini, root->left, level);
	if (!status)
		status = execute_type(mini, root->right, level);
	return (status);
}
