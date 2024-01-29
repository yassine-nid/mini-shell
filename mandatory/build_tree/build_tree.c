/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:00:21 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/24 11:30:06 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_to_tree(t_tree **root, t_tree *new_node)
{
	if (!*root)
		*root = new_node;
	else if (get_priority((*root)->node) < get_priority(new_node->node))
	{
		new_node->left = *root;
		*root = new_node;
	}
	else if ((*root)->right == NULL)
		(*root)->right = new_node;
	else
		add_to_tree(&(*root)->right, new_node);
}

static void	add_to_tree_par(t_tree **root, t_tree *new_node)
{
	if (!*root)
		*root = new_node;
	else if ((*root)->right == NULL)
		(*root)->right = new_node;
	else
		add_to_tree_par(&(*root)->right, new_node);
}

static void	creat_add_node(t_token *token, t_tree **root, t_mini *mini, int lvl)
{
	t_tree	*new_node;

	new_node = creat_node(token, mini, lvl);
	add_to_tree(root, new_node);
}

static int	condition(t_token *token)
{
	return (!token->preveus || (token->preveus->type != RED_AP_OUT
			&& token->preveus->type != RED_OUT && token->preveus->type != H_DOC
			&& token->preveus->type != WORD && token->preveus->type != RED_IN));
}

t_tree	*build_tree(t_token **token, t_mini *mini, int level)
{
	t_tree	*root;
	t_tree	*new_node;

	root = NULL;
	while ((*token))
	{
		if ((*token)->type == OPEN_PAR)
		{
			(*token) = (*token)->next;
			new_node = build_tree(token, mini, level + 1);
			if (new_node)
				add_to_tree_par(&root, new_node);
		}
		else if ((*token)->type == CLOSE_PAR)
			break ;
		else if ((*token)->type == OR || (*token)->type == AND
			|| (*token)->type == PIPE)
			creat_add_node((*token), &root, mini, level);
		else if (condition((*token)))
			creat_add_node((*token), &root, mini, level);
		if ((*token))
			(*token) = (*token)->next;
	}
	return (root);
}
