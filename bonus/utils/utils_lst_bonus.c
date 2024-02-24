/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:02:39 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 22:13:22 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

t_env	*ft_lstnew(void *key, void *value)
{
	t_env	*result;

	result = malloc (sizeof * result);
	if (result == NULL)
		return (result);
	result->next = NULL;
	result->value = value;
	result->key = key;
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

void	herdoc_incrypt(char *str)
{
	int	index;

	index = 0;
	while (str && str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			str[index] = (unsigned char)(str[index] + 100);
		index++;
	}
}
