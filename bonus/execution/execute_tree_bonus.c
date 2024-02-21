/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:01:02 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:33:03 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	execute_type(t_mini *mini, t_tree *root, int level)
{
	if (!root)
		return (0);
	else if (root->node->type == AND)
		return (execute_and(mini, root, level));
	else if (root->node->type == OR)
		return (execute_or(mini, root, level));
	else if (root->node->type == PIPE)
		return (execute_pip(mini, root, level + 1));
	else
		return (execute_cmd(mini, root, level));
}

int	execute_tree(t_mini *mini)
{
	t_tree	*root;

	root = mini->tree;
	mini->exit_status = execute_type(mini, root, 0);
	return (mini->exit_status);
}
