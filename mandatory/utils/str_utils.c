/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:39:45 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/19 08:11:43 by yzirri           ###   ########.fr       */
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

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (c + ('a' - 'A'));
	return (c);
}

bool    ft_strcmp_no_case(const char *s1, const char *s2)
{
    if (!s1 && s2)
        return (false);
	if (s1 && !s2)
        return (false);
    while (*s1 && *s2)
    {
        if (ft_tolower(*s1) != ft_tolower(*s2))
			return (false);
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 == (unsigned char)*s2);
}

int	ft_putstr_fd(char *s, int fd)
{
	char	c;
	int		return_val;

	if (s == NULL)
		return (write(fd, "", 0));
	return_val = 0;
	while (*s)
	{
		c = *s;
		return_val += write(fd, &c, 1);
		s++;
	}
	return (return_val);
}

