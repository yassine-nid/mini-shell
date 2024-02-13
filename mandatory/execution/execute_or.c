/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:35 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/11 10:54:01 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_or(t_mini *mini, t_tree *root, int level)
{
	int	status;

	status = execute_type(mini, root->left, level);
	if (status)
		status = execute_type(mini, root->right, level);
	return (status);
}
