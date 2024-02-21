/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_libft_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:12:32 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:36:37 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p;
	char		ch;

	ch = (char) c;
	p = s;
	if (!s)
		return (0);
	while (*p)
	{
		if (*p == ch)
			return ((char *) p);
		p++;
	}
	return (0);
}

int	is_alpha_num(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

bool	is_str_alpha_num(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (!ft_isalpha(*str) && !ft_isdigit(*str) && !(*str == '_'))
			return (false);
		str++;
	}
	return (true);
}

bool	ft_strcmp(const char *s1, const char *s2)
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
