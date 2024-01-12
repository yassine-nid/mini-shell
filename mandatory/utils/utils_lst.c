/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:02:39 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/12 15:24:41 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(void *key, void *value, void *origin)
{
	t_env	*result;

	result = malloc (sizeof * result);
	if (result == NULL)
		return (result);
	result->next = NULL;
	result->value = value;
	result->key = key;
	result->origin = origin;
	return (result);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp_lst;

	temp_lst = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp_lst->next != NULL)
		temp_lst = temp_lst->next;
	temp_lst->next = new;
}

void	ft_lstiter(t_env *lst, void (*f)())
{
	int	index;

	if (lst == NULL)
		return ;
	index = 0;
	while (lst != NULL)
	{
		f(lst, index);
		lst = lst->next;
		index++;
	}
}
