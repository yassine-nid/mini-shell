/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:44:29 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/23 11:30:07 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*creat_node(t_token *token, t_mini *mini)
{
	t_tree	*new_node;

	new_node = (t_tree *) malloc(sizeof (t_tree));
	if (!new_node)
		return (clean_exit(mini, NULL, errno), NULL);
	new_node->node = token;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	get_priority(t_token *token)
{
	if (token->type == PIPE)
		return (1);
	else if (token->type == OR)
		return (2);
	else if (token->type == AND)
		return (3);
	else
		return (0);
}
