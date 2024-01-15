/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:39:45 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/15 14:30:47 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 && s2)
        return (false);
	if (s1 && !s2)
        return (false);
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (false);
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 == (unsigned char)*s2);
}
