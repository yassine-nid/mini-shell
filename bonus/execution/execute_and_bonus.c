/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:48 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:32:44 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	execute_and(t_mini *mini, t_tree *root, int level)
{
	int	status;

	status = execute_type(mini, root->left, level);
	if (!status)
		status = execute_type(mini, root->right, level);
	return (status);
}
